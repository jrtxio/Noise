// MainWindow.xaml.h
#pragma once

#include "MainWindow.g.h"

namespace winrt::NoiseBackendExample::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void InitializeComponent();
    };
}

namespace winrt::NoiseBackendExample::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
