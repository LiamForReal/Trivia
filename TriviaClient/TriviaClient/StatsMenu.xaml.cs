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
            GetHighScoreRequest.GetHighScoreResponse response = getHighScoreRequest.GetFromServer(mainWindow.clientStream);
            if((Cods.Status)response.status == Cods.Status.GET_HIGH_SCORE_STATUS)
            {
                this.Hide();
                this.bestScores = new BestScores(this);
                this.bestScores.FirstPlaceLabel.Content = $"1. {response.statistics[0]}";
                this.bestScores.SecondPlaceLabel.Content = $"2. {response.statistics[1]}";
                this.bestScores.ThirdPlaceLabel.Content = $"3. {response.statistics[2]}";
                this.bestScores.FourPlaceLabel.Content = $"4. {response.statistics[3]}";
                this.bestScores.FivePlaceLabel.Content = $"5. {response.statistics[4]}";
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
                this.personalStats.NumberOfGamesLabel.Content = $"Number Of Games: {response.statistics[0]}";
                this.personalStats.NumberOfRightAnswersLabel.Content = $"Number Of Right Answers: {response.statistics[1]}";
                this.personalStats.NumberOfWrongAnswersLabel.Content = $"Number Of Wrong Answers: {response.statistics[2]}";
                this.personalStats.AverageTimeForAnswerLabel.Content = $"Average Time For Answer: {response.statistics[3]}";
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
