#include "pch.h"
#include "EclAct1.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

EclAct1::EclAct1(String^ name, Action<EclObject^>^ action)
	: BaseEclFunc(name), action_(action)
{
	if (action == nullptr)
	{
		throw gcnew ArgumentNullException("action");
	}
}

void EclAct1::Register()
{
	BaseEclFunc::Register();

	// register wrapper function
	auto funcDef = String::Format("(defun {0} (x) (_EngineCallAct1 {1} x))", this->Name, this->InternalName);

	cl_safe_eval(EclObject::ReadFromString(funcDef), Cnil, Cnil);
}

void EclAct1::Run(EclObject ^p1)
{
	return this->action_(p1);
}
