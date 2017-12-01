#ifdef _WIN32
#include "Windows.h"
#endif

void SErrDisplayError(const char *inText, const char *inTitle)
{
	MessageBox(0, inText, inTitle, MB_ABORTRETRYIGNORE);
	exit(420);
}
