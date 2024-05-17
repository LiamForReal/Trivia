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
        private GetHighScoreRequest getHighScoreRequest;
        private GetPersonalStatsRequest getPersonalStatsRequest;
        public StatsMenu(MainWindow main)
        {
            getPersonalStatsRequest = new GetPersonalStatsRequest();
            getHighScoreRequest = new GetHighScoreRequest();
            mainWindow = main;
            InitializeComponent();
        }

        private void BestScoresButton_Click(object sender, RoutedEventArgs e)
        {
            getHighScoreRequest.SendToServer(mainWindow.clientStream);
            Cods.Status res = (Cods.Status)(getHighScoreRequest.GetFromServer(mainWindow.clientStream).status);
            if(res == Cods.Status.GET_HIGH_SCORE_STATUS)
            {
                this.Hide();
                this.bestScores = new BestScores(this);
                this.bestScores.Show();
            }else MessageBox.Show("[GET_HIGH_SCORE] error!");
           
        }

        private void PersonalStatsButton_Click(object sender, RoutedEventArgs e)
        {
            getPersonalStatsRequest.SendToServer(mainWindow.clientStream);
            GetPersonalStatsRequest.GetPersonalStatsResponse response = getPersonalStatsRequest.GetFromServer(mainWindow.clientStream);
            if ((Cods.Status)response.status == Cods.Status.GET_PERSONAL_STATS_STATUS)
            {
                this.Hide();
                this.personalStats = new PersonalStats(this);
                this.personalStats.Show();
            }
            else MessageBox.Show("[GET_PERSONAL_STATS] error!");
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            this.mainWindow.Show();
        }
    }
}
