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
        MainWindow mainWindow;

        private BackgroundWorker getResultsBackgroundWorker;


        public FinishWaitingRoom(MainWindow mainWindow)
        {
            this.mainWindow = mainWindow;

            this.getResultsBackgroundWorker = new BackgroundWorker();

            this.getResultsBackgroundWorker.WorkerSupportsCancellation = true;
            this.getResultsBackgroundWorker.WorkerReportsProgress = true;

            this.getResultsBackgroundWorker.DoWork += ;
            this.getResultsBackgroundWorker.ProgressChanged += ;
            this.getResultsBackgroundWorker.RunWorkerCompleted += ;

            this.getResultsBackgroundWorker.RunWorkerAsync();

            InitializeComponent();
        }

        private void getResults()
        {
            
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
