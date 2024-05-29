using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Microsoft.UI;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Media.Imaging;
using Microsoft.UI.Xaml.Navigation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using WinRT.Interop;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace WinUI3_image
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        ImageBrush imageBrush;
        public MainWindow()
        {
            this.InitializeComponent();

            string imagePath = "ms-appx:///Assets/noise.png";
            BitmapImage bitmapImage = new BitmapImage(new Uri(imagePath));
            imageBrush = new ImageBrush();
            imageBrush.ImageSource = bitmapImage;

            IntPtr hWnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
            WindowId myWndId = Microsoft.UI.Win32Interop.GetWindowIdFromWindow(hWnd);
            AppWindow m_appWindow = AppWindow.GetFromWindowId(myWndId);
            m_appWindow.SetPresenter(AppWindowPresenterKind.FullScreen);
        }

        private void onClick(object sender, RoutedEventArgs e)
        {            
            background.Background = imageBrush;
        }

        private void onRelease(object sender, RoutedEventArgs e)
        {
            background.Background = new SolidColorBrush(Microsoft.UI.Colors.Black);
        }
    }
}
