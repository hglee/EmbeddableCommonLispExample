#pragma once

#include "BaseEclFunc.h"

namespace EmbeddableCommonLispNet
{
	/// <summary>
	/// Wrapper for one parameter, zero return function
	/// </summary>
	public ref class EclAct1 : public BaseEclFunc
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="EclAct1"/> class.
		/// </summary>
		/// <param name="name">Target function name</param>
		/// <param name="action">Target action</param>
		EclAct1(System::String^ name, System::Action<EclObject^>^ action);

		/// <summary>
		/// Register to engine.
		/// </summary>
		void Register() override;

		/// <summary>
		/// Run function.
		/// </summary>
		void Run(EclObject ^p1);

	private:
		/// <summary>
		/// Target function.
		/// </summary>
		System::Action<EclObject^>^ action_;
	};
}
