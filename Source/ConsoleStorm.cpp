#include "H/STPL.h"
#include "H/SThread.h"
#include <cstdio>

STHREAD_LOCK lock;

void *DoWork(void *arg)
{
	STORM_LOCK(&lock);
	printf("DoWork acquired lock.\n");
	int i = 0;
	while (i++ < 10000)
		;
	printf("DoWork releasing lock.\n");
	STORM_UNLOCK(&lock);
	return 0;
}

void *DoWorkTwo(void *arg)
{
	STORM_LOCK(&lock);
	printf("DoWorkTwo acquired lock.\n");
	int i = 0;
	while (i++ < 10000)
		;
	printf("DoWorkTwo releasing lock.\n");
	STORM_UNLOCK(&lock);
	return 0;
}

int main(int argc, char *argv[])
{
	const int digit = '4';
	const char *string = "It's so fun!";
	char curArg[64];

	SStrTokenize(&string, curArg, 64u, "\t");
	return IsDigit(digit);
}
