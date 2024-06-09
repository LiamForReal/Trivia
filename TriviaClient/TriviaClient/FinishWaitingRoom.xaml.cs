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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for FinishWaitingRoom.xaml
    /// </summary>
    public partial class FinishWaitingRoom : Window
    {
        public MainWindow mainWindow;

        private BackgroundWorker getResultsBackgroundWorker;


        public FinishWaitingRoom(MainWindow mainWindow)
        {
            this.mainWindow = mainWindow;

            InitializeComponent();

            this.getResultsBackgroundWorker = new BackgroundWorker();

            this.getResultsBackgroundWorker.WorkerSupportsCancellation = true;
            this.getResultsBackgroundWorker.WorkerReportsProgress = true;

            this.getResultsBackgroundWorker.DoWork += this.getResultsLoop_DoWork;
            this.getResultsBackgroundWorker.ProgressChanged += this.getResultsLoop_ProgressChanged;
            this.getResultsBackgroundWorker.RunWorkerCompleted += this.getResultsLoop_RunWorkerCompleted;

            this.getResultsBackgroundWorker.RunWorkerAsync();
        }

        private void getResults()
        {
            this.getResultsBackgroundWorker.CancelAsync();

            GetGameResultsRequest getGameResultsRequest = new GetGameResultsRequest();
            getGameResultsRequest.SendToServer(this.mainWindow.clientStream);
            GetGameResultsRequest.GetGameResultsResponse getGameResultsResponse = getGameResultsRequest.GetFromServer(this.mainWindow.clientStream);

            if ((uint)(Cods.Status.GET_GAME_RESULTS_STATUS) == getGameResultsResponse.status)
            {
                string resultsReport = "";
                int totalAnswers = 0;
                double score = 0.0;
                foreach (PlayerResults playerResults in getGameResultsResponse.results)
                {
                    // TODO: calculate score as our formula 
                    totalAnswers = (int)(playerResults.wrongAnswerCount + playerResults.correctAnswerCount);
                    if((int)(playerResults.correctAnswerCount) != 0 && (double)(playerResults.averageAnswerTime) != 0.0)
                        score = (double)((totalAnswers / playerResults.correctAnswerCount) / playerResults.averageAnswerTime);
                    else score = 0.0;
                    resultsReport += "Username: " + playerResults.username + " Average Global Score Is: " + score.ToString() + "\n";
                }

                MessageBox.Show(resultsReport, "[Trivia] Game Results Report", MessageBoxButton.OK, MessageBoxImage.Information);
                this.Close();
                this.mainWindow.Show();
            }
            else
            {
                this.getResultsBackgroundWorker.RunWorkerAsync();
            }
        }

        private void getResultsLoop_DoWork(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (this.getResultsBackgroundWorker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                this.getResultsBackgroundWorker.ReportProgress(0);
                Thread.Sleep(3000);
            }
        }

        private void getResultsLoop_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            this.getResults();
        }

        private void getResultsLoop_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                // MessageBox.Show("BackgroundWorker canceled");
            }
            else
            {
                // MessageBox.Show("BackgroundWorker ended successfully");
            }
        }
    }
}
