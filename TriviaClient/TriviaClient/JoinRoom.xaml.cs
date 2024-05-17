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
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        public MainWindow mainWindow;
        private BackgroundWorker refreshBackgroundWorker = new BackgroundWorker();

        public JoinRoom(MainWindow main)
        {
            this.mainWindow = main;
            InitializeComponent();

            this.refreshBackgroundWorker.WorkerSupportsCancellation = true;
            this.refreshBackgroundWorker.WorkerReportsProgress = true;
        }

        private void JoinButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
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
                this.RoomsListBox.Items.Clear();
                foreach (CreateRoomRequest.RoomData rd in getRoomsResponse.rooms)
                {
                    this.RoomsListBox.Items.Add(rd.name);
                }
            }
        }

        private void RefreshAvailableRoomsLoop()
        {
            while (true)
            {
                RefreshAvailableRooms();
                Thread.Sleep(3000);
            }
        }
    }
}
