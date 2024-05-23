#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI_default::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}

//#include "pch.h"
//#include "MainWindow.xaml.h"
//#include <winrt/Microsoft.UI.Xaml.Media.h>
//
//using namespace winrt;
//using namespace Microsoft::UI::Xaml;
//using namespace Microsoft::UI::Xaml::Controls;
//using namespace Microsoft::UI::Xaml::Input;
//using namespace Microsoft::UI::Xaml::Media;
//using namespace winui3_app::implementation;
//
//MainWindow::MainWindow()
//{
//    InitializeComponent();
//}
//
//void MainWindow::BackgroundBorder_PointerPressed(IInspectable const& sender, PointerRoutedEventArgs const&)
//{
//    auto border = sender.as<Border>();
//    if (border)
//    {
//        SolidColorBrush brush = border.Background().as<SolidColorBrush>();
//        if (brush.Color() == Windows::UI::Colors::Black())
//        {
//            border.Background(SolidColorBrush(Windows::UI::Colors::White()));
//        }
//        else
//        {
//            border.Background(SolidColorBrush(Windows::UI::Colors::Black()));
//        }
//    }
//}

