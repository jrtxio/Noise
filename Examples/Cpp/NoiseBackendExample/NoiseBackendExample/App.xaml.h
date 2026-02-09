// App.xaml.h
#pragma once

#include "App.xaml.g.h"

namespace winrt::NoiseBackendExample::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}

namespace winrt::NoiseBackendExample::factory_implementation
{
    struct App : AppT<App, implementation::App>
    {
    };
}
