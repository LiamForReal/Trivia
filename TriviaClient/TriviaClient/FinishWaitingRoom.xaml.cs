using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using TriviaClient;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for FinishWaitingRoom.xaml
    /// </summary>
    /// 
    public class PlayerResultsDataObject
    {
        public string username { get; set; }
        public string correctAnswersAmount { get; set; }
        public string wrongAnswersAmount { get; set; }

        public string averageAnswerTime { get; set; }
    }

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
            GetGameResultsRequest getGameResultsRequest = new GetGameResultsRequest();
            getGameResultsRequest.SendToServer(this.mainWindow.clientStream);
            GetGameResultsRequest.GetGameResultsResponse getGameResultsResponse = getGameResultsRequest.GetFromServer(this.mainWindow.clientStream);

            if ((uint)(Cods.Status.GET_GAME_RESULTS_STATUS) == getGameResultsResponse.status)
            {
                this.getResultsBackgroundWorker.CancelAsync();

                this.WaitingLabel.Visibility = Visibility.Hidden;

                this.ResultsDataGrid.Visibility = Visibility.Visible;

                foreach (PlayerResults playerResults in getGameResultsResponse.results)
                {
                    this.ResultsDataGrid.Items.Add(new PlayerResultsDataObject() { username = playerResults.username, correctAnswersAmount = playerResults.correctAnswerCount.ToString(), wrongAnswersAmount = playerResults.wrongAnswerCount.ToString(), averageAnswerTime = ((double)(playerResults.averageAnswerTime)).ToString("F6") });
                }

                this.CloseButton.Visibility = Visibility.Visible;
                this.CloseButton.IsEnabled = true;
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
                Thread.Sleep(4000);
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
                //MessageBox.Show("BackgroundWorker canceled");
            }
            else
            {
                //MessageBox.Show("BackgroundWorker ended successfully");
            }
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            this.mainWindow.Show();
            this.Close();
        }
    }
}