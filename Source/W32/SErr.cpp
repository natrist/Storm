#include <SErr.inl>
#include "Windows.h"

void SErrDisplayError(const char *inText, const char *inTitle)
{
	MessageBoxA(0, inText, inTitle, MB_ABORTRETRYIGNORE);
}
