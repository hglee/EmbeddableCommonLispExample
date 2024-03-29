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

static cl_object EngineCallAct1(cl_object obj, cl_object p1)
{
	auto data = ecl_to_pointer(obj);
	if (data == nullptr)
	{
		return Cnil;
	}

	auto handle = GCHandle::FromIntPtr(IntPtr(data));

	EclAct1^ act = (EclAct1^)handle.Target;

	act->Run(gcnew EclObject(p1));

	return Cnil;
}

static cl_object EngineCallAct2(cl_object obj, cl_object p1, cl_object p2)
{
	auto data = ecl_to_pointer(obj);
	if (data == nullptr)
	{
		return Cnil;
	}

	auto handle = GCHandle::FromIntPtr(IntPtr(data));

	EclAct2^ act = (EclAct2^)handle.Target;

	act->Run(gcnew EclObject(p1), gcnew EclObject(p2));

	return Cnil;
}

static cl_object EngineCallAct3(cl_object obj, cl_object p1, cl_object p2, cl_object p3)
{
	auto data = ecl_to_pointer(obj);
	if (data == nullptr)
	{
		return Cnil;
	}

	auto handle = GCHandle::FromIntPtr(IntPtr(data));

	EclAct3^ act = (EclAct3^)handle.Target;

	act->Run(gcnew EclObject(p1), gcnew EclObject(p2), gcnew EclObject(p3));

	return Cnil;
}

EclEngine::EclEngine()
{
	ecl_def_c_function(c_string_to_object("_EngineCallFunc0"), (cl_objectfn_fixed)EngineCallFunc0, 1);
	ecl_def_c_function(c_string_to_object("_EngineCallFunc2"), (cl_objectfn_fixed)EngineCallFunc2, 3);

	ecl_def_c_function(c_string_to_object("_EngineCallAct1"), (cl_objectfn_fixed)EngineCallAct1, 2);
	ecl_def_c_function(c_string_to_object("_EngineCallAct2"), (cl_objectfn_fixed)EngineCallAct2, 3);
	ecl_def_c_function(c_string_to_object("_EngineCallAct3"), (cl_objectfn_fixed)EngineCallAct3, 4);
}

EclObject^ EclEngine::Read(String^ str)
{
	if (str == nullptr)
	{
		return EclObject::Nil;
	}

	return gcnew EclObject(EclObject::ReadFromString(str));
}

EclObject^ EclEngine::Call(String^ call)
{
	return this->Eval(this->Read(call));
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

	auto result = gcnew EclFunc0(name, function);
	result->Register();

	return result;
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

	auto result = gcnew EclFunc2(name, function);
	result->Register();

	return result;
}

EclAct1^ EclEngine::RegisterFunction(String^ name, Action<EclObject^>^ action)
{
	if (name == nullptr)
	{
		throw gcnew ArgumentNullException("name");
	}

	if (action == nullptr)
	{
		throw gcnew ArgumentNullException("action");
	}

	auto result = gcnew EclAct1(name, action);
	result->Register();

	return result;
}

EclAct2^ EclEngine::RegisterFunction(String^ name, Action<EclObject^, EclObject^>^ action)
{
	if (name == nullptr)
	{
		throw gcnew ArgumentNullException("name");
	}

	if (action == nullptr)
	{
		throw gcnew ArgumentNullException("action");
	}

	auto result = gcnew EclAct2(name, action);
	result->Register();

	return result;
}

EclAct3^ EclEngine::RegisterFunction(String^ name, Action<EclObject^, EclObject^, EclObject^>^ action)
{
	if (name == nullptr)
	{
		throw gcnew ArgumentNullException("name");
	}

	if (action == nullptr)
	{
		throw gcnew ArgumentNullException("action");
	}

	auto result = gcnew EclAct3(name, action);
	result->Register();

	return result;
}

void EclEngine::EnableLoadPrint(bool state)
{
	this->Call(String::Format("(setq *load-verbose* {0})", state ? "T" : "nil"));
	this->Call(String::Format("(setq *load-print* {0})", state ? "T" : "nil"));
}

void EclEngine::ReAttachStdout()
{
	if (AllocConsole())
	{
		auto handle = CreateFile(L"CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

		ecl_setq(ecl_process_env(),
			ecl_make_symbol("*STANDARD-OUTPUT*", "COMMON-LISP"),
			ecl_make_stream_from_FILE(ecl_make_constant_base_string("stdout", -1),
				handle,
				ecl_smm_io_wcon,
				8,
				0,
				ecl_make_keyword("UTF-8")));
	}
}
