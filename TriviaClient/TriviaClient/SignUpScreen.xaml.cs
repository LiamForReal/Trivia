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
    /// Interaction logic for SignUpScreen.xaml
    /// </summary>
    public partial class SignUpScreen : Window
    {
        public MainWindow mainWindow;
        private bool revealPassword = false;
        private SignupRequest request;
        public SignUpScreen()
        {
            request = new SignupRequest("", "", "");
            this.revealPassword = false;
            InitializeComponent();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            this.mainWindow.Show();
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            if ((!this.revealPassword && (string.IsNullOrWhiteSpace(this.UsernameTextBox.Text) || string.IsNullOrWhiteSpace(this.PasswordTextBox.Password)) ) ||
                (this.revealPassword && (string.IsNullOrWhiteSpace(this.UsernameTextBox.Text) || string.IsNullOrWhiteSpace(this.RevealedTextBox.Text)) ) ||
                string.IsNullOrWhiteSpace(this.EmailTextBox.Text)
            )
            {
                MessageBox.Show("Invalid Credentials!", "[Trivia] Error", MessageBoxButton.OK, icon: MessageBoxImage.Error);
                this.PasswordTextBox.Password = "";
                this.UsernameTextBox.Text = "";
                this.RevealedTextBox.Text = "";
                return;
            }
            request.username = this.UsernameTextBox.Text;
            request.email = this.EmailTextBox.Text;
            if (this.revealPassword)
            {
                request.password = this.RevealedTextBox.Text;
            }
            else
            {
                request.password = this.PasswordTextBox.Password;
            }

            request.SendToServer(mainWindow.clientStream);

            Cods.Status res = (Cods.Status)(request.GetFromServer(mainWindow.clientStream).status);

            if (res == Cods.Status.SIGNUP_STATUS)
            {
                this.Close();
                this.mainWindow.Show();
                MessageBox.Show("[SignUp] successfully!");
            } else  MessageBox.Show("[SignUp] error!");
        }
        private void RevealPasswordButton_Click(object sender, RoutedEventArgs e)
        {
            revealPassword = !revealPassword;

            if (revealPassword)
            {
                this.RevealedTextBox.Text = this.PasswordTextBox.Password;
                this.RevealedTextBox.Visibility = Visibility.Visible;
                this.PasswordTextBox.Visibility = Visibility.Collapsed;

                this.ShowPasswordImage.Source = new BitmapImage(new Uri(@"../Resources/hide_password.png", UriKind.Relative));

            }
            else
            {
                this.PasswordTextBox.Password = this.RevealedTextBox.Text;
                this.PasswordTextBox.Visibility = Visibility.Visible;
                this.RevealedTextBox.Visibility = Visibility.Collapsed;

                this.ShowPasswordImage.Source = new BitmapImage(new Uri(@"../Resources/show_password.png", UriKind.Relative));
            }
        }
    }
}
