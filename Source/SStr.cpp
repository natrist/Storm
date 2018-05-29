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

extern char *SStrToLower(char *string)
{
	char *tempstring = string;
	do
	{
		*tempstring++ = ToLower(*string++);
	} while (*string != 0);
	string = tempstring;
	return string;
}

extern char *SStrToUpper(char *string)
{
	char *tempstring = string;
	do
	{
		*tempstring++ = ToUpper(*string++);
	} while (*string != 0);
	string = tempstring;
	return string;
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
		if (*source == 0)
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

extern void SStrTokenize(const char **string, char *buffer, unsigned int maxbufchars, const char *whitespace)
{
	if (string && *string)
	{
		// For write access to string
		const char *copy = *string;

		if (whitespace && *whitespace)
		{
			unsigned int pos = 0;
			
			// Here we reset our buffer (lol)
			while(buffer[pos] != '\0')
			{
				buffer[pos] = '\0';
				pos++;
			}

			for (pos = 0; pos < maxbufchars; pos++)
			{
				for (unsigned int i = 0; i < SStrLength(whitespace); i++)
				{
					if (copy[pos] == whitespace[i])
					{
						// Whitespace found at beginning of string
						if (pos == 0)
							copy++;
						else
						{
							copy = SStrChr(*string, whitespace[i]);
							copy++;
							goto WRITEOUT;
						}
					}
				}
				buffer[pos] = copy[pos];
				if (copy[pos] == 0)
					break;
			}

			for (unsigned int i = 0; i < pos; i++)
				copy++;
WRITEOUT:
			*string = copy;
		}
		// Error out here:
		// You should not be able to tokenize without a whitespace argument
	}
	// Error out here:
	// You should not be able to tokenize without a string
}
