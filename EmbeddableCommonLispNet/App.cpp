#include "pch.h"
#include <vector>
#include <ecl/ecl.h>
#include "App.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EmbeddableCommonLispNet;

/// <summary>
/// Convert input array to output
/// <para>Call DestructStringArray to free internal memory.</para>
/// </summary>
/// <param name="input">Input array</param>
/// <param name="output">Output array.</param>
static void ConvertStringArray(cli::array<String ^>^ input, vector<char *> &output)
{
	for each (auto str in input)
	{
		IntPtr ptr = Marshal::StringToHGlobalAnsi(str);

		output.push_back(_strdup((char*)ptr.ToPointer()));
	}
}

/// <summary>
/// Destruct string vector
/// </summary>
/// <param name="output">String vector</param>
static void DestructStringArray(vector<char *> &output)
{
	for (auto && str : output)
	{
		free(str);
	}

	output.clear();
}

void App::Boot(cli::array<String^>^ args)
{
	vector<char*> argv;
	
	if (args == nullptr || args->Length <= 0)
	{
		argv.push_back(_strdup("App"));
	}
	else
	{
		ConvertStringArray(args, argv);
	}

	cl_boot(argv.size(), &argv[0]);

	DestructStringArray(argv);
}

void App::Shutdown()
{
	cl_shutdown();
}
