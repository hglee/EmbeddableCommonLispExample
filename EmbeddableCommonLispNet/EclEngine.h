#pragma once

#include "EclFunc0.h"
#include "EclFunc2.h"
#include "EclObject.h"

namespace EmbeddableCommonLispNet
{
	/// <summary>
	/// Wrapper for common functions.
	/// </summary>
	public ref class EclEngine
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="EclEngine"/> class.
		/// </summary>
		EclEngine();

		/// <summary>
		/// Constructs object from string.
		/// </summary>
		/// <param name="str">Object representation</param>
		/// <returns>Returns object.</returns>
		EclObject^ Read(System::String^ str);
		
		/// <summary>
		/// Evaluate call string.
		/// </summary>
		/// <param name="call">Target string</param>
		/// <returns>Returns evaluated result.</returns>
		EclObject^ Call(System::String^ call);

		/// <summary>
		/// Evaluate form
		/// </summary>
		/// <param name="form">Target object.</param>
		/// <returns>Returns evaluated result.</returns>
		EclObject^ Eval(EclObject^ form);

		/// <summary>
		/// Evaluate form
		/// </summary>
		/// <param name="form">Target object.</param>
		/// <param name="env">Environment object.</param>
		/// <param name="value">Value object.</param>
		/// <returns>Returns evaluated result.</returns>
		EclObject^ Eval(EclObject^ form, EclObject^ env, EclObject^ value);

		/// <summary>
		/// Prints object
		/// </summary>
		/// <param name="obj">Target object.</param>
		void Print(EclObject ^obj);

		/// <summary>
		/// Register function
		/// </summary>
		/// <param name="name"></param>
		/// <param name="function"></param>
		EclFunc0 ^RegisterFunction(System::String ^name, System::Func<EclObject ^> ^function);

		/// <summary>
		/// Register function
		/// </summary>
		/// <param name="name"></param>
		/// <param name="function"></param>
		EclFunc2^ RegisterFunction(System::String^ name, System::Func<EclObject^, EclObject ^, EclObject ^>^ function);
	};
}
