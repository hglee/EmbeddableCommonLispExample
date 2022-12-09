#include "pch.h"
#include "BaseEclFunc.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

BaseEclFunc::BaseEclFunc(String^ name)
	: name_(name)
{
	if (name == nullptr)
	{
		throw gcnew ArgumentNullException("name");
	}

	this->internalName_ = String::Format("*EngineData{0}*", name->Trim());
	this->handle_ = GCHandle::Alloc(this);
}

BaseEclFunc::~BaseEclFunc()
{
	this->!BaseEclFunc();
}

BaseEclFunc::!BaseEclFunc()
{
	if (this->handle_.IsAllocated)
	{
		this->Unregister();

		this->handle_.Free();
	}
}

void BaseEclFunc::Register()
{
	auto name = EclObject::ReadFromString(this->internalName_);

	if (cl_safe_eval(name, Cnil, Cnil) != Cnil)
	{
		throw gcnew EclException("Function already registered: " + this->internalName_);
	}

	// register .NET handle as foreign data
	const auto data = ecl_make_pointer(this->GetPointer());

	ecl_defvar(name, data);
}

void BaseEclFunc::Unregister()
{
	auto name = EclObject::ReadFromString(this->internalName_);

	if (cl_safe_eval(name, Cnil, Cnil) != Cnil)
	{
		ecl_defvar(name, Cnil);
	}
}

void* BaseEclFunc::GetPointer()
{
	if (!this->handle_.IsAllocated)
	{
		return nullptr;
	}

	return GCHandle::ToIntPtr(this->handle_).ToPointer();
}
