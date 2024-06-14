using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;
using System.Net;
using System.Windows.Interop;
using static TriviaClient.CreateRoomRequest;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public LogInScreen logInScreen;
        public SignUpScreen signUpScreen;
        public StatsMenu statsMenu;
        public CreateRoom createRoom;
        public JoinRoom joinRoom;
        public AddNewQuestion addNewQuestion;

        public bool isUserLogged;
        public string username;
        public TcpClient client;
        public NetworkStream clientStream;

        private LogOutResquest logOutResquest;
        public MainWindow()
        {
            try
            {
                logOutResquest = new LogOutResquest();
                this.client = new TcpClient();
                IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8888);
                client.Connect(serverEndPoint);
                this.clientStream = this.client.GetStream();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Could not connect to trivia server", "[Trivia] Connection Error", MessageBoxButton.OK, MessageBoxImage.Error);
                this.Close();
            }

            InitializeComponent();
        }

        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.logInScreen = new LogInScreen();
            this.logInScreen.mainWindow = this;
            this.logInScreen.Show();

            if (this.isUserLogged)
            {
                this.SignUpButton.Visibility = Visibility.Collapsed;
            }
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.logInScreen != null)
            {
                this.logInScreen.Close();
            }
            if (this.signUpScreen != null)
            {
                this.signUpScreen.Close();
            }
            if (this.statsMenu != null)
            {
                if (this.statsMenu.personalStats != null)
                {
                    this.statsMenu.personalStats.Close();
                }
                if (this.statsMenu.bestScores != null)
                {
                    this.statsMenu.bestScores.Close();
                }
                this.statsMenu.Close();
            }
            if (this.addNewQuestion != null)
            {
                this.addNewQuestion.Close();
            }

            this.Close();
          
            if (this.isUserLogged)
            {
                this.LogOutButton_Click(sender, e); // if doesnt work it is liam's fault!!!
            }

            if (this.client != null)
            {
                this.client.Close();
            }
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.signUpScreen = new SignUpScreen();
            this.signUpScreen.mainWindow = this;
            this.signUpScreen.Show();
        }

        private void LogOutButton_Click(object sender, RoutedEventArgs e)
        {
            if (!this.isUserLogged)
            {
                MessageBox.Show("There Is No User Logged!", "[Trivia] Message", MessageBoxButton.OK, icon: MessageBoxImage.Exclamation);
                return;
            }
            logOutResquest.SendToServer(clientStream);
            Cods.Status res = (Cods.Status)logOutResquest.GetFromServer(clientStream).status;
            if (res == Cods.Status.LOGOUT_STATUS)
            {
                this.isUserLogged = false;
                this.username = "";
                this.HelloLabel.Content = "";
                this.HelloLabel.Visibility = Visibility.Collapsed;
                this.LogInButton.Visibility = Visibility.Visible;
                this.SignUpButton.Visibility = Visibility.Visible;
                this.CreateRoomButton.IsEnabled = false;
                this.JoinRoomButton.IsEnabled = false;
                this.LogOutButton.IsEnabled = false;
                this.LogOutButton.Visibility = Visibility.Collapsed;
                this.StatsMenuButton.IsEnabled = false;
                this.AddNewQuestionButton.IsEnabled = false;
                this.JoinMatchmakingButton.IsEnabled = false;
            }
            else MessageBox.Show("[LogOut] error!");
        }

        private void StatsMenuButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.statsMenu = new StatsMenu(this);
            this.statsMenu.Show();
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.joinRoom = new JoinRoom(this);
            this.joinRoom.Show();
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.createRoom = new CreateRoom(this, false);
            this.createRoom.Show();
        }

        public void SendToServer(List<byte> list)
        {
            byte[] buffer = list.ToArray();
            this.clientStream.Write(buffer, 0, buffer.Length);
            this.clientStream.Flush();

            // FOR DEBUG:
            byte[] response = new byte[4096];
            this.clientStream.Read(response, 0, 4096);

            foreach (byte b in response)
            {
                Console.Write((char)b);
            }
            Console.WriteLine();
        }

        private void AddNewQuestionButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.addNewQuestion = new AddNewQuestion(this);
            this.addNewQuestion.Show();
        }

        private void JoinMatchmakingButton_Click(object sender, RoutedEventArgs e)
        {
            MatchmakeRequest matchmakeRequest = new MatchmakeRequest();
            matchmakeRequest.SendToServer(this.clientStream);
            MatchmakeRequest.MatchmakeResponse matchmakeResponse = matchmakeRequest.GetFromServer(this.clientStream);

            if ((uint)(Cods.Status.MATCHMAKE_CREATE_STATUS) == matchmakeResponse.status)
            {
                this.Hide();
                this.createRoom = new CreateRoom(this, true);
                this.createRoom.Show();
            }
            else if ((uint)(Cods.Status.MATCHMAKE_JOIN_STATUS) == matchmakeResponse.status)
            {
                this.Hide();
                ConnectedRoom connectedRoom = new ConnectedRoom(this, false, matchmakeResponse.amountOfQuestions, matchmakeResponse.timePerQuestion, true);
                connectedRoom.Show();
            }
        }
    }
}