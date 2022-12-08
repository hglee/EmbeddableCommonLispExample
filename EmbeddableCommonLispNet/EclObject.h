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
		/// <para>Creates just base string.</para>
		/// </summary>
		EclObject(System::String^ str);

		/// <summary>
		/// Initializes a new instance of the <see cref="EclObject"/> class.
		/// </summary>
		EclObject(long long value);

		/// <summary>
		/// Initializes a new instance of the <see cref="EclObject"/> class.
		/// </summary>
		EclObject(double value);
		
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
		/// Gets current object is fixnum or not.
		/// </summary>
		property bool IsFixNum
		{
			bool get()
			{
				return ECL_FIXNUMP(this->obj_);
			}
		}

		/// <summary>
		/// Gets current object is double or not.
		/// </summary>
		property bool IsDouble
		{
			bool get()
			{
				return ECL_DOUBLE_FLOAT_P(this->obj_);
			}
		}

		/// <summary>
		/// Gets current object is base string or not.
		/// </summary>
		property bool IsBaseString
		{
			bool get()
			{
				return ECL_BASE_STRING_P(this->obj_);
			}
		}

		/// <summary>
		/// Gets current object is symbol or not.
		/// </summary>
		property bool IsSymbol
		{
			bool get()
			{
				return ECL_SYMBOLP(this->obj_);
			}
		}
		
		/// <summary>
		/// Gets fixnum value.
		/// </summary>
		property long long FixNum
		{
			long long get()
			{
				if (ECL_FIXNUMP(this->obj_))
				{
					return ecl_fixnum(this->obj_);
				}

				throw gcnew System::ApplicationException("Object is not fixnum");
			}
		}

		/// <summary>
		/// Gets double value.
		/// </summary>
		property double Double
		{
			double get()
			{
				if (ECL_DOUBLE_FLOAT_P(this->obj_))
				{
					return ecl_double_float(this->obj_);
				}

				throw gcnew System::ApplicationException("Object is not double");
			}
		}
		
		/// <summary>
		/// Gets base string.
		/// </summary>
		property System::String ^BaseString
		{
			System::String ^get()
			{
				return this->GetBaseString(this->obj_);
			}
		}
		
		/// <summary>
		/// Gets symbol name.
		/// </summary>
		property System::String ^SymbolName
		{
			System::String ^get()
			{
				if (ECL_SYMBOLP(this->obj_))
				{
					return this->GetBaseString(ecl_symbol_name(this->obj_));
				}

				throw gcnew System::ApplicationException("Object is not symbol");
			}
		}

		/// <summary>
		/// Compares to current object to obj
		/// </summary>
		/// <param name="obj">Target object.</param>
		/// <returns>Returns true if current object is equal to obj.</returns>
		bool IsEqual(EclObject^ obj);

		/// <summary>
		/// Gets current object as fixnum
		/// </summary>
		long long ToFixNum()
		{
			return ecl_to_fixnum(this->obj_);
		}

		/// <summary>
		/// Gets current object as double
		/// </summary>
		double ToDouble()
		{
			return ecl_to_double(this->obj_);
		}
		
	internal:
		/// <summary>
		/// Initializes a new instance of the <see cref="EclObject"/> class.
		/// </summary>
		/// <param name="obj">Target object</param>
		EclObject(cl_object obj);

		/// <summary>
		/// Read from string
		/// </summary>
		/// <param name="str">Target str</param>
		/// <returns>Result object</returns>
		static cl_object ReadFromString(System::String^ str);

		/// <summary>
		/// Gets internal backfield.
		/// </summary>
		cl_object GetInternal()
		{
			return this->obj_;
		}
		
	private:
		/// <summary>
		/// Gets base string from obj.
		/// </summary>
		/// <param name="obj">Target object.</param>
		/// <returns>Returns base string of obj.</returns>
		System::String^ GetBaseString(cl_object obj);
		
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
