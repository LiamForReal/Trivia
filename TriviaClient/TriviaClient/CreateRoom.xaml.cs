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
        private CreateRoomRequest createRoomRequest;
        private List<CreateRoomRequest.RoomData> rooms;
        public ConnectedRoom connectedRoom;

        public CreateRoom(MainWindow main)
        {
            mainWindow = main;
            rooms = new List<CreateRoomRequest.RoomData>();
            createRoomRequest = new CreateRoomRequest("", 0, 0, 0);
            InitializeComponent();
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            this.mainWindow.Show();
        }

        private void SubmitButton_Click(object sender, RoutedEventArgs e)
        {
            this.connectedRoom = new ConnectedRoom(mainWindow, true);
            this.connectedRoom.room = this;
            this.connectedRoom.mainWindow = this.mainWindow;
            this.connectedRoom.ConnectedRoomNameLabel.Content = this.RoomNameTextBox.Text;

            if (this.NumberOfPlayersTextBox.Text == "" || this.NumberOfQuestionsTextBox.Text == ""
                || this.RoomNameTextBox.Text == "" || this.TimeForQuestionTextBox.Text == "")

            {
                MessageBox.Show("Invalid Credentials!", "[Trivia] Error", MessageBoxButton.OK, icon: MessageBoxImage.Error);
                return;
            }
            try
            {
                createRoomRequest.roomName = this.RoomNameTextBox.Text;
                createRoomRequest.maxUsers = uint.Parse(this.NumberOfPlayersTextBox.Text);
                createRoomRequest.answerTimeout = uint.Parse(this.TimeForQuestionTextBox.Text);
                createRoomRequest.questionsCount = uint.Parse(this.NumberOfQuestionsTextBox.Text);
                createRoomRequest.SendToServer(mainWindow.clientStream);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Invalid Credentials!", "[Trivia] Error", MessageBoxButton.OK, icon: MessageBoxImage.Error);
                return;
            }

            CreateRoomRequest.CreateRoomResponse roomResponse = createRoomRequest.GetFromServer(mainWindow.clientStream);

            if (roomResponse.status == (uint)Cods.Status.CREATE_ROOM_STATUS)
            {
                try
                {
                    CreateRoomRequest.RoomData roomData = new CreateRoomRequest.RoomData(createRoomRequest, 0, (uint)this.rooms.Count());
                    rooms.Add(roomData);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                    return;
                }

                this.Close();
                connectedRoom.Show();
            }
            else MessageBox.Show("[CreateRoom] error");
        }
          
    }
}
