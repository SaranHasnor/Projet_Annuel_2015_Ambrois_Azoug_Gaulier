#include "cstring.h"

#include <string>

extern "C" const char *stringToCharArray(void *string)
{
	std::string *realString = (std::string*)string;

	return realString->c_str();
}

extern "C" void putCharArrayInString(const char *in, void *out)
{
	std::string *realString = (std::string*)out;

	*realString = std::string(in);
}