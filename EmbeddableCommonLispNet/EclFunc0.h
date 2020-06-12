#pragma once

#include "BaseEclFunc.h"

namespace EmbeddableCommonLispNet
{
	/// <summary>
	/// Wrapper for zero parameter, one return function
	/// </summary>
	public ref class EclFunc0 : public BaseEclFunc
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="EclFunc0"/> class.
		/// </summary>
		/// <param name="name">Target function name</param>
		/// <param name="function">Target function</param>
		EclFunc0(System::String ^name, System::Func<EclObject^>^ function);

		/// <summary>
		/// Register to engine.
		/// </summary>
		void Register() override;
		
		/// <summary>
		/// Run function.
		/// </summary>
		EclObject^ Run();

	private:
		/// <summary>
		/// Target function.
		/// </summary>
		System::Func<EclObject^>^ function_;
	};
}
