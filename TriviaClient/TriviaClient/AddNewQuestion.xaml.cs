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
    /// Interaction logic for AddNewQuestion.xaml
    /// </summary>
    public partial class AddNewQuestion : Window
    {
        private MainWindow mainWindow;

        public AddNewQuestion(MainWindow mainWindow)
        {
            this.mainWindow = mainWindow;

            InitializeComponent();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            this.mainWindow.Show();
            this.Close();
        }

        private void SubmitButton_Click(object sender, RoutedEventArgs e)
        {
            string[] answers = { this.CorrectAnswerTextBox.Text, this.WrongAnswer1TextBox.Text, this.WrongAnswer2TextBox.Text, this.WrongAnswer3TextBox.Text };

            if
            (
                string.IsNullOrWhiteSpace(this.QuestionTextBox.Text) ||
                string.IsNullOrWhiteSpace(answers[0]) ||
                string.IsNullOrWhiteSpace(answers[1]) ||
                string.IsNullOrWhiteSpace(answers[2]) ||
                string.IsNullOrWhiteSpace(answers[3]) ||
                (answers.GroupBy(s => s).Any(g => g.Count() >= 2))
            )
            {
                MessageBox.Show("Not all fields are filled!", "[Trivia] Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            AddNewQuestionRequest addNewQuestionRequest = new AddNewQuestionRequest(this.QuestionTextBox.Text, answers[0], answers[1], answers[2], answers[3]);
            addNewQuestionRequest.SendToServer(this.mainWindow.clientStream);
            AddNewQuestionRequest.AddNewQuestionResponse addNewQuestionResponse = addNewQuestionRequest.GetFromServer(this.mainWindow.clientStream);

            if ((uint)(Cods.Status.ADD_NEW_QUESTION_STATUS) == addNewQuestionResponse.status)
            {
                MessageBox.Show("The question have been added successfully!", "[Trivia] Success", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                this.QuestionTextBox.Text = "";
                this.CorrectAnswerTextBox.Text = "";
                this.WrongAnswer1TextBox.Text = "";
                this.WrongAnswer2TextBox.Text = "";
                this.WrongAnswer3TextBox.Text = "";
                return;
            }
            else
            {
                MessageBox.Show("The question already exists in the questions repository!", "[Trivia] Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
        }
    }
}
