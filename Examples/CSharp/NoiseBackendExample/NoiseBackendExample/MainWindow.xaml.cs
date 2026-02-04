using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using System;
using System.Collections.ObjectModel;
using System.IO;
using System.Threading.Tasks;

namespace NoiseBackendExample
{
    public sealed partial class MainWindow : Window
    {
        public ObservableCollection<Story> Stories { get; } = new();
        private Backend _backend;

        public MainWindow()
        {
            this.InitializeComponent();
            this.Title = "Noise Backend Example";
            this.Activated += OnActivated;
        }

        private async void OnActivated(object sender, WindowActivatedEventArgs args)
        {
            this.Activated -= OnActivated; // Run once
            await InitializeAsync();
        }

        private async Task InitializeAsync()
        {
            try
            {
                // Locate core.zo
            string zoPath = Path.Combine(AppContext.BaseDirectory, "res", "core.zo");
                
                // Hack: If running from VS bin/Debug, might be further up?
                // Or user provides it via args? 
                // For now, assume it's there or user reads error.
                
                // Initialize Backend
                _backend = new Backend(zoPath, "main", "serve");
                
                // Navigate to List
            RootFrame.Navigate(typeof(StoryListPage), _backend);
            }
            catch (Exception ex)
            {
                // If backend init fails, show error in a dialog or simplistic TextBlock in Frame (if compatible)
                RootFrame.Content = new TextBlock { Text = $"Initialization Error: {ex.Message}", HorizontalAlignment = HorizontalAlignment.Center, VerticalAlignment = VerticalAlignment.Center };
            }
        }
    }
}
