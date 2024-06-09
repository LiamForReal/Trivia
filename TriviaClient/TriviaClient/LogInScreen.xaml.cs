using Microsoft.VisualBasic;
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
    /// Interaction logic for LogInScreen.xaml
    /// </summary>
    public partial class LogInScreen : Window
    {
        public MainWindow mainWindow;
        private bool revealPassword = false;
        private LoginRequest loginRequest;
        public LogInScreen()
        {
            loginRequest = new LoginRequest("", "");
            this.revealPassword = false;
            InitializeComponent();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            this.mainWindow.Show();
        }

        private void LogInButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.mainWindow.isUserLogged)
            {
                MessageBox.Show("There Is A User That Is Already Logged!", "[Trivia] Error", MessageBoxButton.OK, icon: MessageBoxImage.Error);
                return;
            }
            else if ((!this.revealPassword && (string.IsNullOrWhiteSpace(this.UsernameTextBox.Text) || string.IsNullOrWhiteSpace(this.PasswordTextBox.Password))) ||
                (this.revealPassword && (string.IsNullOrWhiteSpace(this.UsernameTextBox.Text) || string.IsNullOrWhiteSpace(this.RevealedTextBox.Text)))
            )
            {
                MessageBox.Show("Invalid Credentials!", "[Trivia] Error", MessageBoxButton.OK, icon: MessageBoxImage.Error);
                this.PasswordTextBox.Password = "";
                this.UsernameTextBox.Text = "";
                this.RevealedTextBox.Text = "";
                return;
            }

            loginRequest.username = this.UsernameTextBox.Text;
            if (this.revealPassword)
            {
                loginRequest.password = this.RevealedTextBox.Text;
            }
            else
            {
                loginRequest.password = this.PasswordTextBox.Password;
            }

            loginRequest.SendToServer(mainWindow.clientStream);

            Cods.Status res = (Cods.Status)(loginRequest.GetFromServer(mainWindow.clientStream).status);

            if (res == Cods.Status.LOGIN_STATUS)
            {
                this.mainWindow.username = this.UsernameTextBox.Text;
                this.mainWindow.isUserLogged = true;
                this.mainWindow.HelloLabel.Content = "Hello, " + this.mainWindow.username;
                this.mainWindow.CreateRoomButton.IsEnabled = true;
                this.mainWindow.JoinRoomButton.IsEnabled = true;
                this.mainWindow.LogOutButton.Visibility = Visibility.Visible;
                this.mainWindow.LogOutButton.IsEnabled = true;
                this.mainWindow.StatsMenuButton.IsEnabled = true;
                this.mainWindow.LogInButton.Visibility = Visibility.Collapsed;
                this.Close();
                this.mainWindow.Show();


                var button = (Button)(this.mainWindow.FindName("SignUpButton"));
                if (button != null)
                {
                    button.Visibility = Visibility.Collapsed;
                }
            }
            else MessageBox.Show("[LogIn] error!");
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