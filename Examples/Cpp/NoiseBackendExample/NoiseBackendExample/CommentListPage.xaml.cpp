// CommentListPage.xaml.cpp
#include "pch.h"
#include "CommentListPage.xaml.h"
#if __has_include("CommentListPage.g.cpp")
#include "CommentListPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Navigation;
using namespace Windows::Foundation::Collections;

namespace winrt::NoiseBackendExample::implementation
{
    CommentListPage::CommentListPage()
    {
        InitializeComponent();
        
        m_comments = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>();
        
        // Get resource path
        auto exePath = std::filesystem::current_path();
        auto resPath = exePath / "res";
        
        // Create ViewModel
        auto dispatcher = Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();
        m_viewModel = std::make_shared<::NoiseBackendExample::ViewModel>(resPath, dispatcher);
    }

    IObservableVector<Windows::Foundation::IInspectable> CommentListPage::Comments()
    {
        return m_comments;
    }

    void CommentListPage::OnNavigatedTo(NavigationEventArgs const& e)
    {
        // Get story ID from navigation parameter
        if (e.Parameter()) {
            m_storyId = winrt::unbox_value<uint64_t>(e.Parameter());
            LoadComments();
        }
    }

    void CommentListPage::LoadComments()
    {
        LoadingRing().IsActive(true);
        
        m_viewModel->fetchComments(m_storyId, [this](const std::vector<::NoiseBackendExample::Comment>& comments) {
            m_comments.Clear();
            
            for (const auto& comment : comments) {
                auto author = winrt::to_hstring(comment.author);
                auto timestamp = winrt::to_hstring(comment.timestamp);
                auto text = winrt::to_hstring(comment.text);
                
                auto item = winrt::make<CommentItem>(author, timestamp, text);
                m_comments.Append(item);
            }
            
            LoadingRing().IsActive(false);
        });
    }

    void CommentListPage::BackButton_Click(Windows::Foundation::IInspectable const&,
                                           RoutedEventArgs const&)
    {
        if (Frame().CanGoBack()) {
            Frame().GoBack();
        }
    }
}
