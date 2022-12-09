#pragma once

using namespace System;
using namespace System::Runtime::Serialization;

namespace EmbeddableCommonLispNet
{
	[Serializable]
	/// <summary>
	/// Exception type used in library.
	/// </summary>
	public ref class EclException : public Exception
	{
	public:
		EclException()
		{
			
		}

		EclException(String ^msg)
			: Exception(msg)
		{
			
		}

		EclException(String ^msg, Exception ^ex)
			: Exception(msg, ex)
		{
			
		}

	protected:
		EclException(SerializationInfo^ info, StreamingContext ctx)
			: Exception(info, ctx)
		{
			
		}
	};
}
