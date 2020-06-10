#include "pch.h"
#include "EclEngine.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

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
