#ifndef __SSTR_INL__
#define __SSTR_INL__

inline int ToLower(int ch)
{
	if (ch > 64 && ch < 91)
		ch+=32;
	return ch;
}

inline int ToUpper(int ch)
{
	if (ch > 96 && ch < 123)
		ch-=32;
	return ch;
}

inline int IsDigit(int ch)
{
	return (ch > 47 && ch < 58);
}

inline char *SStrToLower(char *string)
{
	char *tempstring = string;
	do
	{
		*tempstring++ = ToLower(*string++);
	} while (*string != 0);
	string = tempstring;
	return string;
}

inline char *SStrToUpper(char *string)
{
	char *tempstring = string;
	do
	{
		*tempstring++ = ToUpper(*string++);
	} while (*string != 0);
	string = tempstring;
	return string;
}

inline char *SStrCopy(char *dest, const char *source)
{
	char *str = dest;
	while((*dest++ = *source++));
	return str;
}

inline char *SStrNumCopy(char *dest, const char *source, unsigned int maxchar)
{
	char *str = dest;
	for ( ; maxchar; maxchar--)
	{
		*dest++ = *source++;
		if (*source == 0)
			maxchar = 0;
	}
	return str;
}

inline unsigned int SStrLen(const char *str)
{
	unsigned int length;

	for (length = 0; *str; *str++ && length++);
	return length;
}

inline char *SStrChr(char *string, int ch)
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

inline const char *SStrChr(const char *string, int ch)
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

inline int SStrToInt(char *string)
{
	int result = 0;
	bool negative = 0;

	// If the string is a negative number, we set the negative multiplier flag
	if (*string == '-')
	{
		negative = 1;
		*string++;
	}

	while ('0' <= *string && *string <= '9')
    	result = result * 10 + *string++ - '0';
	if (negative)
		result = result * -1;
	return result;
}

void SStrTokenize(const char **string, char *buffer, unsigned int maxbufchars, const char *whitespace);

#endif
