#include "pch.h"
#include "EclEngine.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

static cl_object EngineCallFunc0(cl_object obj)
{
	auto data = ecl_to_pointer(obj);
	if (data == nullptr)
	{
		return Cnil;
	}

	auto handle = GCHandle::FromIntPtr(IntPtr(data));

	EclFunc0^ func = (EclFunc0^)handle.Target;

	auto result = func->Run();

	return result->GetInternal();
}

static cl_object EngineCallFunc2(cl_object obj, cl_object p1, cl_object p2)
{
	auto data = ecl_to_pointer(obj);
	if (data == nullptr)
	{
		return Cnil;
	}

	auto handle = GCHandle::FromIntPtr(IntPtr(data));

	EclFunc2^ func = (EclFunc2^)handle.Target;

	auto result = func->Run(gcnew EclObject(p1), gcnew EclObject(p2));

	return result->GetInternal();
}

EclEngine::EclEngine()
{
	ecl_def_c_function(c_string_to_object("_EngineCallFunc0"), (cl_objectfn_fixed)EngineCallFunc0, 1);
	ecl_def_c_function(c_string_to_object("_EngineCallFunc2"), (cl_objectfn_fixed)EngineCallFunc2, 3);
}

EclObject^ EclEngine::Call(String^ call)
{
	return this->Eval(gcnew EclObject(call));
}

EclObject^ EclEngine::Eval(EclObject^ form)
{
	return this->Eval(form, EclObject::Nil, EclObject::Nil);
}

EclObject^ EclEngine::Eval(EclObject^ form, EclObject^ env, EclObject^ value)
{
	if (form == nullptr)
	{
		throw gcnew ArgumentNullException("form");
	}

	if (env == nullptr)
	{
		throw gcnew ArgumentNullException("env");
	}

	if (value == nullptr)
	{
		throw gcnew ArgumentNullException("value");
	}

	return gcnew EclObject(cl_safe_eval(form->GetInternal(), env->GetInternal(), value->GetInternal()));
}

void EclEngine::Print(EclObject^ obj)
{
	if (obj != nullptr)
	{
		cl_print(1, obj->GetInternal());
	}
}

EclFunc0 ^EclEngine::RegisterFunction(String ^name, Func<EclObject^>^ function)
{
	if (name == nullptr)
	{
		throw gcnew ArgumentNullException("name");
	}
	
	if (function == nullptr)
	{
		throw gcnew ArgumentNullException("function");
	}

	return gcnew EclFunc0(name, function);
}

EclFunc2^ EclEngine::RegisterFunction(String^ name, Func<EclObject^, EclObject^, EclObject^>^ function)
{
	if (name == nullptr)
	{
		throw gcnew ArgumentNullException("name");
	}

	if (function == nullptr)
	{
		throw gcnew ArgumentNullException("function");
	}

	return gcnew EclFunc2(name, function);
}
