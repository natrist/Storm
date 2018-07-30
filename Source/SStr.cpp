#include "H/SStr.inl"

extern int ToLower(int ch);

extern int ToUpper(int ch);

extern int IsDigit(int ch);

extern char *SStrToLower(char *string);

extern char *SStrToUpper(char *string);

extern char *SStrCopy(char *dest, const char *source);

extern char *SStrNumCopy(char *dest, const char *source, unsigned int maxchar);

extern unsigned int SStrLen(const char *str);

extern char *SStrChr(char *string, int ch);

extern const char *SStrChr(const char *string, int ch);

extern int SStrToInt(char *string);

void SStrTokenize(const char **string, char *buffer, unsigned int maxbufchars, const char *whitespace)
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
				for (unsigned int i = 0; i < SStrLen(whitespace); i++)
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
