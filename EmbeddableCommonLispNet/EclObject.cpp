#include "pch.h"
#include "EclObject.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

EclObject::EclObject()
	: obj_(Cnil)
{
	
}

EclObject::EclObject(String^ str)
{
	if (str == nullptr)
	{
		throw gcnew ArgumentNullException("str");
	}

	IntPtr ptr = Marshal::StringToHGlobalAnsi(str);

	try
	{
		this->obj_ = ecl_make_simple_base_string((const char*)ptr.ToPointer(), -1);
	}
	finally
	{
		Marshal::FreeHGlobal(ptr);
	}
}

EclObject::EclObject(long long value)
	: obj_(ecl_make_integer(value))
{

}

EclObject::EclObject(double value)
	: obj_(ecl_make_double_float(value))
{
	
}

EclObject::EclObject(cl_object obj)
	: obj_(obj)
{
	if (obj == nullptr)
	{
		this->obj_ = Cnil;
	}
}

cl_object EclObject::ReadFromString(System::String^ str)
{
	if (str == nullptr)
	{
		return Cnil;
	}

	IntPtr ptr = Marshal::StringToHGlobalAnsi(str);

	try
	{
		return si_string_to_object(1, ecl_make_simple_base_string((const char*)ptr.ToPointer(), -1));
	}
	finally
	{
		Marshal::FreeHGlobal(ptr);
	}
}

bool EclObject::IsEqual(EclObject^ obj)
{
	if (obj == nullptr)
	{
		return false;
	}
	
	return cl_equal(this->obj_, obj->obj_) != Cnil;
}

String^ EclObject::GetString(cl_object obj)
{
	if (ECL_BASE_STRING_P(obj))
	{
		return gcnew String((const char*)(obj->base_string.self));
	}

	if (ECL_STRINGP(obj))
	{
		// convert from internal UTF-32
		const auto copySize = obj->string.dim * sizeof(ecl_character);
		auto buffer = gcnew array<byte>(copySize);

		Marshal::Copy(IntPtr(obj->string.self), buffer, 0, copySize);

		return Text::Encoding::UTF32->GetString(buffer);
	}

	throw gcnew EclException("obj is not string type.");
}
