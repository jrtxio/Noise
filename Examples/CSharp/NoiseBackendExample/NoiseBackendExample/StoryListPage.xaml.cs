using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using System;
using System.Collections.ObjectModel;
using System.Threading.Tasks;

namespace NoiseBackendExample
{
    public sealed partial class StoryListPage : Page
    {
        public ObservableCollection<Story> Stories { get; } = new();
        private Backend _backend;

        public StoryListPage()
        {
            this.InitializeComponent();
        }

        protected override async void OnNavigatedTo(NavigationEventArgs e)
        {
            if (e.Parameter is Backend backend)
            {
                _backend = backend;
                await LoadStoriesAsync();
            }
        }

        private async Task LoadStoriesAsync()
        {
            try
            {
                if (_backend == null) return;
                
                StatusText.Text = "Fetching Stories...";
                LoadingRing.IsActive = true;
                LoadingRing.Visibility = Visibility.Visible;
                
                var stories = await _backend.GetTopStories();

                Stories.Clear();
                foreach (var story in stories)
                {
                    Stories.Add(story);
                }

                StatusText.Text = $"Loaded {stories.Count} stories.";
                LoadingRing.IsActive = false;
                LoadingRing.Visibility = Visibility.Collapsed;
            }
            catch (Exception ex)
            {
                StatusText.Text = $"Error: {ex.Message}";
                LoadingRing.IsActive = false;
            }
        }

        private void StoryListView_ItemClick(object sender, ItemClickEventArgs e)
        {
            if (e.ClickedItem is Story story)
            {
                Frame.Navigate(typeof(StoryDetailPage), new Tuple<Story, Backend>(story, _backend));
            }
        }
    }
}
