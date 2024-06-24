#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    init_apartment();
    Application::Start([](auto&&)
        {
            auto textBlock = Controls::TextBlock();
            textBlock.Text(L"Hello, World!");

            auto window = Window();
            window.Content(textBlock);

            window.Activate();
        });

    return 0;
}
