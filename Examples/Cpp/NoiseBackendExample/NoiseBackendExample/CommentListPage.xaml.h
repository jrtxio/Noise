// CommentListPage.xaml.h
#pragma once

#include "CommentListPage.g.h"
#include "ViewModel.hpp"

namespace winrt::NoiseBackendExample::implementation
{
    // Comment item for data binding
    struct CommentItem : winrt::implements<CommentItem, winrt::Windows::Foundation::IInspectable>
    {
        CommentItem(winrt::hstring author, winrt::hstring timestamp, winrt::hstring text)
            : m_author(author), m_timestamp(timestamp), m_text(text) {}

        winrt::hstring Author() { return m_author; }
        winrt::hstring Timestamp() { return m_timestamp; }
        winrt::hstring Text() { return m_text; }

    private:
        winrt::hstring m_author;
        winrt::hstring m_timestamp;
        winrt::hstring m_text;
    };

    struct CommentListPage : CommentListPageT<CommentListPage>
    {
        CommentListPage();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> Comments();
        void BackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, 
                             winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    protected:
        void OnNavigatedTo(winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);

    private:
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> m_comments;
        std::shared_ptr<::NoiseBackendExample::ViewModel> m_viewModel;
        uint64_t m_storyId = 0;
        
        void LoadComments();
    };
}

namespace winrt::NoiseBackendExample::factory_implementation
{
    struct CommentListPage : CommentListPageT<CommentListPage, implementation::CommentListPage>
    {
    };
}
