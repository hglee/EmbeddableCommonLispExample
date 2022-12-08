#include "pch.h"
#include "EclFunc2.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

EclFunc2::EclFunc2(String^ name, Func<EclObject^, EclObject ^, EclObject ^>^ function)
	: BaseEclFunc(name), function_(function)
{
	if (function == nullptr)
	{
		throw gcnew ArgumentNullException("function");
	}
}

void EclFunc2::Register()
{
	BaseEclFunc::Register();

	// register wrapper function
	auto funcDef = String::Format("(defun {0} (x y) (_EngineCallFunc2 {1} x y))", this->Name, this->InternalName);

	cl_safe_eval(EclObject::ReadFromString(funcDef), Cnil, Cnil);
}

EclObject^ EclFunc2::Run(EclObject ^p1, EclObject ^p2)
{
	return this->function_(p1, p2);
}
