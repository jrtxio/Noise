// StoryListPage.xaml.h
#pragma once

#include "StoryListPage.g.h"
#include "ViewModel.hpp"
#include <winrt/Windows.Foundation.Collections.h>

namespace winrt::NoiseBackendExample::implementation
{
    // Story item for data binding
    struct StoryItem : winrt::implements<StoryItem, winrt::Windows::Foundation::IInspectable>
    {
        StoryItem(uint64_t id, winrt::hstring title, uint64_t commentCount)
            : m_id(id), m_title(title), m_commentCount(commentCount) {}

        uint64_t Id() { return m_id; }
        winrt::hstring Title() { return m_title; }
        uint64_t CommentCount() { return m_commentCount; }

    private:
        uint64_t m_id;
        winrt::hstring m_title;
        uint64_t m_commentCount;
    };

    struct StoryListPage : StoryListPageT<StoryListPage>
    {
        StoryListPage();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> Stories();
        void StoryListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, 
                                      winrt::Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& e);

    private:
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> m_stories;
        std::shared_ptr<::NoiseBackendExample::ViewModel> m_viewModel;
        
        void LoadStories();
    };
}

namespace winrt::NoiseBackendExample::factory_implementation
{
    struct StoryListPage : StoryListPageT<StoryListPage, implementation::StoryListPage>
    {
    };
}
