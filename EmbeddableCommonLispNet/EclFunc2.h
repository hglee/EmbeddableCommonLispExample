#pragma once

#include "EclObject.h"

namespace EmbeddableCommonLispNet
{
	/// <summary>
	/// Wrapper for two parameter, one return function
	/// </summary>
	/// TODO: extract class
	public ref class EclFunc2
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="EclFunc0"/> class.
		/// </summary>
		/// <param name="name">Target function name</param>
		/// <param name="function">Target function</param>
		EclFunc2(System::String^ name, System::Func<EclObject^, EclObject^, EclObject ^>^ function);

		/// <summary>Destructor</summary>
		~EclFunc2();

		/// <summary>Finalizer</summary>
		!EclFunc2();

		/// <summary>
		/// Run function.
		/// </summary>
		EclObject^ Run(EclObject ^p1, EclObject ^p2);

	private:
		/// <summary>
		/// Register to engine.
		/// </summary>
		void Register();

		/// <summary>
		/// Register from engine.
		/// </summary>
		void Unregister();

		/// <summary>
		/// Get pointer from handle.
		/// </summary>
		void* GetPointer();

		/// <summary>
		/// Target function name.
		/// </summary>
		System::String^ name_;

		/// <summary>
		/// Internal name in engine
		/// </summary>
		System::String^ internalName_;

		/// <summary>
		/// Target function.
		/// </summary>
		System::Func<EclObject^, EclObject ^, EclObject ^>^ function_;

		/// <summary>
		/// Handle to current object.
		/// </summary>
		System::Runtime::InteropServices::GCHandle handle_;
	};
}
