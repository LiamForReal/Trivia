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

        public bool isUserLogged;
        public string username;
        public TcpClient client;
        public NetworkStream clientStream;

        public MainWindow()
        {
            try
            {
                this.client = new TcpClient();
                IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8888);
                client.Connect(serverEndPoint);
                this.clientStream = this.client.GetStream();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Could not connect to trivia server", "[Trivia] Connection Error", MessageBoxButton.OK, MessageBoxImage.Error);
                //this.Close();
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
                var button = (Button)(this.FindName("SignUpButton"));
                if (button != null)
                {
                    button.Visibility = Visibility.Collapsed;
                }
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

            this.Close();
            
            // fix this
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

            this.isUserLogged = false;
            this.username = "";
            this.HelloLabel.Content = "";

            var button = (Button)(this.FindName("LogInButton"));
            if (button != null)
            {
                button.Visibility = Visibility.Visible;
            }

            button = (Button)(this.FindName("SignUpButton"));
            if (button != null)
            {
                button.Visibility = Visibility.Visible;
            }
        }

        private void StatsMenuButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.statsMenu = new StatsMenu();
            this.statsMenu.mainWindow = this;
            this.statsMenu.Show();
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.joinRoom = new JoinRoom();
            this.joinRoom.mainWindow = this;
            this.joinRoom.Show();
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.createRoom = new CreateRoom();
            this.createRoom.mainWindow = this;
            this.createRoom.Show();
        }
    }
}