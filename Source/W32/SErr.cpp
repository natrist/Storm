#ifdef WIN32
#include "../H/STPL.h"

extern void SErrDisplayError(const char *inText, const char *inTitle)
{
	MessageBox(0, inText, inTitle, MB_ABORTRETRYIGNORE);
}
#endif
