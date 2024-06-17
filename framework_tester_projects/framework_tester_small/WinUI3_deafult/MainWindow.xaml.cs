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

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace WinUI3_deafult
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        public MainWindow()
        {
            this.InitializeComponent();
            IntPtr hWnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
            WindowId myWndId = Microsoft.UI.Win32Interop.GetWindowIdFromWindow(hWnd);
            AppWindow m_appWindow = AppWindow.GetFromWindowId(myWndId);

            m_appWindow.Resize(new Windows.Graphics.SizeInt32 { Width = 100, Height = 100 });
            m_appWindow.SetPresenter(AppWindowPresenterKind.Overlapped);
            m_appWindow.TitleBar.ExtendsContentIntoTitleBar = true;
            m_appWindow.Move(new Windows.Graphics.PointInt32 { X = -10, Y = -32 });

            var presenter = m_appWindow.Presenter as OverlappedPresenter;
            if (presenter != null)
            {
                presenter.IsMinimizable = false;
                presenter.IsMaximizable = false;
                presenter.IsResizable = false;
                presenter.IsAlwaysOnTop = false;
                presenter.SetBorderAndTitleBar(false, false);
            }
        }

        private void onClick(object sender, RoutedEventArgs e)
        {
            background.Background = new SolidColorBrush(Microsoft.UI.Colors.White);
        }

        private void onRelease(object sender, RoutedEventArgs e)
        {
            background.Background = new SolidColorBrush(Microsoft.UI.Colors.Black);
        }
    }
}
