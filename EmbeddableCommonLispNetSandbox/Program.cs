namespace EmbeddableCommonLispNetSandbox
{
    using System;
    using EmbeddableCommonLispNet;

    /// <summary>
    /// Program class
    /// </summary>
    public class Program
    {
        /// <summary>
        /// Main entry point
        /// </summary>
        /// <param name="args">Program arguments.</param>
        static void Main(string[] args)
        {
            App.Boot(args);

            try
            {

            }
            catch (Exception ex)
            {
                Console.WriteLine("Error on running: " + ex);
            }
            finally
            {
                App.Shutdown();
            }
        }
    }
}
