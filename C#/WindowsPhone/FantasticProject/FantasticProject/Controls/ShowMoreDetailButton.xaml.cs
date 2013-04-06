using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using FantasticProject.Utils;

namespace FantasticProject.Controls
{
    public partial class ShowMoreDetailButton : UserControl
    {
        #region DependencyProperties
        // text content of button
        public static readonly DependencyProperty ContentTextProperty =
            DependencyProperty.Register("ContentText",
            typeof(string),
            typeof(ShowMoreDetailButton),
            new PropertyMetadata("ShowMoreDetailButton", null));

        // detail text of button
        public static readonly DependencyProperty DetailTextProperty =
            DependencyProperty.Register("None",
            typeof(string),
            typeof(ShowMoreDetailButton),
            new PropertyMetadata(String.Empty, null));

        #endregion

        #region MyRegion
        public string ContentText
        {
            get { return (string)GetValue(ContentTextProperty); }
            set { SetValue(ContentTextProperty, value); }
        }
        public string DetailText
        {
            get { return (string)GetValue(DetailTextProperty); }
            set { SetValue(DetailTextProperty, value); }
        }
        #endregion

        public ShowMoreDetailButton()
        {
            InitializeComponent();
            // set default state
            VisualStateManager.GoToState(this, "NotExpend", false);
            InitializeEventHandlers();
        }

        private void InitializeEventHandlers()
        {
            DetailButton.Checked += (sender, args) =>
            {
                bool result;
                result = VisualStateManager.GoToState(this, "Expend", true);
                FantasticDebugger.Log("GoToState Expend: " + result);
            };

            DetailButton.Unchecked += (sender, args) =>
            {
                bool result;
                result = VisualStateManager.GoToState(this, "NotExpend", true);
                FantasticDebugger.Log("GoToState NotExpend: " + result);
            };
        }

        protected override Size MeasureOverride(Size availableSize)
        {
            Size compositeSize = new Size();
            UIElement contentChild = (Content as UIElement);
            contentChild.Measure(availableSize);
            compositeSize.Width = contentChild.DesiredSize.Width;
            compositeSize.Height = contentChild.DesiredSize.Height;
            return compositeSize;
        }

        protected override Size ArrangeOverride(Size finalSize)
        {
            (Content as UIElement).Arrange(new Rect(0, 0, finalSize.Width, finalSize.Height));
            return base.ArrangeOverride(finalSize);
        }

    #region Callbacks of DependencyProperties
	#endregion
    }
}
