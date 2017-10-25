inline void SSwap(char &a, char &b)
{
	char temp = a;
	a = b;
	b = temp;
}

int ToLower(int c)
{
	if (c > 64 && c < 91)
		c+=32;
	return c;
}

int ToUpper(int c)
{
	if (c > 96 && c < 123)
		c-=32;
	return c;
}

char *SStrCopy(char *dest, const char *source)
{
	char *str;

	str = dest;
	while(*dest++ = *source++);
	return str;
}

char *SStrNumCopy(char *dest, const char *source, unsigned int maxchar)
{
	char *str;

	str = dest;
	for ( ; maxchar; maxchar--)
	{
		*dest++ = *source++;
		if (*source == '/0')
			maxchar = 0;
	}
	return str;
}

unsigned int SStrLength(const char *str)
{
	unsigned int length;

	for (length = 0; *str; *str++ && length++);
	return length;
}

char *SStrReverse(char *dest, const char *source)
{
	char *str;
	int len;
	int pos;

	SStrCopy(dest, source);
	str = dest;
	len = SStrLength(source) - 1;
	pos = 0;
	while (pos < len)
		SSwap(dest[pos++], dest[len--]);

	return str;
}
