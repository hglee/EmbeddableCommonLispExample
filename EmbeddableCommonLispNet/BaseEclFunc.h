#pragma once

#include "EclObject.h"

namespace EmbeddableCommonLispNet
{
	/// <summary>
	/// Base class for function wrapper
	/// </summary>
	public ref class BaseEclFunc
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="BaseEclFunc"/> class.
		/// </summary>
		/// <param name="name">Target function name</param>
		BaseEclFunc(System::String^ name);

		/// <summary>Destructor</summary>
		~BaseEclFunc();

		/// <summary>Finalizer</summary>
		!BaseEclFunc();

		/// <summary>
		/// Register to engine.
		/// </summary>
		virtual void Register();

		/// <summary>
		/// Gets function name.
		/// </summary>
		property System::String ^Name
		{
			System::String ^get()
			{
				return this->name_;
			}
		}

	protected:
		/// <summary>
		/// Gets internal variable name for foreign data.
		/// </summary>
		property System::String ^InternalName
		{
			System::String^ get()
			{
				return this->internalName_;
			}
		}

		/// <summary>
		/// Register from engine.
		/// </summary>
		virtual void Unregister();

		/// <summary>
		/// Get pointer from handle.
		/// </summary>
		void* GetPointer();

	private:
		/// <summary>
		/// Target function name.
		/// </summary>
		System::String^ name_;

		/// <summary>
		/// Internal name in engine
		/// </summary>
		System::String^ internalName_;

		/// <summary>
		/// Handle to current object.
		/// </summary>
		System::Runtime::InteropServices::GCHandle handle_;
	};
}
