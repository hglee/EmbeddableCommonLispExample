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

	this->obj_ = c_string_to_object((const char *)ptr.ToPointer());
}

EclObject::EclObject(cl_object obj)
	: obj_(obj)
{
	if (obj == nullptr)
	{
		this->obj_ = Cnil;
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
