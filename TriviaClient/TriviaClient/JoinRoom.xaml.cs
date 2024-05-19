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

        public JoinRoom(MainWindow main)
        {
            mainWindow = main;
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
            if (this.RoomsListBox.SelectedItem != null)
            {
                string selectedRoom = this.RoomsListBox.SelectedItem.ToString();
                MessageBox.Show($"Joining room: {selectedRoom}");

                this.Hide();
                this.refreshBackgroundWorker.CancelAsync();
                this.connectedRoom = new ConnectedRoom(this.mainWindow);
                this.connectedRoom.Show();
                this.connectedRoom.ConnectedRoomNameLabel.Content = selectedRoom;
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

                foreach (CreateRoomRequest.RoomData rd in getRoomsResponse.rooms)
                {
                    if (!this.RoomsListBox.Items.Contains(rd.name))
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
                MessageBox.Show("BackgroundWorker canceled");
            }
            else
            {
                MessageBox.Show("BackgroundWorker ended successfully");
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
