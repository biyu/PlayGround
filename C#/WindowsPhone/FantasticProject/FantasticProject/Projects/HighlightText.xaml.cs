using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;

namespace FantasticProject.Projects
{
    public partial class HighlightText : PhoneApplicationPage
    {
        public HighlightText()
        {
            InitializeComponent();
        }

        private void SearchTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            ResultTextBlock.HighlightText = (sender as TextBox).Text;
        }
    }
}