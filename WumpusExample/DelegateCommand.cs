namespace WumpusExample
{
    using System;
    using System.Windows.Input;

    /// <summary>
    /// Delegate command
    /// </summary>
    public sealed class DelegateCommand : ICommand
    {
        /// <summary>
        /// Function to execute
        /// </summary>
        private readonly Action<object?> execute;

        /// <summary>
        /// Function to check
        /// </summary>
        private readonly Predicate<object?> canExecute;

        /// <summary>
        /// Initializes a new instance of the <see cref="DelegateCommand"/> class.
        /// </summary>
        /// <param name="execute">Function to execute</param>
        /// <param name="canExecute">Function to check</param>
        public DelegateCommand(Action<object?> execute, Predicate<object?> canExecute)
        {
            if (execute == null)
            {
                throw new ArgumentNullException(nameof(execute));
            }

            this.execute = execute;
            this.canExecute = canExecute;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DelegateCommand"/> class.
        /// </summary>
        /// <param name="execute">Function to execute</param>
        public DelegateCommand(Action<object?> execute)
            : this(execute, x => true)
        {

        }

        /// <inheritdoc />
        public event EventHandler? CanExecuteChanged;

        /// <inheritdoc />
        public bool CanExecute(object? parameter)
        {
            return this.canExecute(parameter);
        }

        /// <inheritdoc />
        public void Execute(object? parameter)
        {
            this.execute(parameter);
        }

        /// <summary>
        /// Raises <see cref="CanExecuteChanged"/> event.
        /// </summary>
        public void RaiseCanExecuteChanged()
        {
            this.CanExecuteChanged?.Invoke(this, EventArgs.Empty);
        }
    }
}
