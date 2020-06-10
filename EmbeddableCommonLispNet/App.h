#pragma once

namespace EmbeddableCommonLispNet
{
	/// <summary>
	/// App class for entire initialization
	/// </summary>
	public ref class App abstract sealed
	{
	public:
		/// <summary>
		/// App level initialization.
		/// </summary>
		/// <param name="args">Boot arguments</param>
		static void Boot(array<System::String ^> ^args);

		/// <summary>
		/// App level shutdown.
		/// </summary>
		static void Shutdown();
	};
}
