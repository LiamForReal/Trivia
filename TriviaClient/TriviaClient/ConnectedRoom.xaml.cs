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
using static TriviaClient.GetRoomsRequest;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for ConnectedRoom.xaml
    /// </summary>
    public partial class ConnectedRoom : Window
    {
        public MainWindow mainWindow;
        public CreateRoom room;

        private BackgroundWorker refreshBackgroundWorker = new BackgroundWorker();

        public ConnectedRoom(MainWindow main)
        {
            mainWindow = main;
            InitializeComponent();

            this.refreshBackgroundWorker.WorkerSupportsCancellation = true;
            this.refreshBackgroundWorker.WorkerReportsProgress = true;

            this.refreshBackgroundWorker.DoWork += this.RefreshPlayersInRoomLoop_DoWork;
            this.refreshBackgroundWorker.ProgressChanged += this.RefreshPlayersInRoomLoop_ProgressChanged;
            this.refreshBackgroundWorker.RunWorkerCompleted += this.RefreshPlayersInRoomLoop_RunWorkerCompleted;

            this.refreshBackgroundWorker.RunWorkerAsync();
        }

        private void LeaveRoomButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            mainWindow.Show();
        }

        private void RefreshPlayersInRoom()
        {
/*            GetRoomsRequest getRoomsRequest = new GetRoomsRequest();
            getRoomsRequest.SendToServer(this.mainWindow.clientStream);
            GetRoomsResponse getRoomsResponse = getRoomsRequest.GetFromServer(this.mainWindow.clientStream);
            if ((uint)(Cods.Status.GET_ROOMS_STATUS) == getRoomsResponse.status)
            {
                this.RoomsListBox.Items.Clear();
                foreach (CreateRoomRequest.RoomData rd in getRoomsResponse.rooms)
                {
                    this.RoomsListBox.Items.Add(rd.name);
                }
            }*/
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
    }
}
