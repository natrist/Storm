#include "H/SThread.h"

#ifdef _WIN32
static  DWORD WINAPI ThreadProc(LPVOID lpParam);
#endif /* _WIN32 */

SThread::SThread(void *startAddr, void *arg)
{
	m_startAddr = startAddr;
	m_arg = arg;
#ifdef _WIN32
	_CreateWinThread();
#else
	_CreateThread(startAddr, arg);
#endif /* _WIN32 */
}

SThread::~SThread()
{
	if (m_thandle)
	{
#ifdef _WIN32
		CloseHandle(m_thandle);
#else
#endif /* _WIN32 */
	}
}

void SThread::Join()
{
	if (!m_thandle)
		return;
#ifdef _WIN32
	_JoinWinThread();
#else
	_JoinThread();
#endif /* _WIN32 */
}

THANDLE SThread::CurrentThread()
{
#ifdef _WIN32
	return GetCurrentThread();
#else
	return pthread_self();
#endif
}

#ifdef _WIN32
int SThread::_CreateWinThread()
{
	m_thandle = CreateThread(NULL, 0, &ThreadProc, (void *)this, 0, &m_threadId);
	return 0;
}

void SThread::_JoinWinThread()
{
	WaitForSingleObject(m_thandle, INFINITE);
}

void SThread::CreateLock(STHREAD_LOCK *lock)
{
#ifdef _WIN32
	InitializeCriticalSection(lock);
#else
	pthread_init_mutex(lock, NULL);
#endif /* _WIN32 */
}

void SThread::DeleteLock(STHREAD_LOCK *lock)
{
#ifdef _WIN32
	DeleteCriticalSection(lock);
#else
	pthread_mutex_destroy(lock);
#endif /* _WIN32 */
}

void SThread::AcquireLock(STHREAD_LOCK *lock)
{
#ifdef _WIN32
	EnterCriticalSection(lock);
#else
	pthread_mutex_lock(lock);
#endif /* _WIN32 */
}

void SThread::ReleaseLock(STHREAD_LOCK *lock)
{
#ifdef _WIN32
	LeaveCriticalSection(lock);
#else
	pthread_mutex_unlock(lock);
#endif /* _WIN32 */
}

static DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	SThread *thread = (SThread *)lpParam;
	STHREAD_CALLBACK *callback = (STHREAD_CALLBACK *)&thread->m_startAddr;
	(*callback)(&thread->m_arg);
	return 0;
}

#else

int SThread::_CreateThread(STHREAD_CALLBACK startRoutine, void *arg)
{
	pthread_create(&m_thandle, NULL, startRoutine, arg);
	return 0;
}

void SThread::_JoinThread()
{
	pthread_join(m_thandle, NULL);
}

#endif /* _WIN32 */
