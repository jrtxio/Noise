using Microsoft.UI.Dispatching;
using Microsoft.UI.Xaml;
using System;
using System.Threading;

namespace NoiseBackendExample
{
    public static class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Microsoft.UI.Xaml.Application.Start((p) => {
                var context = new DispatcherQueueSynchronizationContext(DispatcherQueue.GetForCurrentThread());
                SynchronizationContext.SetSynchronizationContext(context);
                new App();
            });
        }
    }
}
