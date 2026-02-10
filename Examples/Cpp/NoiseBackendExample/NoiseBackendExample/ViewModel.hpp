// ViewModel.hpp - View Model for UI data binding
#pragma once

#include "pch.h"
#include "Model.hpp"
#include "Backend.hpp"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.UI.Dispatching.h>

namespace NoiseBackendExample {

// ViewModel manages the backend and provides data to UI
class ViewModel {
    std::unique_ptr<Backend> backend_;
    winrt::Microsoft::UI::Dispatching::DispatcherQueue dispatcher_;

public:
    ViewModel(const std::filesystem::path& resourceDir, 
              winrt::Microsoft::UI::Dispatching::DispatcherQueue dispatcher)
        : backend_(createBackend(resourceDir))
        , dispatcher_(dispatcher) {}

    // Fetch top stories asynchronously
    void fetchTopStories(std::function<void(std::vector<Story>)> callback) {
        auto future = backend_->getTopStories();
        future->sink(
            [this, callback](std::vector<Story> stories) {
                dispatcher_.TryEnqueue([callback, stories]() {
                    callback(stories);
                });
            },
            [this](std::string error) {
                dispatcher_.TryEnqueue([error]() {
                    // TODO: show error dialog
                });
            }
        );
    }

    // Fetch comments for a story
    void fetchComments(uint64_t storyId, std::function<void(std::vector<Comment>)> callback) {
        auto future = backend_->getComments(storyId);
        future->sink(
            [this, callback](std::vector<Comment> comments) {
                dispatcher_.TryEnqueue([callback, comments]() {
                    callback(comments);
                });
            },
            [this](std::string error) {
                dispatcher_.TryEnqueue([error]() {
                    // TODO: show error dialog
                });
            }
        );
    }

    Backend* getBackend() { return backend_.get(); }
};

} // namespace NoiseBackendExample
