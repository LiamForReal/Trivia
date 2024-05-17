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
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using static TriviaClient.GetRoomsRequest;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        public MainWindow mainWindow;
        public JoinRoom(MainWindow main)
        {
            this.mainWindow = main;
            InitializeComponent();
            this.RefreshAvailableRooms();
        }

        private void JoinButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void RefreshButton_Click(object sender, RoutedEventArgs e)
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
            //getRoomsResponse.
        }
    }
}
