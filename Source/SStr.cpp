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
