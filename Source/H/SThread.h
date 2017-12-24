#ifndef __STHREAD_H__
#define __STHREAD_H__

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
// #include <winnt.h>
#include <windows.h>
typedef HANDLE THANDLE;
typedef CRITICAL_SECTION STHREAD_LOCK;
#undef WIN32_LEAN_AND_MEAN
#else
#include <pthread.h>
typedef pthread_t THANDLE;
typedef pthread_mutex_lock STHREAD_LOCK;
#endif /* _WIN32 */

typedef void * (*STHREAD_CALLBACK)(void *);

/**
* Platform specific threading and mutexes.
*/
class SThread
{
public:
	SThread(void *startAddr, void *arg);
	~SThread();

	void Join();
	static THANDLE CurrentThread();
	static void CreateLock(STHREAD_LOCK *lock);
	static void DeleteLock(STHREAD_LOCK *lock);
	static void AcquireLock(STHREAD_LOCK *lock);
	static void ReleaseLock(STHREAD_LOCK *lock);

	void const *m_startAddr;
	void *m_arg;

private:
#ifdef _WIN32
	int _CreateWinThread();
	void _JoinWinThread();
#else /* pthreads */
	int _CreateThread(STHREAD_CALLBACK startRoutine, void *arg);
	void _JoinThread();
#endif /* _WIN32 */

	THANDLE m_thandle;
	DWORD m_threadId;
};

#define STORM_LOCK(lock) SThread::AcquireLock(lock)
#define STORM_UNLOCK(lock) SThread::ReleaseLock(lock)

#endif /* __STHREAD_H__ */
