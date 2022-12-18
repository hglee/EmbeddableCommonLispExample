#include "pch.h"
#include "EclAct3.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

EclAct3::EclAct3(String^ name, Action<EclObject^, EclObject^, EclObject^>^ action)
	: BaseEclFunc(name), action_(action)
{
	if (action == nullptr)
	{
		throw gcnew ArgumentNullException("action");
	}
}

void EclAct3::Register()
{
	BaseEclFunc::Register();

	// register wrapper function
	auto funcDef = String::Format("(defun {0} (x y z) (_EngineCallAct3 {1} x y z))", this->Name, this->InternalName);

	cl_safe_eval(EclObject::ReadFromString(funcDef), Cnil, Cnil);
}

void EclAct3::Run(EclObject^ p1, EclObject^ p2, EclObject^ p3)
{
	return this->action_(p1, p2, p3);
}
