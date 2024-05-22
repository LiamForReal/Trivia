using System;
using System.Collections.Generic;
using System.ComponentModel;
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
using static TriviaClient.CreateRoomRequest.RoomData;
using static TriviaClient.GetRoomsRequest;
using static TriviaClient.GetPlayersInRoomRequest;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for ConnectedRoom.xaml
    /// </summary>
    public partial class ConnectedRoom : Window
    {
        public MainWindow mainWindow;
        public CreateRoom room;
        public bool isOwner;

        private BackgroundWorker refreshBackgroundWorker = new BackgroundWorker();

        public ConnectedRoom(MainWindow main, bool isOwner)
        {
            this.mainWindow = main;
            InitializeComponent();

            this.refreshBackgroundWorker.WorkerSupportsCancellation = true;
            this.refreshBackgroundWorker.WorkerReportsProgress = true;

            this.refreshBackgroundWorker.DoWork += this.RefreshPlayersInRoomLoop_DoWork;
            this.refreshBackgroundWorker.ProgressChanged += this.RefreshPlayersInRoomLoop_ProgressChanged;
            this.refreshBackgroundWorker.RunWorkerCompleted += this.RefreshPlayersInRoomLoop_RunWorkerCompleted;

            this.refreshBackgroundWorker.RunWorkerAsync();
            this.isOwner = isOwner;

            if (isOwner)
            {
                this.LeaveRoomButton.IsEnabled = false;
                this.LeaveRoomButton.Visibility = Visibility.Collapsed;
                this.StartGameButton.IsEnabled = true;
                this.StartGameButton.Visibility = Visibility.Visible;
                this.CloseRoomButton.IsEnabled = true;
                this.CloseRoomButton.Visibility = Visibility.Visible;
            }
        }

        private void LeaveRoomButton_Click(object sender, RoutedEventArgs e)
        {
            LeaveRoomRequest leaveRoomRequest = new LeaveRoomRequest();
            leaveRoomRequest.SendToServer(this.mainWindow.clientStream);
            LeaveRoomRequest.LeaveRoomResponse leaveRoomResponse = leaveRoomRequest.GetFromServer(this.mainWindow.clientStream);

            if ((uint)Cods.Status.LEAVE_ROOM_STATUS == leaveRoomResponse.status)
            {
                this.Close();
                mainWindow.Show();
                this.refreshBackgroundWorker.CancelAsync();
            }
        }

        private void RefreshPlayersInRoom()
        {
            uint roomId = 0;

            GetRoomsRequest getRoomsRequest = new GetRoomsRequest();
            getRoomsRequest.SendToServer(this.mainWindow.clientStream);
            GetRoomsResponse getRoomsResponse = getRoomsRequest.GetFromServer(this.mainWindow.clientStream);

            if (this.ConnectedRoomNameLabel.Content != null && (uint)(Cods.Status.GET_ROOMS_STATUS) == getRoomsResponse.status)
            {
                foreach (CreateRoomRequest.RoomData rd in getRoomsResponse.rooms)
                {
                    if (rd.name == this.ConnectedRoomNameLabel.Content.ToString())
                    {
                        roomId = rd.id;
                        break;
                    }
                }

                GetPlayersInRoomRequest getPlayersInRoomRequest = new GetPlayersInRoomRequest(roomId);
                getPlayersInRoomRequest.SendToServer(this.mainWindow.clientStream);
                GetPlayersInRoomRequest.GetPlayersInRoomResponse getPlayersInRoomResponse = getPlayersInRoomRequest.GetFromServer(this.mainWindow.clientStream);

                if ((uint)(Cods.Status.GET_PLAYERS_IN_ROOM_STATUS) == getPlayersInRoomResponse.status)
                {
                    this.PlayersListBox.Items.Clear();
                    foreach (string player in getPlayersInRoomResponse.players)
                    {
                        this.PlayersListBox.Items.Add(player);
                    }
                }
            }
        }

        private void RefreshPlayersInRoomLoop_DoWork(object sender, DoWorkEventArgs e)
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

        private void RefreshPlayersInRoomLoop_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            RefreshPlayersInRoom();
        }

        private void RefreshPlayersInRoomLoop_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                MessageBox.Show("BackgroundWorker canceled");
            }
            else
            {
                MessageBox.Show("BackgroundWorker ended successfully");
            }
        }

        private void StartGameButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void CloseRoomButton_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
