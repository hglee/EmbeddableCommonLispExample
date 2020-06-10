#pragma once

#include <ecl/ecl.h>
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
	};
}
