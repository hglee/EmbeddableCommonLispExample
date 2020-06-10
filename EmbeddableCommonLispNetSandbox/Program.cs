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
                var engine = new EclEngine();
                var exit = new EclObject(":EXIT");
                var result = new EclObject();

                while (!result.IsEqual(exit))
                {
                    Console.WriteLine();
                    Console.Write("> ");

                    var form = engine.Call("(read)");
                    result = engine.Eval(form);
                    engine.Print(result);
                }
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
