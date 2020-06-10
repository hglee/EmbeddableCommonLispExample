#include "pch.h"
#include "EclFunc2.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

EclFunc2::EclFunc2(String^ name, Func<EclObject^, EclObject ^, EclObject ^>^ function)
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

EclFunc2::~EclFunc2()
{
	if (this->handle_.IsAllocated)
	{
		this->Unregister();

		this->handle_.Free();
	}
}

EclObject^ EclFunc2::Run(EclObject ^p1, EclObject ^p2)
{
	return this->function_(p1, p2);
}

void EclFunc2::Register()
{
	// register .NET handle as foreign data
	auto namePtr = Marshal::StringToHGlobalAnsi(this->internalName_);
	auto data = ecl_make_pointer(this->GetPointer());

	ecl_defvar(c_string_to_object((const char*)namePtr.ToPointer()), data);

	// register wrapper function
	auto funcDef = String::Format("(defun {0} (x y) (_EngineCallFunc2 {1} x y))", this->name_, this->internalName_);
	auto funcDefPtr = Marshal::StringToHGlobalAnsi(funcDef);

	cl_safe_eval(c_string_to_object((const char*)funcDefPtr.ToPointer()), Cnil, Cnil);
}

void EclFunc2::Unregister()
{
	auto namePtr = Marshal::StringToHGlobalAnsi(this->internalName_);

	ecl_defvar(c_string_to_object((const char*)namePtr.ToPointer()), Cnil);
}

void* EclFunc2::GetPointer()
{
	if (!this->handle_.IsAllocated)
	{
		return nullptr;
	}

	return GCHandle::ToIntPtr(this->handle_).ToPointer();
}
