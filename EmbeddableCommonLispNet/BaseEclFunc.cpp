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
	// register .NET handle as foreign data
	auto namePtr = Marshal::StringToHGlobalAnsi(this->internalName_);
	const auto data = ecl_make_pointer(this->GetPointer());

	ecl_defvar(c_string_to_object((const char*)namePtr.ToPointer()), data);
}

void BaseEclFunc::Unregister()
{
	auto namePtr = Marshal::StringToHGlobalAnsi(this->internalName_);

	ecl_defvar(c_string_to_object((const char*)namePtr.ToPointer()), Cnil);
}

void* BaseEclFunc::GetPointer()
{
	if (!this->handle_.IsAllocated)
	{
		return nullptr;
	}

	return GCHandle::ToIntPtr(this->handle_).ToPointer();
}
