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
        public BackgroundWorker updateTimeAndDataBackgroundWorker;


        public GameScreen(ConnectedRoom connectedRoom)
        {
            this.updateTimeAndDataBackgroundWorker = new BackgroundWorker();

            this.updateTimeAndDataBackgroundWorker.WorkerSupportsCancellation = true;
            this.updateTimeAndDataBackgroundWorker.WorkerReportsProgress = true;

            this.updateTimeAndDataBackgroundWorker.DoWork += UpdateTimeAndDataLoop_DoWork;
            this.updateTimeAndDataBackgroundWorker.ProgressChanged += UpdateTimeAndDataLoop_ProgressChanged;
            this.updateTimeAndDataBackgroundWorker.RunWorkerCompleted += UpdateTimeAndDataLoop_RunWorkerCompleted;

            this.updateTimeAndDataBackgroundWorker.RunWorkerAsync();

            _connectedRoom = connectedRoom;
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

        private void UpdateTimeAndData()
        {

        }

        private void UpdateTimeAndDataLoop_DoWork(object sender, DoWorkEventArgs e)
        {

        }

        private void UpdateTimeAndDataLoop_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {

        }

        private void UpdateTimeAndDataLoop_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
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
