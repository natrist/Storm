#ifndef __STHREAD_H__
#define __STHREAD_H__

#include <SLock.h>

/*
struct SThreadTrack
{
	int suspended;
	int live;
	unsigned long threadId;
	void *threadH;
	char name[16];
};

static struct S_Thread
{
	static int s_numthreads;
	static SThreadTrack s_threads[128];
} S_Thread;
*/

class SThread : public SSyncObject{
public:
	SThread();
	~SThread();

#ifdef _WIN32
	int Create(unsigned long (__stdcall *threadProc)(void *), void *param, SThread *thread, char *threadName);  
#endif /* _WIN32 */

	unsigned long m_threadId;
	char m_name[16];
};

//SThread SThreadCreate(DWORD (WINAPI *threadProc)(LPVOID), LPVOID lpParam);
//void SThreadClose(SThread *thread);

#endif /* __STHREAD_H__ */
