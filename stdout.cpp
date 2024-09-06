#include <HalonMTA.h>
#include <unistd.h>
#include <mutex>

std::mutex mstdout;
std::mutex mstderr;

HALON_EXPORT
int Halon_version()
{
	return HALONMTA_PLUGIN_VERSION;
}

void _stdout(HalonHSLContext* hhc, HalonHSLArguments* args, HalonHSLValue* ret)
{
	HalonHSLValue* a;

	char* stringv = nullptr;
	size_t stringl;
	a = HalonMTA_hsl_argument_get(args, 0);
	if (a && HalonMTA_hsl_value_type(a) == HALONMTA_HSL_TYPE_STRING)
		HalonMTA_hsl_value_get(a, HALONMTA_HSL_TYPE_STRING, &stringv, &stringl);
	else
	{
		HalonHSLValue* x = HalonMTA_hsl_throw(hhc);
 		HalonMTA_hsl_value_set(x, HALONMTA_HSL_TYPE_EXCEPTION, "Invalid or missing name parameter", 0);
		return;
	}

	mstdout.lock();
	double r = (double)write(1, stringv, stringl);
	mstdout.unlock();
	HalonMTA_hsl_value_set(ret, HALONMTA_HSL_TYPE_NUMBER, &r, 0);
}

void _stderr(HalonHSLContext* hhc, HalonHSLArguments* args, HalonHSLValue* ret)
{
	HalonHSLValue* a;

	char* stringv = nullptr;
	size_t stringl;
	a = HalonMTA_hsl_argument_get(args, 0);
	if (a && HalonMTA_hsl_value_type(a) == HALONMTA_HSL_TYPE_STRING)
		HalonMTA_hsl_value_get(a, HALONMTA_HSL_TYPE_STRING, &stringv, &stringl);
	else
	{
		HalonHSLValue* x = HalonMTA_hsl_throw(hhc);
 		HalonMTA_hsl_value_set(x, HALONMTA_HSL_TYPE_EXCEPTION, "Invalid or missing name parameter", 0);
		return;
	}

	mstderr.lock();
	double r = (double)write(2, stringv, stringl);
	mstderr.unlock();
	HalonMTA_hsl_value_set(ret, HALONMTA_HSL_TYPE_NUMBER, &r, 0);
}

HALON_EXPORT
bool Halon_hsl_register(HalonHSLRegisterContext* ptr)
{
	HalonMTA_hsl_module_register_function(ptr, "stdout", &_stdout);
	HalonMTA_hsl_module_register_function(ptr, "stderr", &_stderr);
	return true;
}
