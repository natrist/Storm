#ifndef __SERR_INL__
#define __SERR_INL__

inline void SErrDisplayError(const char *inText, const char *inTitle);

// DO NOT REMOVE THE BELOW INCLUSION:
// USED FOR IN-LINING OF SERR CODE!
#ifdef _WIN32 /* Platform check */
    #include "../Win32/SErr.cpp"
#elif __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
    #include "../Mac/SErr.cpp"
#else
    #include "../Linux/SErr.cpp"
#endif /* Platform check */

#endif /* __SERR_INL__ */
