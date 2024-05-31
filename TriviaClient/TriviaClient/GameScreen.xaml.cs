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
    /// Interaction logic for GameScreen.xaml
    /// </summary>
    public partial class GameScreen : Window
    {
        public ConnectedRoom _connectedRoom;
        public BackgroundWorker updateDataBackgroundWorker;

        private System.Windows.Threading.DispatcherTimer timer;

        private bool isFinished;
        private uint currentQuestion;
        private uint timeLeftForQuestion;

        private uint questionsAmount;
        private uint timePerQuestion;


        public GameScreen(ConnectedRoom connectedRoom, uint questionsAmount, uint timePerQuestion)
        {
            this.updateDataBackgroundWorker = new BackgroundWorker();

            this.updateDataBackgroundWorker.WorkerSupportsCancellation = true;
            this.updateDataBackgroundWorker.WorkerReportsProgress = true;

            this.updateDataBackgroundWorker.DoWork += UpdateDataLoop_DoWork;
            this.updateDataBackgroundWorker.ProgressChanged += UpdateDataLoop_ProgressChanged;
            this.updateDataBackgroundWorker.RunWorkerCompleted += UpdateDataLoop_RunWorkerCompleted;

            this.updateDataBackgroundWorker.RunWorkerAsync();

            this.isFinished = false;
            this.currentQuestion = 1;

            this.questionsAmount = questionsAmount;
            this.timePerQuestion = timePerQuestion;

            this.timeLeftForQuestion = this.timePerQuestion;

            this.timer = new System.Windows.Threading.DispatcherTimer();

            this.timer.Interval = new TimeSpan(0, 0, 1);
            this.timer.Tick += this.timer_Tick;
            this.timer.Start();

            _connectedRoom = connectedRoom;

            InitializeComponent();

            this.TimeLeftLabel.Content = this.timeLeftForQuestion.ToString();

        }

        private void Answer1_Click(object sender, RoutedEventArgs e)
        {
            this.HandleClickOnAnswer();
        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {
            this.HandleClickOnAnswer();
        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {
            this.HandleClickOnAnswer();
        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {
            this.HandleClickOnAnswer();
        }

        private void HandleClickOnAnswer()
        {

        }

        private void UpdateData()
        {
            if (this.isFinished)
            {
                this.updateDataBackgroundWorker.CancelAsync();
            }


        }
        
        private void timer_Tick(object sender, EventArgs e)
        {
            this.timeLeftForQuestion--;

            if (this.timeLeftForQuestion <= 3)
            {
                this.TimeLeftLabel.Foreground = new SolidColorBrush(Colors.Red);
            }
            else if (this.timeLeftForQuestion <= 5)
            {
                this.TimeLeftLabel.Foreground = new SolidColorBrush(Colors.Orange);
            }
            else if (this.timeLeftForQuestion <= 10)
            {
                this.TimeLeftLabel.Foreground = new SolidColorBrush(Colors.Yellow);
            }
            else
            {
                this.TimeLeftLabel.Foreground = new SolidColorBrush(Colors.Aqua);
            }

            this.TimeLeftLabel.Content = this.timeLeftForQuestion.ToString();

        }

        private void UpdateDataLoop_DoWork(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (this.updateDataBackgroundWorker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                this.updateDataBackgroundWorker.ReportProgress(0);
                Thread.Sleep(1000);
            }
        }

        private void UpdateDataLoop_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            this.UpdateData();
        }

        private void UpdateDataLoop_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                // MessageBox.Show("BackgroundWorker cancelled");
            }
            else
            {
                // MessageBox.Show("BackgroundWorker ended successfully");
            }
        }
    }
}
