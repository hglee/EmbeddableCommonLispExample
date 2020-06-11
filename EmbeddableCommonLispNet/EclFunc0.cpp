#include "pch.h"
#include "EclFunc0.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

EclFunc0::EclFunc0(String ^name, Func<EclObject^>^ function)
	: name_(name), function_(function)
{
	if (name == nullptr)
	{
		throw gcnew ArgumentNullException("name");
	}
	
	if (function == nullptr)
	{
		throw gcnew ArgumentNullException("function");
	}

	this->internalName_ = String::Format("*EngineData{0}*", name->Trim());
	this->handle_ = GCHandle::Alloc(this);

	this->Register();
}

EclFunc0::~EclFunc0()
{
	if (this->handle_.IsAllocated)
	{
		this->Unregister();
		
		this->handle_.Free();
	}
}

EclObject ^EclFunc0::Run()
{
	return this->function_();
}

void EclFunc0::Register()
{
	// register .NET handle as foreign data
	auto namePtr = Marshal::StringToHGlobalAnsi(this->internalName_);
	const auto data = ecl_make_pointer(this->GetPointer());

	ecl_defvar(c_string_to_object((const char*)namePtr.ToPointer()), data);

	// register wrapper function
	auto funcDef = String::Format("(defun {0} () (_EngineCallFunc0 {1}))", this->name_, this->internalName_);
	auto funcDefPtr = Marshal::StringToHGlobalAnsi(funcDef);

	cl_safe_eval(c_string_to_object((const char*)funcDefPtr.ToPointer()), Cnil, Cnil);
}

void EclFunc0::Unregister()
{
	auto namePtr = Marshal::StringToHGlobalAnsi(this->internalName_);

	ecl_defvar(c_string_to_object((const char*)namePtr.ToPointer()), Cnil);
}

void* EclFunc0::GetPointer()
{
	if (!this->handle_.IsAllocated)
	{
		return nullptr;
	}
	
	return GCHandle::ToIntPtr(this->handle_).ToPointer();
}
