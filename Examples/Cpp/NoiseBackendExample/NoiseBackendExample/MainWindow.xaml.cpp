#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "Backend.hpp"

#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::NoiseBackendExample::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        dispatcherQueue_ = Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();
        InitBackend();
    }

    MainWindow::~MainWindow() = default;

    void MainWindow::InitBackend()
    {
        try {
            std::string zoPath = HN::resolveZoPath();
            backend_ = std::make_unique<HN::HNBackend>(zoPath);
            LoadStories();
        } catch (const std::exception& e) {
            StoriesLoading().IsActive(false);
            PlaceholderText().Text(winrt::to_hstring("Backend error: " + std::string(e.what())));
            PlaceholderText().Visibility(Visibility::Visible);
        }
    }

    void MainWindow::LoadStories()
    {
        StoriesLoading().IsActive(true);

        backend_->getTopStories(
            [this](std::vector<HN::Story> stories) {
                dispatcherQueue_.TryEnqueue([this, stories = std::move(stories)]() {
                    stories_.clear();
                    auto listView = StoryListView();
                    listView.Items().Clear();

                    for (const auto& s : stories) {
                        stories_.emplace_back(s.id, winrt::to_hstring(s.title), s.comments.size());

                        StackPanel panel;
                        panel.Orientation(Orientation::Horizontal);
                        panel.Padding({ 4, 8, 4, 8 });

                        TextBlock titleText;
                        titleText.Text(winrt::to_hstring(s.title));
                        titleText.TextWrapping(TextWrapping::Wrap);

                        TextBlock countText;
                        countText.Text(winrt::to_hstring(std::to_string(s.comments.size())));
                        countText.Foreground(Microsoft::UI::Xaml::Media::SolidColorBrush(
                            Microsoft::UI::Colors::Gray()));
                        countText.Margin({ 8, 0, 0, 0 });
                        countText.VerticalAlignment(VerticalAlignment::Center);

                        panel.Children().Append(titleText);
                        panel.Children().Append(countText);
                        listView.Items().Append(panel);
                    }

                    StoriesLoading().IsActive(false);
                    PlaceholderText().Visibility(Visibility::Visible);
                    PlaceholderText().Text(L"Select a story");
                });
            },
            [this](std::string error) {
                dispatcherQueue_.TryEnqueue([this, error = std::move(error)]() {
                    StoriesLoading().IsActive(false);
                    PlaceholderText().Text(winrt::to_hstring("Error: " + error));
                    PlaceholderText().Visibility(Visibility::Visible);
                });
            }
        );
    }

    void MainWindow::LoadComments(uint64_t itemId)
    {
        CommentsLoading().IsActive(true);
        CommentListView().Visibility(Visibility::Collapsed);
        PlaceholderText().Visibility(Visibility::Collapsed);

        backend_->getComments(itemId,
            [this](std::vector<HN::Comment> comments) {
                dispatcherQueue_.TryEnqueue([this, comments = std::move(comments)]() {
                    comments_.clear();
                    auto listView = CommentListView();
                    listView.Items().Clear();

                    for (size_t i = 0; i < comments.size(); i++) {
                        const auto& c = comments[i];
                        comments_.emplace_back(c.id,
                            winrt::to_hstring(c.author),
                            winrt::to_hstring(c.timestamp),
                            winrt::to_hstring(c.text));

                        Border border;
                        border.CornerRadius({ 8, 8, 8, 8 });
                        border.Padding({ 12, 12, 12, 12 });
                        border.Margin({ 4, 4, 4, 4 });
                        border.BorderThickness({ 1, 1, 1, 1 });
                        border.Tag(winrt::box_value(static_cast<int64_t>(i)));

                        StackPanel panel;

                        TextBlock commentText;
                        commentText.Text(winrt::to_hstring(c.text));
                        commentText.TextWrapping(TextWrapping::Wrap);

                        TextBlock metaText;
                        metaText.Text(winrt::to_hstring(
                            "By " + c.author + " on " + c.timestamp));
                        metaText.Foreground(Microsoft::UI::Xaml::Media::SolidColorBrush(
                            Microsoft::UI::Colors::Gray()));
                        metaText.FontSize(12);
                        metaText.Margin({ 0, 4, 0, 0 });

                        panel.Children().Append(commentText);
                        panel.Children().Append(metaText);
                        border.Child(panel);

                        border.DoubleTapped([this](Windows::Foundation::IInspectable const& sender,
                            Input::DoubleTappedRoutedEventArgs const&) {
                            auto b = sender.as<Border>();
                            auto tag = winrt::unbox_value<int64_t>(b.Tag());
                            if (tag >= 0 && tag < static_cast<int64_t>(comments_.size())) {
                                uint64_t commentId = comments_[tag].Id;
                                commentStack_.insert(commentStack_.begin(), commentId);
                                LoadComments(commentId);
                            }
                        });

                        listView.Items().Append(border);
                    }

                    CommentListView().Visibility(Visibility::Visible);
                    CommentsLoading().IsActive(false);
                    UpdateBackButton();
                });
            },
            [this](std::string error) {
                dispatcherQueue_.TryEnqueue([this, error = std::move(error)]() {
                    CommentsLoading().IsActive(false);
                    StoryTitle().Text(winrt::to_hstring("Error: " + error));
                });
            }
        );
    }

    void MainWindow::OnStorySelected(
        [[maybe_unused]] Windows::Foundation::IInspectable const& sender,
        [[maybe_unused]] SelectionChangedEventArgs const& args)
    {
        int index = StoryListView().SelectedIndex();
        if (index < 0 || index >= static_cast<int>(stories_.size())) return;

        const auto& story = stories_[index];
        StoryTitle().Text(story.Title);
        PlaceholderText().Visibility(Visibility::Collapsed);

        commentStack_.clear();
        commentStack_.push_back(story.Id);
        LoadComments(story.Id);
    }

    void MainWindow::OnCommentDoubleTapped(
        [[maybe_unused]] Windows::Foundation::IInspectable const& sender,
        [[maybe_unused]] Input::DoubleTappedRoutedEventArgs const& args)
    {
        // Handled inline via lambda in LoadComments.
    }

    void MainWindow::OnBackClicked(
        [[maybe_unused]] Windows::Foundation::IInspectable const& sender,
        [[maybe_unused]] RoutedEventArgs const& args)
    {
        if (commentStack_.size() > 1) {
            commentStack_.erase(commentStack_.begin());
            LoadComments(commentStack_.front());
        }
    }

    void MainWindow::UpdateBackButton()
    {
        BackButton().Visibility(commentStack_.size() > 1
            ? Visibility::Visible
            : Visibility::Collapsed);
    }
}
