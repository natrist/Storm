#ifdef _WIN32
// For Windows includes and defines
#include <STPL.h>

extern void SErrDisplayError(const char *inText, const char *inTitle)
{
	MessageBoxA(0, inText, inTitle, MB_ABORTRETRYIGNORE);
}
#endif /* _WIN32 */
