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
	SThread::CreateLock(&lock);
	SThread thread1(&DoWork, nullptr);
	SThread thread2(&DoWorkTwo, nullptr);
	thread2.Join();
	SThread::DeleteLock(&lock);

	int digit = '4';
	return IsDigit(digit);
}
