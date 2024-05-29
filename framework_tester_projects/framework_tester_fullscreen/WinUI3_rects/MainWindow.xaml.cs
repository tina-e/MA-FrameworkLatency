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
using Microsoft.UI.Xaml.Navigation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Microsoft.UI.Xaml.Shapes;
using Windows.UI;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace WinUI3_rects
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        int NUM_RECTS = 999;
        Random rand = new Random();

        public MainWindow()
        {
            this.InitializeComponent();
            IntPtr hWnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
            WindowId myWndId = Microsoft.UI.Win32Interop.GetWindowIdFromWindow(hWnd);
            AppWindow m_appWindow = AppWindow.GetFromWindowId(myWndId);
            m_appWindow.SetPresenter(AppWindowPresenterKind.FullScreen);
        }

        private void onClick(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < NUM_RECTS; i++)
            {
                int w = rand.Next(100, 500);
                int h = rand.Next(100, 500);
                int x = rand.Next(100, 1920 - w);
                int y = rand.Next(0, 1080 - h);
                
                byte r = (byte) rand.Next(0, 255);
                byte g = (byte) rand.Next(0, 255);
                byte b = (byte) rand.Next(0, 255);

                Rectangle rect = new Rectangle();
                rect.Width = w;
                rect.Height = h;
                rect.Fill = new SolidColorBrush(Color.FromArgb(255, r, g, b)); 
                                                                        
                Canvas.SetLeft(rect, x);
                Canvas.SetTop(rect, y);
                                         
                background.Children.Add(rect);
            }
            Rectangle whiteRect = new Rectangle();
            whiteRect.Width = 100;
            whiteRect.Height = 100;
            whiteRect.Fill = new SolidColorBrush(Microsoft.UI.Colors.White);
            Canvas.SetLeft(whiteRect, 0);
            Canvas.SetTop(whiteRect, 0);
            background.Children.Add(whiteRect);
        }

        private void onRelease(object sender, RoutedEventArgs e)
        {
            background.Children.Clear();
            background.Background = new SolidColorBrush(Microsoft.UI.Colors.Black);
        }
    }
}
