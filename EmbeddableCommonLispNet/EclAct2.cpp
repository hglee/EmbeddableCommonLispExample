#include "pch.h"
#include "EclAct2.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

EclAct2::EclAct2(String^ name, Action<EclObject^, EclObject^>^ action)
	: BaseEclFunc(name), action_(action)
{
	if (action == nullptr)
	{
		throw gcnew ArgumentNullException("action");
	}
}

void EclAct2::Register()
{
	BaseEclFunc::Register();

	// register wrapper function
	auto funcDef = String::Format("(defun {0} (x y) (_EngineCallAct2 {1} x y))", this->Name, this->InternalName);

	cl_safe_eval(EclObject::ReadFromString(funcDef), Cnil, Cnil);
}

void EclAct2::Run(EclObject^ p1, EclObject^ p2)
{
	return this->action_(p1, p2);
}
