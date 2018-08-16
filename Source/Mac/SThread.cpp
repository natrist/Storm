#include <SThread.h>
#include <SStr.inl>
#include <stdlib.h>

SThread::SThread()
{
}

SThread::~SThread()
{
}

//************************************
// Method:    Create
// FullName:  SThread::Create
// Access:    public 
// Returns:   0 if CreateThread fails or a valid thread handle
//************************************
int SThread::Create(void *(*threadProc)(void *), void *param, SThread *thread, char *threadName)
{
	pthread_t tThread;

	/* Create our thread */
	m_threadId = pthread_create(&tThread, 0, *threadProc, param);
	m_handle = (void *)tThread;

	SStrCopy(m_name, threadName);
	return m_handle != 0;
}
