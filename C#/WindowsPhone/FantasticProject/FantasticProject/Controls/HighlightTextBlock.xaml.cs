using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Windows.Media;
using FantasticProject.Utils;
using System.Windows.Documents;

namespace FantasticProject.Controls
{
    public partial class HighlightTextBlock : UserControl
    {
        #region DependencyProperties

        // original text for text block
        public static readonly DependencyProperty TextProperty =
            DependencyProperty.Register("Text",
            typeof(string),
            typeof(HighlightTextBlock),
            new PropertyMetadata(String.Empty, OnTextPropertyChanged));

        public static readonly DependencyProperty HighlightTextProperty = 
            DependencyProperty.Register("HighlightText",
            typeof(string),
            typeof(HighlightTextBlock),
            new PropertyMetadata(String.Empty, OnHighlightTextPropertyChanged));

        public static readonly DependencyProperty HighlightBrushProperty =
            DependencyProperty.Register("HighlightBrush",
            typeof(SolidColorBrush),
            typeof(HighlightTextBlock),
            new PropertyMetadata(new SolidColorBrush(Colors.Blue)));

        public static readonly DependencyProperty TextAlignmentProperty =
            DependencyProperty.Register("TextAlignment",
            typeof(TextAlignment),
            typeof(HighlightTextBlock),
            new PropertyMetadata(TextAlignment.Left));

        #endregion

        #region Properties

        public string Text
        {
            get { return (string)GetValue(TextProperty); }
            set { SetValue(TextProperty, value); }
        }

        public string HighlightText
        {
            get { return (string)GetValue(HighlightTextProperty); }
            set { SetValue(HighlightTextProperty, value); }
        }

        public SolidColorBrush HighlightBrush
        {
            get { return (SolidColorBrush)GetValue(HighlightBrushProperty); }
            set { SetValue(HighlightBrushProperty, value); }
        }

        public TextAlignment TextAlignment
        {
            get { return (TextAlignment)GetValue(TextAlignmentProperty); }
            set { SetValue(TextAlignmentProperty, value); }
        }

        #endregion

        public HighlightTextBlock()
        {
            InitializeComponent();

            VisualStateManager.GoToState(this, "NotHighlight", false);
        }

        private string[] SearchLogic(string text, string searchText)
        {
            FantasticDebugger.Log();
            List<string> resultText = new List<string>();
            if (searchText != String.Empty)
            {
                string curString = text;
                while (true)
                {
                    int foundIndex = 0;
                    // find index of search string
                    foundIndex = curString.ToLower().IndexOf(searchText.ToLower());
                    // search string exists
                    if (foundIndex != -1)
                    {
                        string previousStr = String.Empty;
                        previousStr = curString.Substring(0, foundIndex);
                        if (previousStr != String.Empty)
                        {
                            // push previous part into result list
                            resultText.Add(previousStr);
                        }
                        // push search string into result list
                        resultText.Add(curString.Substring(foundIndex, searchText.Count()));
                        // iterate next
                        curString = curString.Substring(foundIndex + searchText.Count());
                    }
                    else
                    {
                        // push rest substring into result list
                        resultText.Add(curString);
                        break;
                    }
                }
            }
            return resultText.ToArray<string>();
        }

        private void CompositeTextRuns(string[] stringList)
        {
            // first clear text inlines
            HighlightedText.Inlines.Clear();
            for (int i = 0; i < stringList.Length; i++)
            {
                string subText = stringList[i];
                Run childRun = new Run();
                childRun.Text = subText;
                if (subText.ToLower() == HighlightText.ToLower())
                {
                    childRun.Foreground = HighlightBrush;
                }
                HighlightedText.Inlines.Add(childRun);
            }
        }

        #region PropertyChangeHandlers

        private static void OnTextPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            FantasticDebugger.Log();
        }

        private static void OnHighlightTextPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is HighlightTextBlock)
            {
                HighlightTextBlock self = d as HighlightTextBlock;
                string searchText = (string)e.NewValue;
                string text = self.Text;

                string[] results = self.SearchLogic(text, searchText);
                if (results != null && results.Count() > 0)
                {
                    self.CompositeTextRuns(results);
                }

                VisualStateManager.GoToState(self, (self.HighlightText != String.Empty) ? "Highlight" : "NotHighlight", false);
            }
            else
            {
                FantasticDebugger.Log("ERROR");
            }
        }

        #endregion
    }
}
