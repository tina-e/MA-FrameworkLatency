#pragma once

#include "MainWindow.g.h"

namespace winrt::WinUI_default::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WinUI_default::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
//
//#pragma once
//
//#include "MainWindow.g.h"
//
//namespace winrt::winui3_app::implementation
//{
//    struct MainWindow : MainWindowT<MainWindow>
//    {
//        MainWindow();
//        void BackgroundBorder_PointerPressed(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
//    };
//}
//
//namespace winrt::winui3_app::factory_implementation
//{
//    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
//    {
//    };
//}
//
