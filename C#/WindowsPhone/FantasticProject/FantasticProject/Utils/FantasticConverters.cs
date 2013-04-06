using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;

namespace FantasticProject.Utils
{
    public class BoolToVisibilityConverter : IValueConverter
    {
        /// <summary>
        /// Converts chat message color based on status (read etc)
        /// </summary>
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value is Boolean)
            {
                bool show = (bool)value;
                return show ? Visibility.Visible : Visibility.Collapsed;
            }
            else
            {
                throw new InvalidCastException("Value is not Boolen type");
            }
        }

        // No need to implement converting back on a one-way binding 
        public object ConvertBack(object value, Type targetType,
            object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
