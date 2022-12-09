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
        /// Run loop
        /// </summary>
        static void Run()
        {
            var engine = new EclEngine();
            engine.RegisterFunction("foo", () => new EclObject(42));
            engine.RegisterFunction("bar", (x, y) => new EclObject(x.FixNum + y.FixNum));

            var exit = engine.Read(":EXIT");
            var result = EclObject.Nil;

            Console.WriteLine(";; Enter :EXIT to break loop");
            Console.WriteLine(";; Embedded functions");
            Console.WriteLine(";;  - foo : returns 42. e.g. (foo)");
            Console.WriteLine(";;  - bar : add two number. e.g. (bar 1 2)");

            while (!result.IsEqual(exit))
            {
                Console.WriteLine();
                Console.Write("> ");

                try
                {
                    var form = engine.Call("(read)");
                    result = engine.Eval(form);
                    engine.Print(result);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error on eval: " + ex);

                    result = EclObject.Nil;
                }
            }
        }

        /// <summary>
        /// Main entry point
        /// </summary>
        /// <param name="args">Program arguments.</param>
        static void Main(string[] args)
        {
            App.Boot(args);

            try
            {
                Run();
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
