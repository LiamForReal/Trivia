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
using System.Windows.Threading;

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
        public GameScreen gameScreen;

        private uint questionsAmount;
        private uint timePerQuestion;

        private bool isMatchmaking;

        private BackgroundWorker getRoomStateBackgroundWorker;

        public ConnectedRoom(MainWindow main, bool isOwner, uint questionsAmount, uint timePerQuestion, bool isMatchmaking)
        {
            this.mainWindow = main;

            this.isMatchmaking = isMatchmaking;

            InitializeComponent();

            this.getRoomStateBackgroundWorker = new BackgroundWorker();

            this.getRoomStateBackgroundWorker.WorkerSupportsCancellation = true;
            this.getRoomStateBackgroundWorker.WorkerReportsProgress = true;

            this.getRoomStateBackgroundWorker.DoWork += this.GetRoomStateLoop_DoWork;
            this.getRoomStateBackgroundWorker.ProgressChanged += this.GetRoomStateLoop_ProgressChanged;
            this.getRoomStateBackgroundWorker.RunWorkerCompleted += this.GetRoomStateLoop_RunWorkerCompleted;

            if (isMatchmaking)
            {
                this.LeaveRoomButton.IsEnabled = false;
                this.LeaveRoomButton.Visibility = Visibility.Collapsed;
                //this.StartGameButton.IsEnabled = false;
                this.StartGameButton.Visibility = Visibility.Collapsed;
                this.CloseRoomButton.IsEnabled = false;
                this.CloseRoomButton.Visibility = Visibility.Collapsed;
            }

            this.isOwner = isOwner;

            if (!isMatchmaking && isOwner)
            {
                this.LeaveRoomButton.IsEnabled = false;
                this.LeaveRoomButton.Visibility = Visibility.Collapsed;
                this.StartGameButton.IsEnabled = true;
                this.StartGameButton.Visibility = Visibility.Visible;
                this.CloseRoomButton.IsEnabled = true;
                this.CloseRoomButton.Visibility = Visibility.Visible;
            }

            this.getRoomStateBackgroundWorker.RunWorkerAsync();

            this.questionsAmount = questionsAmount;
            this.timePerQuestion = timePerQuestion;
        }

        private void LeaveRoomButton_Click(object sender, RoutedEventArgs e)
        {
            this.getRoomStateBackgroundWorker.CancelAsync();

            LeaveRoomRequest leaveRoomRequest = new LeaveRoomRequest();
            leaveRoomRequest.SendToServer(this.mainWindow.clientStream);
            LeaveRoomRequest.LeaveRoomResponse leaveRoomResponse = leaveRoomRequest.GetFromServer(this.mainWindow.clientStream);

            if ((uint)Cods.Status.LEAVE_ROOM_STATUS == leaveRoomResponse.status)
            {
                this.Close();
                mainWindow.Show();
            }
            else
            {
                this.getRoomStateBackgroundWorker.RunWorkerAsync();
            }
        }

        private void GetRoomState()
        {
            GetRoomStateRequest getRoomStateRequest = new GetRoomStateRequest();
            getRoomStateRequest.SendToServer(this.mainWindow.clientStream);
            GetRoomStateRequest.GetRoomStateResponse getRoomStateResponse = getRoomStateRequest.GetFromServer(this.mainWindow.clientStream);

            if ((uint)Cods.Errors.GET_ROOM_STATE_ROOM_ERROR == getRoomStateResponse.status && !isOwner)
            {
                this.getRoomStateBackgroundWorker.CancelAsync();
                this.mainWindow.Show();
                this.Close();
            }
            else if ((uint)Cods.Status.GET_ROOM_STATE_STATUS == getRoomStateResponse.status && !isOwner)
            {
                this.getRoomStateBackgroundWorker.CancelAsync();
                this.gameScreen = new GameScreen(this, this.mainWindow, this.questionsAmount, this.timePerQuestion);
                this.gameScreen.Show();
                this.Close();
            }
            else
            {
                this.PlayersListBox.Items.Clear();
                foreach (string player in getRoomStateResponse.players)
                {
                    this.PlayersListBox.Items.Add(player);
                }

                if (isMatchmaking && isOwner)
                {
                    if (this.PlayersListBox.Items.Count == 2)
                    {
                        this.StartGameLogic();
                    }
                }
            }
        }

        private void GetRoomStateLoop_DoWork(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (this.getRoomStateBackgroundWorker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                this.getRoomStateBackgroundWorker.ReportProgress(0);
                Thread.Sleep(3000);
            }
        }

        private void GetRoomStateLoop_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            this.GetRoomState();
        }

        private void GetRoomStateLoop_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                // MessageBox.Show("BackgroundWorker cancelled");
            }
            else
            {
                // MessageBox.Show("BackgroundWorker ended successfully");
            }
        }

        private void StartGameLogic()
        {
            this.getRoomStateBackgroundWorker.CancelAsync();
            StartGameRequest sgr = new StartGameRequest();
            sgr.SendToServer(this.mainWindow.clientStream);
            StartGameRequest.StartGameResponse responed = sgr.GetFromServer(this.mainWindow.clientStream);
            if (Cods.Status.START_GAME_STATUS == (Cods.Status)responed.status)
            {
                this.Hide();
                this.gameScreen = new GameScreen(this, this.mainWindow, this.questionsAmount, this.timePerQuestion);
                this.gameScreen.Show();
            }
            else this.getRoomStateBackgroundWorker.RunWorkerAsync();
        }

        private void StartGameButton_Click(object sender, RoutedEventArgs e)
        {
            this.StartGameLogic();
        }

        private void CloseRoomButton_Click(object sender, RoutedEventArgs e)
        {
            this.getRoomStateBackgroundWorker.CancelAsync();

            CloseRoomRequest closeRoomRequest = new CloseRoomRequest();
            closeRoomRequest.SendToServer(this.mainWindow.clientStream);
            CloseRoomRequest.CloseRoomResponse closeRoomResponse = closeRoomRequest.GetFromServer(this.mainWindow.clientStream);

            if ((uint)(Cods.Status.CLOSE_ROOM_STATUS) == closeRoomResponse.status)
            {
                this.Close();
                this.mainWindow.Show();
            }
            else
            {
                this.getRoomStateBackgroundWorker.RunWorkerAsync();
            }
        }
    }
}