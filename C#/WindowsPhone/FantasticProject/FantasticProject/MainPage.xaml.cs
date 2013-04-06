using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using FantasticProject.Resources;
using FantasticProject.Utils;

namespace FantasticProject
{
    public partial class MainPage : PhoneApplicationPage
    {
        // project class
        public class FantasticProject
        {
            public string ProjectName { get; set; }
            public string ProjectDescription { get; set; }
        }

        private List<FantasticProject> projects = null;
        public List<FantasticProject> Projects
        {
            get
            {
                if (projects == null)
                {
                    projects = new List<FantasticProject>();
                    // add more project pages here
                    projects.Add(new FantasticProject
                    {
                        ProjectName = "ColorfulButton",
                        ProjectDescription = "Button can change its color when pressing and releasing; " +
                                             "Demo of basic use of VisualStateManager and Animations"
                    });
                    projects.Add(new FantasticProject
                    {
                        ProjectName = "MoreDetailButton",
                        ProjectDescription = "Customized UserControl to show more details; " +
                                             "better used transition and state"
                    });
                    projects.Add(new FantasticProject
                    {
                        ProjectName = "HighlightText",
                        ProjectDescription = "Using UserControl to composite HighlightTextBlock; " +
                                             "Very useful for searching"
                    });
                    projects.Add(new FantasticProject
                    {
                        ProjectName = "Box2DDemo",
                        ProjectDescription = "First Demo for using Box2D on windows phone 8; " +
                                             "WinPRT used"
                    });
                    projects.Add(new FantasticProject
                    {
                        ProjectName = "Box2DD3DDemo",
                        ProjectDescription = "Using D3D native code to demo Box2D physical engine " +
                                             "WinPRT and D3D used"
                    });
                }
                return projects;
            }
        }

        // Constructor
        public MainPage()
        {
            InitializeComponent();

            ProjectList.DataContext = this;

            // Sample code to localize the ApplicationBar
            //BuildLocalizedApplicationBar();
        }

        private void ProjectList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            FantasticDebugger.Log();
            if (ProjectList.SelectedItem != null)
            {
                FantasticProject project = (sender as ListBox).SelectedItem as FantasticProject;
                NavigateToProjectPage(project.ProjectName);
            }
            ProjectList.SelectedItem = null;
        }

        private void NavigateToProjectPage(string projectName)
        {
            FantasticDebugger.Log();
            if (projectName != null)
            {
                string projectPageName = "/Projects/" + projectName + ".xaml";
                FantasticDebugger.Log("ProjectPageName: " + projectPageName);
                NavigationService.Navigate(new Uri(projectPageName, UriKind.Relative));
            }
        }

        // Sample code for building a localized ApplicationBar
        //private void BuildLocalizedApplicationBar()
        //{
        //    // Set the page's ApplicationBar to a new instance of ApplicationBar.
        //    ApplicationBar = new ApplicationBar();

        //    // Create a new button and set the text value to the localized string from AppResources.
        //    ApplicationBarIconButton appBarButton = new ApplicationBarIconButton(new Uri("/Assets/AppBar/appbar.add.rest.png", UriKind.Relative));
        //    appBarButton.Text = AppResources.AppBarButtonText;
        //    ApplicationBar.Buttons.Add(appBarButton);

        //    // Create a new menu item with the localized string from AppResources.
        //    ApplicationBarMenuItem appBarMenuItem = new ApplicationBarMenuItem(AppResources.AppBarMenuItemText);
        //    ApplicationBar.MenuItems.Add(appBarMenuItem);
        //}
    }
}