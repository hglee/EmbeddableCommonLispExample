#pragma once

#include <ecl/ecl.h>

namespace EmbeddableCommonLispNet
{
	/// <summary>
	/// cl_object wrapper class
	/// </summary>
	public ref class EclObject
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="EclObject"/> class.
		/// </summary>
		EclObject();

		/// <summary>
		/// Initializes a new instance of the <see cref="EclObject"/> class.
		/// </summary>
		EclObject(System::String^ str);

		/// <summary>
		/// Initializes a new instance of the <see cref="EclObject"/> class.
		/// </summary>
		EclObject(int value);
		
		/// <summary>
		/// Gets default nil object.
		/// </summary>
		static property EclObject ^Nil
		{
			EclObject ^get()
			{
				return NilObject;
			}
		}

		/// <summary>
		/// Compares to current object to obj
		/// </summary>
		/// <param name="obj">Target object.</param>
		/// <returns>Returns true if current object is equal to obj.</returns>
		bool IsEqual(EclObject^ obj);
		
	internal:
		/// <summary>
		/// Initializes a new instance of the <see cref="EclObject"/> class.
		/// </summary>
		/// <param name="obj">Target object</param>
		EclObject(cl_object obj);

		/// <summary>
		/// Gets internal backfield.
		/// </summary>
		cl_object GetInternal()
		{
			return this->obj_;
		}
		
	private:
		/// <summary>
		/// Default nil object.
		/// </summary>
		static EclObject^ NilObject = gcnew EclObject();

		/// <summary>
		/// Backfield.
		/// </summary>
		cl_object obj_;
	};
}
