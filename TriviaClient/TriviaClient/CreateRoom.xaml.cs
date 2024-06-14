using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Xml.Linq;
namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        public MainWindow mainWindow;
        public ConnectedRoom connectedRoom;
        private uint amountOfRooms;
        private bool isMatchmaking;

        public CreateRoom(MainWindow main, bool isMatchmaking)
        {
            this.isMatchmaking = isMatchmaking;
            mainWindow = main;
            InitializeComponent();
            amountOfRooms = 0;

            if (isMatchmaking)
            {
                this.NumberOfPlayersTextBox.Text = "2";
                this.NumberOfPlayersTextBox.IsEnabled = false;
            }
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            this.mainWindow.Show();
        }

        private void SubmitButton_Click(object sender, RoutedEventArgs e)
        {
            if ( this.NumberOfPlayersTextBox.Text == "" || this.NumberOfQuestionsTextBox.Text == "" 
                || this.RoomNameTextBox.Text == "" || this.TimeForQuestionTextBox.Text == "")
            {
                MessageBox.Show("Invalid Credentials!", "[Trivia] Error", MessageBoxButton.OK, icon: MessageBoxImage.Error);
                return;
            }
            try
            {
                CreateRoomRequest createRoomRequest = new CreateRoomRequest();
                createRoomRequest.roomName = this.RoomNameTextBox.Text;
                createRoomRequest.maxUsers = uint.Parse(this.NumberOfPlayersTextBox.Text);
                createRoomRequest.answerTimeout = uint.Parse(this.TimeForQuestionTextBox.Text);
                createRoomRequest.questionsCount = uint.Parse(this.NumberOfQuestionsTextBox.Text);
                createRoomRequest.SendToServer(this.mainWindow.clientStream);

                CreateRoomRequest.CreateRoomResponse createRoomResponse = createRoomRequest.GetFromServer(this.mainWindow.clientStream);
                if ((uint)Cods.Status.CREATE_ROOM_STATUS == createRoomResponse.status)
                {
                    try
                    {
                        CreateRoomRequest.RoomData roomData = new CreateRoomRequest.RoomData(createRoomRequest, 0, amountOfRooms);
                        amountOfRooms++;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.ToString());
                        return;
                    }

                    this.Close();
                    this.connectedRoom = new ConnectedRoom(mainWindow, true, createRoomRequest.questionsCount, createRoomRequest.answerTimeout, false);
                    this.connectedRoom.room = this;
                    this.connectedRoom.mainWindow = this.mainWindow;
                    this.connectedRoom.ConnectedRoomNameLabel.Content = this.RoomNameTextBox.Text;
                    this.connectedRoom.MaxPlayersLabel.Content = "Max players: " + createRoomRequest.maxUsers;
                    this.connectedRoom.AmountOfQuestionsLabel.Content = "Amount of questions: " + createRoomRequest.questionsCount;
                    this.connectedRoom.TimePerQuestionLabel.Content = "Timer per question: " + createRoomRequest.answerTimeout;
                    this.connectedRoom.Show();
                }
                else MessageBox.Show("[CreateRoom] error");
            }
            catch(Exception ex)
            {
                MessageBox.Show("Invalid Credentials!", "[Trivia] Error", MessageBoxButton.OK, icon: MessageBoxImage.Error);
                return;
            }
        }
    }
}
