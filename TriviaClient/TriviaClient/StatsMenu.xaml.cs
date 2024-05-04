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
    /// Interaction logic for StatsMenu.xaml
    /// </summary>
    public partial class StatsMenu : Window
    {
        public PersonalStats personalStats;

        public StatsMenu()
        {
            InitializeComponent();
        }

        private void BestScoresButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void PersonalStatsButton_Click(object sender, RoutedEventArgs e)
        {
            this.personalStats = new PersonalStats();
            this.personalStats.Show();
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
