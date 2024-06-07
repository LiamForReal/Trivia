using System;
using System.Threading;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Diagnostics;
using static TriviaClient.GetRoomsRequest;
using System.ComponentModel;

namespace TriviaClient
{
    public partial class JoinRoom : Window
    {
        public ConnectedRoom connectedRoom;
        public MainWindow mainWindow;
        private BackgroundWorker refreshBackgroundWorker = new BackgroundWorker();
        private JoinRoomRequest jrr;

        public JoinRoom(MainWindow main)
        {
            mainWindow = main;
            jrr = new JoinRoomRequest(0);
            InitializeComponent();
            
            this.JoinButton.IsEnabled = false;

            this.refreshBackgroundWorker.WorkerSupportsCancellation = true;
            this.refreshBackgroundWorker.WorkerReportsProgress = true;

            this.refreshBackgroundWorker.DoWork += this.RefreshAvailableRoomsLoop_DoWork;
            this.refreshBackgroundWorker.ProgressChanged += this.RefreshAvailableRoomsLoop_ProgressChanged;
            this.refreshBackgroundWorker.RunWorkerCompleted += this.RefreshAvailableRoomsLoop_RunWorkerCompleted;

            this.refreshBackgroundWorker.RunWorkerAsync();
        }

        private void JoinButton_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomRequest.RoomData connectedRoomData = new CreateRoomRequest.RoomData();
            uint roomId = 0;
            string selectedRoom = this.RoomsListBox.SelectedItem.ToString();

            if (this.RoomsListBox.SelectedItem != null)
            {
                GetRoomsRequest getRoomsRequest = new GetRoomsRequest();
                getRoomsRequest.SendToServer(this.mainWindow.clientStream);
                GetRoomsResponse getRoomsResponse = getRoomsRequest.GetFromServer(this.mainWindow.clientStream);

                if ((uint)(Cods.Status.GET_ROOMS_STATUS) == getRoomsResponse.status)
                {
                    foreach (CreateRoomRequest.RoomData rd in getRoomsResponse.rooms)
                    {
                        if (rd.name == selectedRoom)
                        {
                            roomId = rd.id;
                            connectedRoomData = rd;
                            break;
                        }
                    }
                }

                MessageBox.Show($"Joining room: {selectedRoom}");

                jrr.roomId = roomId;
                jrr.SendToServer(this.mainWindow.clientStream);
                uint statusCode= (uint)jrr.GetFromServer(this.mainWindow.clientStream).status;
                if((Cods.Status)statusCode == Cods.Status.JOIN_ROOM_STATUS)
                {
                    this.Close();
                    this.refreshBackgroundWorker.CancelAsync();
                    this.connectedRoom = new ConnectedRoom(this.mainWindow, false, connectedRoomData.numOfQuestionsInGame, connectedRoomData.timePerQuestion);
                    this.connectedRoom.ConnectedRoomNameLabel.Content = selectedRoom;
                    this.connectedRoom.MaxPlayersLabel.Content = "Max players: " + connectedRoomData.maxPlayers;
                    this.connectedRoom.AmountOfQuestionsLabel.Content = "Amount of questions: " + connectedRoomData.numOfQuestionsInGame;
                    this.connectedRoom.TimePerQuestionLabel.Content = "Timer per question: " + connectedRoomData.timePerQuestion;
                    this.connectedRoom.Show();
                } else MessageBox.Show("cant join room");

            }
            else
            {
                MessageBox.Show("Please select a room to join.");
            }
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
            this.refreshBackgroundWorker.CancelAsync();
            this.Close();
            this.mainWindow.Show();
        }

        private void RefreshAvailableRooms()
        {
            GetRoomsRequest getRoomsRequest = new GetRoomsRequest();
            getRoomsRequest.SendToServer(this.mainWindow.clientStream);
            GetRoomsResponse getRoomsResponse = getRoomsRequest.GetFromServer(this.mainWindow.clientStream);
            if ((uint)(Cods.Status.GET_ROOMS_STATUS) == getRoomsResponse.status)
            {
                if (getRoomsResponse.rooms.Count <= 0)
                {
                    this.NoRoomsAvailable.Content = "No Rooms Available";
                }
                else
                {
                    this.NoRoomsAvailable.Content = "";
                }

                this.RoomsListBox.Items.Clear();
                foreach (CreateRoomRequest.RoomData rd in getRoomsResponse.rooms)
                {
                    if (rd.isActive == 0) // not active
                    {
                        this.RoomsListBox.Items.Add(rd.name);
                    }
                }

                if (this.RoomsListBox.SelectedItem != null)
                {
                    this.JoinButton.IsEnabled = true;
                }
                else
                {
                    this.JoinButton.IsEnabled = false;
                }
            }
        }

        private void RefreshAvailableRoomsLoop_DoWork(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (this.refreshBackgroundWorker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                this.refreshBackgroundWorker.ReportProgress(0);
                Thread.Sleep(3000);
            }
        }

        private void RefreshAvailableRoomsLoop_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            RefreshAvailableRooms();
        }

        private void RefreshAvailableRoomsLoop_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                // MessageBox.Show("BackgroundWorker canceled");
            }
            else
            {
                // MessageBox.Show("BackgroundWorker ended successfully");
            }
        }

        private void RoomsListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (this.RoomsListBox.SelectedItem != null)
            {
                this.JoinButton.IsEnabled = true;
            }
            else
            {
                this.JoinButton.IsEnabled = false;
            }
        }
    }

}
