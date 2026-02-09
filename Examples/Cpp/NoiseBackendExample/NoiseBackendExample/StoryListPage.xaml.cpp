// StoryListPage.xaml.cpp
#include "pch.h"
#include "StoryListPage.xaml.h"
#if __has_include("StoryListPage.g.cpp")
#include "StoryListPage.g.cpp"
#endif
#include "CommentListPage.xaml.h"
#include "NoiseBoot_Windows/NoiseBoot.hpp"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Foundation::Collections;

namespace winrt::NoiseBackendExample::implementation
{
    StoryListPage::StoryListPage()
    {
        InitializeComponent();
        
        m_stories = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>();
        
        // Initialize Noise backend
        Noise::NoiseBoot::boot();
        
        // Get resource path
        auto exePath = std::filesystem::current_path();
        auto resPath = exePath / "res";
        
        // Create ViewModel
        auto dispatcher = Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();
        m_viewModel = std::make_shared<::NoiseBackendExample::ViewModel>(resPath, dispatcher);
        
        // Load stories
        LoadStories();
    }

    IObservableVector<Windows::Foundation::IInspectable> StoryListPage::Stories()
    {
        return m_stories;
    }

    void StoryListPage::LoadStories()
    {
        LoadingRing().IsActive(true);
        
        m_viewModel->fetchTopStories([this](const std::vector<::NoiseBackendExample::Story>& stories) {
            m_stories.Clear();
            
            for (const auto& story : stories) {
                auto title = winrt::to_hstring(story.title);
                auto item = winrt::make<StoryItem>(story.id, title, story.comments.size());
                m_stories.Append(item);
            }
            
            LoadingRing().IsActive(false);
        });
    }

    void StoryListPage::StoryListView_ItemClick(Windows::Foundation::IInspectable const& sender,
                                                  ItemClickEventArgs const& e)
    {
        auto item = e.ClickedItem().as<StoryItem>();
        uint64_t storyId = item->Id();
        
        // Navigate to comment list page
        Frame().Navigate(xaml_typename<NoiseBackendExample::CommentListPage>(), 
                        winrt::box_value(storyId));
    }
}
