namespace WumpusExample
{
    using System;
    using System.Windows;

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {
        /// <summary>
        /// View model
        /// </summary>
        private readonly MainViewModel viewModel;

        /// <summary>
        /// Initializes a new instance of the <see cref="MainWindow"/> class.
        /// </summary>
        public MainWindow()
        {
            this.InitializeComponent();

            this.viewModel = new MainViewModel();

            this.DataContext = this.viewModel;

            // AutomaticGraphLayoutControl's Graph does not support update by binding.
            // So GraphViewer and panel used to update directly instead 
            this.viewModel.AllCityGraphViewer.BindToPanel(this.AllGraphPanel);
            this.viewModel.KnownCityGraphViewer.BindToPanel(this.KnownGraphPanel);
        }

        /// <summary>
        /// Loaded handler.
        /// </summary>
        /// <param name="sender">Sender object.</param>
        /// <param name="e">Event arguments.</param>
        private void MainWindowOnLoaded(object sender, RoutedEventArgs e)
        {
            this.viewModel.Init();
        }

        /// <summary>
        /// Closed handler.
        /// </summary>
        /// <param name="sender">Sender object.</param>
        /// <param name="e">Event arguments.</param>
        private void MainWindowOnClosed(object? sender, EventArgs e)
        {
            this.viewModel.Dispose();
        }
    }
}
