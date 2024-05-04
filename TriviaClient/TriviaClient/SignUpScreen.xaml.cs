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
        private bool revealPassword = false;

        public SignUpScreen()
        {
            this.revealPassword = false;
            InitializeComponent();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {

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
