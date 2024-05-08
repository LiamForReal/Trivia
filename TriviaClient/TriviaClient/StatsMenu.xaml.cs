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
        public BestScores bestScores;
        public MainWindow mainWindow;

        public StatsMenu()
        {
            InitializeComponent();
        }

        private void BestScoresButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.bestScores = new BestScores();
            this.bestScores.statsMenu = this;
            this.bestScores.Show();
        }

        private void PersonalStatsButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            this.personalStats = new PersonalStats();
            this.personalStats.statsMenu = this;
            this.personalStats.Show();
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            this.mainWindow.Show();
        }
    }
}
