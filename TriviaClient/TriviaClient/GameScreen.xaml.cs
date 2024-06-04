using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net.Sockets;
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
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for GameScreen.xaml
    /// </summary>
    public partial class GameScreen : Window
    {
        public MainWindow mainWindow;
        public ConnectedRoom _connectedRoom;
        public FinishWaitingRoom finishWaitingRoom;

        // public BackgroundWorker updateDataBackgroundWorker;

        private System.Windows.Threading.DispatcherTimer timer;

        private bool isFinished;
        private uint timeLeftForQuestion;

        private uint questionsAmount;
        private uint timePerQuestion;

        public GameScreen(ConnectedRoom connectedRoom, MainWindow mainWindow, uint questionsAmount, uint timePerQuestion)
        {
            //this.updateDataBackgroundWorker = new BackgroundWorker();
            this.mainWindow = mainWindow;

            //this.updateDataBackgroundWorker.WorkerSupportsCancellation = true;
            //this.updateDataBackgroundWorker.WorkerReportsProgress = true;

            //this.updateDataBackgroundWorker.DoWork += UpdateDataLoop_DoWork;
            //this.updateDataBackgroundWorker.ProgressChanged += UpdateDataLoop_ProgressChanged;
            //this.updateDataBackgroundWorker.RunWorkerCompleted += UpdateDataLoop_RunWorkerCompleted;

            //this.updateDataBackgroundWorker.RunWorkerAsync();

            this.isFinished = false;

            this.questionsAmount = questionsAmount;
            this.timePerQuestion = timePerQuestion;

            this.timeLeftForQuestion = this.timePerQuestion;

            this.timer = new System.Windows.Threading.DispatcherTimer();

            this.timer.Interval = new TimeSpan(0, 0, 1);
            this.timer.Tick += this.timer_Tick;
            this.timer.Start();

            _connectedRoom = connectedRoom;

            InitializeComponent();


            this.GetNextQuestion();

            this.TimeLeftLabel.Content = this.timeLeftForQuestion.ToString();
        }

        private List<string> Shuffle(List<string> items)
        {
            return items.Distinct().OrderBy(x => System.Guid.NewGuid().ToString()).ToList();
        }

        private void GetNextQuestion()
        {
            this.questionsAmount--;

            if (this.questionsAmount <= 0)
            {
                this.finishWaitingRoom = new FinishWaitingRoom(this.mainWindow);
                this.timer.Stop();
                this.Close();
                this.finishWaitingRoom.Show();
            }

            this.timeLeftForQuestion = this.timePerQuestion;
            this.TimeLeftLabel.Content = this.timeLeftForQuestion.ToString();

            GetQuestionRequest getQuestionRequest = new GetQuestionRequest();
            getQuestionRequest.SendToServer(this.mainWindow.clientStream);
            GetQuestionRequest.GetQuestionResponse getQuestionResponse = getQuestionRequest.GetFromServer(this.mainWindow.clientStream);
            getQuestionResponse.answers = this.Shuffle(getQuestionResponse.answers);

            this.Answer1.Content = getQuestionResponse.answers[0];
            this.Answer2.Content = getQuestionResponse.answers[1];
            this.Answer3.Content = getQuestionResponse.answers[2];
            this.Answer4.Content = getQuestionResponse.answers[3];

            this.QuestionLabel.Content = getQuestionResponse.question;
        }

        private void Answer1_Click(object sender, RoutedEventArgs e)
        {
            this.HandleClickOnAnswer(this.Answer1.Content.ToString());
        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {
            this.HandleClickOnAnswer(this.Answer2.Content.ToString());
        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {
            this.HandleClickOnAnswer(this.Answer3.Content.ToString());
        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {
            this.HandleClickOnAnswer(this.Answer4.Content.ToString());
        }

        private void HandleClickOnAnswer(string answer)
        {
            SubmitAnswerRequest submitAnswerRequest = new SubmitAnswerRequest(answer);
            submitAnswerRequest.SendToServer(this.mainWindow.clientStream);
            SubmitAnswerRequest.SubmitAnswerResponse submitAnswerResponse = submitAnswerRequest.GetFromServer(this.mainWindow.clientStream);

            if ((uint)(Cods.Status.SUBMIT_ANSWER_CORRECT) == submitAnswerResponse.status || (uint)(Cods.Status.SUBMIT_ANSWER_WRONG) == submitAnswerResponse.status)
            {
                this.GetNextQuestion();
            }
        }

        /*private void UpdateData()
        {
            if (this.isFinished)
            {
                this.updateDataBackgroundWorker.CancelAsync();
            }


        }*/
        
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

        /*private void UpdateDataLoop_DoWork(object sender, DoWorkEventArgs e)
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
    */
    }
}
