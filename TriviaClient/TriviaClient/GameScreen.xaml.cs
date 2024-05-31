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
    /// Interaction logic for GameScreen.xaml
    /// </summary>
    public partial class GameScreen : Window
    {
        public ConnectedRoom _conectedRoom;
        public GameScreen(ConnectedRoom conectedRoom)
        {
            _conectedRoom = conectedRoom;
            InitializeComponent();
        }

        private void Answer1_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
