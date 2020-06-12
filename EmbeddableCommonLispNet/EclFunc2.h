#pragma once

#include "BaseEclFunc.h"

namespace EmbeddableCommonLispNet
{
	/// <summary>
	/// Wrapper for two parameter, one return function
	/// </summary>
	public ref class EclFunc2 : public BaseEclFunc
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="EclFunc0"/> class.
		/// </summary>
		/// <param name="name">Target function name</param>
		/// <param name="function">Target function</param>
		EclFunc2(System::String^ name, System::Func<EclObject^, EclObject^, EclObject ^>^ function);

		/// <summary>
		/// Register to engine.
		/// </summary>
		void Register() override;

		/// <summary>
		/// Run function.
		/// </summary>
		EclObject^ Run(EclObject ^p1, EclObject ^p2);

	private:
		/// <summary>
		/// Target function.
		/// </summary>
		System::Func<EclObject^, EclObject ^, EclObject ^>^ function_;
	};
}
