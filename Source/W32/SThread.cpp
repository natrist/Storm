#include <SThread.h>
#include <SStr.inl>

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
int SThread::Create(unsigned long (__stdcall *threadProc)(void *), void *param, SThread *thread, char *threadName)
{
	m_handle = CreateThread( 
		0,			// default security attributes
		0,			// use default stack size  
		threadProc,	// thread function name
		param,		// argument to thread function 
		0,			// use default creation flags 
		&m_threadId);

	SStrCopy(m_name, threadName);
	return m_handle != 0;
}
