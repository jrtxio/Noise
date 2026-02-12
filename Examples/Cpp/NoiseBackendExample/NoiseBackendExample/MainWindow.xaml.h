#pragma once

#include "MainWindow.g.h"
#include <winrt/Microsoft.UI.Dispatching.h>

#include <string>
#include <vector>
#include <memory>

// Forward declarations to avoid Chez Scheme header conflicts with WinRT.
namespace HN {
    struct Comment;
    struct Story;
    class HNBackend;
}

namespace winrt::NoiseBackendExample::implementation
{
    // View model for story items in the ListView.
    struct StoryViewModel {
        uint64_t Id;
        winrt::hstring Title;
        winrt::hstring CommentCount;

        StoryViewModel(uint64_t id, winrt::hstring title, size_t count)
            : Id(id), Title(std::move(title)), CommentCount(winrt::to_hstring(count)) {}
    };

    // View model for comment items in the ListView.
    struct CommentViewModel {
        uint64_t Id;
        winrt::hstring Author;
        winrt::hstring Timestamp;
        winrt::hstring Text;

        CommentViewModel(uint64_t id, winrt::hstring author,
                         winrt::hstring ts, winrt::hstring text)
            : Id(id), Author(std::move(author)), Timestamp(std::move(ts)), Text(std::move(text)) {}
    };

    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();
        ~MainWindow();

        void OnStorySelected(winrt::Windows::Foundation::IInspectable const& sender,
                             winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& args);
        void OnCommentDoubleTapped(winrt::Windows::Foundation::IInspectable const& sender,
                                   winrt::Microsoft::UI::Xaml::Input::DoubleTappedRoutedEventArgs const& args);
        void OnBackClicked(winrt::Windows::Foundation::IInspectable const& sender,
                           winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        std::unique_ptr<HN::HNBackend> backend_;
        std::vector<StoryViewModel> stories_;
        std::vector<CommentViewModel> comments_;
        std::vector<uint64_t> commentStack_;

        winrt::Microsoft::UI::Dispatching::DispatcherQueue dispatcherQueue_{ nullptr };

        void InitBackend();
        void LoadStories();
        void LoadComments(uint64_t itemId);
        void UpdateBackButton();
    };
}

namespace winrt::NoiseBackendExample::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
