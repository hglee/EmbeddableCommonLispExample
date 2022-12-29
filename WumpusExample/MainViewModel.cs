namespace WumpusExample
{
    using System;
    using System.ComponentModel;
    using System.Windows.Input;
    using EmbeddableCommonLispNet;
    using Microsoft.Msagl.Drawing;
    using Microsoft.Msagl.WpfGraphControl;

    /// <summary>
    /// Main view model
    /// </summary>
    public sealed class MainViewModel : INotifyPropertyChanged, IDisposable
    {
        /// <summary>
        /// Main engine
        /// </summary>
        private EclEngine? engine;

        /// <summary>
        /// <see cref="ShowAllMap"/> backfield.
        /// </summary>
        private bool showAllMap;

        /// <summary>
        /// <see cref="TargetPosition"/> backfield.
        /// </summary>
        private int targetPosition;

        /// <summary>
        /// <see cref="ChargePosition"/> backfield.
        /// </summary>
        private int chargePosition;

        /// <summary>
        /// <see cref="Status"/> backfield.
        /// </summary>
        private string status;

        /// <summary>
        /// Initializes a new instance of the <see cref="MainViewModel"/> class.
        /// </summary>
        public MainViewModel()
        {
            this.status = string.Empty;

            this.AllCityGraphViewer = new GraphViewer();
            this.AllCityGraphViewer.RunLayoutAsync = true;

            this.KnownCityGraphViewer = new GraphViewer();
            this.KnownCityGraphViewer.RunLayoutAsync = true;

            this.AllCityGraph = new Graph();
            this.KnownCityGraph = new Graph();

            this.NewGameCommand = new DelegateCommand(this.NewGameCommandExecuted);
            this.GoCommand = new DelegateCommand(this.GoCommandExecuted);
            this.ChargeCommand = new DelegateCommand(this.ChargeCommandExecuted);
        }

        /// <inheritdoc />
        public event PropertyChangedEventHandler? PropertyChanged;

        /// <summary>
        /// Gets graph viewer for all city.
        /// </summary>
        public GraphViewer AllCityGraphViewer { get; }

        /// <summary>
        /// Gets graph viewer for known city.
        /// </summary>
        public GraphViewer KnownCityGraphViewer { get; }

        /// <summary>
        /// Gets or sets flag to show all map
        /// </summary>
        public bool ShowAllMap
        {
            get => this.showAllMap;
            set
            {
                if (this.showAllMap != value)
                {
                    this.showAllMap = value;

                    this.OnPropertyChanged("ShowAllMap");
                    this.OnPropertyChanged("HideAllMap");
                }
            }
        }

        /// <summary>
        /// Gets flag to hide all map
        /// </summary>
        public bool HideAllMap => !this.ShowAllMap;

        /// <summary>
        /// Gets or sets position to target
        /// </summary>
        public int TargetPosition
        {
            get => this.targetPosition;
            set
            {
                if (this.targetPosition != value)
                {
                    this.targetPosition = value;

                    this.OnPropertyChanged("TargetPosition");
                }
            }
        }

        /// <summary>
        /// Gets or sets position to charge
        /// </summary>
        public int ChargePosition
        {
            get => this.chargePosition;
            set
            {
                if (this.chargePosition != value)
                {
                    this.chargePosition = value;

                    this.OnPropertyChanged("ChargePosition");
                }
            }
        }

        /// <summary>
        /// Gets current status.
        /// </summary>
        public string Status
        {
            get => this.status;
            private set
            {
                if (this.status != value)
                {
                    this.status = value;

                    this.OnPropertyChanged("Status");
                }
            }
        }

        /// <summary>
        /// Gets new game command.
        /// </summary>
        public ICommand NewGameCommand { get; }

        /// <summary>
        /// Gets go command.
        /// </summary>
        public ICommand GoCommand { get; }

        /// <summary>
        /// Gets charge command.
        /// </summary>
        public ICommand ChargeCommand { get; }

        /// <summary>
        /// Gets or sets graph for all city.
        /// </summary>
        private Graph AllCityGraph { get; set; }

        /// <summary>
        /// Gets or sets graph for known city.
        /// </summary>
        public Graph KnownCityGraph { get; set; }

        /// <summary>
        /// Displays console
        /// </summary>
        private bool ShowConsole => true;

        /// <summary>
        /// Initializes state.
        /// </summary>
        public void Init()
        {
            EmbeddableCommonLispNet.App.Boot(Environment.GetCommandLineArgs());

            this.engine = new EclEngine();

            if (this.ShowConsole)
            {
                this.engine.ReAttachStdout();
            }
            else
            {
                // Disable stdio if you target to Windows application or you need to target to Console application.
                this.engine.EnableLoadPrint(false);
            }

            this.engine.RegisterFunction("AddNodeToAllCity", (x, y) =>
            {
                var node = this.AllCityGraph.AddNode(x.LString);
                node.LabelText = y.LString;
            });

            this.engine.RegisterFunction("AddEdgeToAllCity", (x, y, z) =>
            {
                var edge = this.AllCityGraph.AddEdge(x.LString, y.LString);
                if (z.IsString)
                {
                    edge.LabelText = z.LString;
                }
                edge.Attr.ArrowheadAtSource = ArrowStyle.None;
                edge.Attr.ArrowheadAtTarget = ArrowStyle.None;
            });

            this.engine.RegisterFunction("AddNodeToKnownCity", (x, y) =>
            {
                var node = this.KnownCityGraph.AddNode(x.LString);
                //node.LabelText = y.LString;
            });

            this.engine.RegisterFunction("AddEdgeToKnownCity", (x, y, z) =>
            {
                var edge = this.KnownCityGraph.AddEdge(x.LString, y.LString);
                if (z.IsString)
                {
                    edge.LabelText = z.LString;
                }
                edge.Attr.ArrowheadAtSource = ArrowStyle.None;
                edge.Attr.ArrowheadAtTarget = ArrowStyle.None;
            });

            this.engine.RegisterFunction("SetStatus", (x) =>
            {
                if (x.IsString)
                {
                    this.Status = x.LString;
                }
            });

            this.engine?.Call("(load \"Wumpus.lsp\")");
        }

        /// <inheritdoc />
        public void Dispose()
        {
            EmbeddableCommonLispNet.App.Shutdown();
        }

        /// <summary>
        /// Update player position in known graph
        /// </summary>
        private void UpdatePlayerPos()
        {
            var pos = this.engine?.Call("*player-pos*");
            if (pos != null && pos.IsFixNum)
            {
                var node = this.KnownCityGraph.FindNode(pos.FixNum.ToString());
                if (node != null)
                {
                    node.Attr.FillColor = Color.Yellow;
                }
            }
        }

        /// <summary>
        /// New game command executed handler.
        /// </summary>
        private void NewGameCommandExecuted(object? parameter)
        {
            this.AllCityGraph = new Graph();
            this.KnownCityGraph = new Graph();

            this.engine?.Call("(new-game)");

            this.UpdatePlayerPos();

            this.AllCityGraph.Attr.LayerDirection = LayerDirection.LR;
            this.KnownCityGraph.Attr.LayerDirection = LayerDirection.LR;

            this.AllCityGraphViewer.Graph = this.AllCityGraph;
            this.KnownCityGraphViewer.Graph = this.KnownCityGraph;
        }

        /// <summary>
        /// Go command executed handler.
        /// </summary>
        private void GoCommandExecuted(object? parameter)
        {
            if (this.TargetPosition < 0)
            {
                this.Status = "Invalid position";

                return;
            }

            this.KnownCityGraph = new Graph();

            this.engine?.Call($"(walk {this.TargetPosition})");

            this.UpdatePlayerPos();

            this.KnownCityGraph.Attr.LayerDirection = LayerDirection.LR;
            this.KnownCityGraphViewer.Graph = this.KnownCityGraph;
        }

        /// <summary>
        /// Charge command executed handler.
        /// </summary>
        private void ChargeCommandExecuted(object? parameter)
        {
            if (this.ChargePosition < 0)
            {
                this.Status = "Invalid position";

                return;
            }

            this.KnownCityGraph = new Graph();

            this.engine?.Call($"(charge {this.ChargePosition})");

            this.UpdatePlayerPos();

            this.KnownCityGraph.Attr.LayerDirection = LayerDirection.LR;
            this.KnownCityGraphViewer.Graph = this.KnownCityGraph;
        }

        /// <summary>
        /// Raises <see cref="PropertyChanged"/> event.
        /// </summary>
        /// <param name="propertyName">Property name</param>
        private void OnPropertyChanged(string? propertyName)
        {
            this.PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
