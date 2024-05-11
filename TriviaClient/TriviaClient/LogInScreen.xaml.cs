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
            else if (string.IsNullOrWhiteSpace(this.UsernameTextBox.Text) || string.IsNullOrWhiteSpace(this.PasswordTextBox.Password))
            {
                MessageBox.Show("Invalid Credentials!", "[Trivia] Error", MessageBoxButton.OK, icon: MessageBoxImage.Error);
                return;
            }

            try
            {

                loginRequest.username = $@"liam";
                loginRequest.password = $@"1Aa@";
                loginRequest.SendToServer(mainWindow.clientStream);
                if ((Cods.Status)(loginRequest.GetFromServer(mainWindow.clientStream).status) == Cods.Status.LOGIN_STATUS)
                {
                    this.mainWindow.username = this.UsernameTextBox.Text;
                    this.mainWindow.isUserLogged = true;
                    this.mainWindow.HelloLabel.Content = "Hello, " + this.mainWindow.username;
                    this.mainWindow.CreateRoomButton.IsEnabled = true;
                    this.mainWindow.JoinRoomButton.IsEnabled = true;
                    this.mainWindow.LogOutButton.Visibility = Visibility.Visible;
                    this.mainWindow.LogOutButton.IsEnabled = true;
                    this.mainWindow.StatsMenuButton.IsEnabled = true;
                    this.Close();
                    this.mainWindow.Show();

                    var button = (Button)(this.mainWindow.FindName("LogInButton"));
                    if (button != null)
                    {
                        button.Visibility = Visibility.Collapsed;
                    }

                    button = (Button)(this.mainWindow.FindName("SignUpButton"));
                    if (button != null)
                    {
                        button.Visibility = Visibility.Collapsed;
                    }
                }
                //string msg =$@"{{'username': '{this.username}', 'password': '{this.password}'}}";
            }
            catch (Exception ex)
            {
                MessageBox.Show("Login failed!", "[LogIn] Error", MessageBoxButton.OK, icon: MessageBoxImage.Error);
            }
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
