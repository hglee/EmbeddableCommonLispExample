#include <iostream>

#include <ecl/ecl.h>

using namespace std;

static cl_object foo()
{
	return ecl_make_integer(42);
}

static cl_object bar(cl_object a, cl_object b)
{
	int aval = fix(a);
	int bval = fix(b);

	return ecl_make_integer(aval + bval);
}

static cl_object ecl_Call(const char* call)
{
	return cl_safe_eval(c_string_to_object(call), Cnil, Cnil);
}

static void init(int argc, char** argv)
{
	cl_boot(argc, argv);
	atexit(cl_shutdown);

	ecl_def_c_function(c_string_to_object("foo"), (cl_objectfn_fixed)foo, 0);
	ecl_def_c_function(c_string_to_object("bar"), (cl_objectfn_fixed)bar, 2);
}

// 1. Original example: https://github.com/fabriceleal/ecl-win-vs11-example
// 2. Ensure copy ecl.dll and encoding directory to output
int main(int argc, char** argv)
{
	init(argc, argv);

	cl_object exit_obj = c_string_to_object(":EXIT");
	cl_object result = Cnil;

	while (cl_equal(exit_obj, result) == Cnil)
	{
		printf("\n> ");
		cl_object form = ecl_Call("(read)");
		result = cl_safe_eval(form, Cnil, Cnil);
		cl_print(1, result);
	}

	return 0;
}
