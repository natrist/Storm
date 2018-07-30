#include <SErr.inl>

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501
#include "Windows.h"

void SErrDisplayError(const char *inText, const char *inTitle)
{
	MessageBoxA(0, inText, inTitle, MB_ABORTRETRYIGNORE);
}
