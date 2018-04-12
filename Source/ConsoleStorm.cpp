#include <STPL.h>

int main(__in int _Argc, __in_ecount_z(_Argc) char ** _Argv, __in_z char ** _Env)
{
	char buf[255] = { 0, };
	const char *string = "Zed 3 5 9";

	SStrTokenize(&string, buf, -1, " \t");
	printf("\tSStrTokenize returned '%s'\n", buf);
	SStrTokenize(&string, buf, -1, " \t");
	printf("\tSStrTokenize returned '%s'\n", buf);
	SStrTokenize(&string, buf, -1, " \t");
	printf("\tSStrTokenize returned '%s'\n", buf);
	SStrTokenize(&string, buf, -1, " \t");
	printf("\tSStrTokenize returned '%s'\n", buf);
	return 0;
}

/*
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
*/