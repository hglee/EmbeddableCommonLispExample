#include "pch.h"
#include "EclFunc0.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

EclFunc0::EclFunc0(String ^name, Func<EclObject^>^ function)
	: BaseEclFunc(name), function_(function)
{
	if (function == nullptr)
	{
		throw gcnew ArgumentNullException("function");
	}
}

void EclFunc0::Register()
{
	BaseEclFunc::Register();

	// register wrapper function
	auto funcDef = String::Format("(defun {0} () (_EngineCallFunc0 {1}))", this->Name, this->InternalName);

	cl_safe_eval(EclObject::ReadFromString(funcDef), Cnil, Cnil);
}

EclObject ^EclFunc0::Run()
{
	return this->function_();
}
