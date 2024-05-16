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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for ConnectedRoom.xaml
    /// </summary>
    public partial class ConnectedRoom : Window
    {
        public MainWindow mainWindow;
        public CreateRoom room;
        public ConnectedRoom()
        {
            InitializeComponent();
        }

        private void LeaveRoomButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.mainWindow != null)
            {
                this.mainWindow.Show();
            }
            if (this.room != null)
            {
                this.room.Show();
            }
            this.Close();
        }
    }
}
