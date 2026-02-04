using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using System;
using System.Collections.ObjectModel;
using System.Threading.Tasks;

namespace NoiseBackendExample
{
    public sealed partial class StoryDetailPage : Page
    {
        public ObservableCollection<Comment> Comments { get; } = new();
        private Story _story;
        private Backend _backend;

        public StoryDetailPage()
        {
            this.InitializeComponent();
        }

        protected override async void OnNavigatedTo(NavigationEventArgs e)
        {
            if (e.Parameter is Tuple<Story, Backend> param)
            {
                _story = param.Item1;
                _backend = param.Item2;
                TitleTextBlock.Text = _story.Title;
                await LoadCommentsAsync();
            }
        }

        private async Task LoadCommentsAsync()
        {
             try
             {
                 LoadingRing.Visibility = Visibility.Visible;
                 LoadingRing.IsActive = true;
                 
                 var comments = await _backend.GetComments(_story.Id);
                 Comments.Clear();
                 foreach (var c in comments)
                 {
                     Comments.Add(c);
                 }
             }
             catch (Exception ex)
             {
                 // Handle error
                 System.Diagnostics.Debug.WriteLine(ex.Message);
             }
             finally
             {
                 LoadingRing.IsActive = false;
                 LoadingRing.Visibility = Visibility.Collapsed;
             }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            if (Frame.CanGoBack)
            {
                Frame.GoBack();
            }
        }
    }
}
