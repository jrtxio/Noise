// MainWindow.xaml.cpp
#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include "StoryListPage.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::NoiseBackendExample::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        
        // Set window title
        Title(L"Hacker News - NoiseBackendExample");
        
        // Navigate to story list page
        ContentFrame().Navigate(xaml_typename<NoiseBackendExample::StoryListPage>());
    }

    void MainWindow::InitializeComponent()
    {
        MainWindowT::InitializeComponent();
    }
}
