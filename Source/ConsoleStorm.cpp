#include <STPL.h>
#include <cstdio>

SMutex mutex;
SMutex mutex2;

void Test(const char *name)
{
	int i = 0;
	mutex2.Wait(INFINITE);
	if (!strcmp(name, "thread1"))
		i = -15;
	do
	{
		i++;
		printf("\tTest: %s\n", name);
	} while (i < 5);
	mutex2.Release();
}

unsigned long __stdcall DoWork1(void *)
{
	printf("Thread 1 is done!\n\tGetLastError returned %d\n", GetLastError());
	Test("thread1");
	return 0;
}

unsigned long __stdcall DoWork2(void *)
{
	printf("Thread 2 is done!\n\tGetLastError returned %d\n", GetLastError());
	Test("thread2");
	return 0;
}

int main(int argc, char *argv[])
{
	SThread thread1(&DoWork1, 0);
	SThread thread2(&DoWork2, 0);

	mutex.Create(0, "MYMUTEX"); // Testing creating mutexes
	mutex2.Open("MYMUTEX"); // Testing opening mutexes

	thread1.Join();
	thread2.Join();
	
	mutex.Close();
	return 0;
}
