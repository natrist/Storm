#include <stdio.h>
#include <windows.h>
#include <SStr.cpp>

int main()
{
	HMODULE STORMLIB;
	int result;
	char c;
	char str[50];
	
	result = 0;
	c = 'C';
	STORMLIB = LoadLibrary("Storm.dll");
	if (STORMLIB == NULL)
	{
		MessageBox(0, "Could not load the Storm library!\nPress OK to exit.", "StormConsole Error", MB_OK);
		result = 1;
	}
	c = ToLower(c);
	SStrCopy(str, "test string");
	// printf("%c\n%s\n%d\n%s", c, str, SStrLength(str), SStrReverse(str));
	return result;
}