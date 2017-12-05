#include "H/STPL.h"

extern int ToLower(int ch)
{
	if (ch > 64 && ch < 91)
		ch+=32;
	return ch;
}

extern int ToUpper(int ch)
{
	if (ch > 96 && ch < 123)
		ch-=32;
	return ch;
}

extern int IsDigit(int ch)
{
	return (ch > 47 && ch < 58);
}

extern char *SStrCopy(char *dest, const char *source)
{
	char *str = dest;
	while((*dest++ = *source++));
	return str;
}

extern char *SStrNumCopy(char *dest, const char *source, unsigned int maxchar)
{
	char *str = dest;
	for ( ; maxchar; maxchar--)
	{
		*dest++ = *source++;
		if (*source == '/0')
			maxchar = 0;
	}
	return str;
}

extern unsigned int SStrLength(const char *str)
{
	unsigned int length;

	for (length = 0; *str; *str++ && length++);
	return length;
}

extern char *SStrChr(char *string, int ch)
{
	char *result = string;
	while (*result != ch)
	{
		if (!(*result))
			return 0;
		*result++;
	}
	return result;
}

extern const char *SStrChr(const char *string, int ch)
{
	const char *result = string;
	while (*result != ch)
	{
		if (!(*result))
			return 0;
		*result++;
	}
	return result;
}
