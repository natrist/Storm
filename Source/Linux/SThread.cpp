#include "SThread.h"

SThread::SThread(void *startAddr, void *arg)
{
	m_startAddr = startAddr;
	m_arg = arg;
	m_thandle = nullptr;
	m_threadId = NULL;
	_CreateThread(startAddr, arg);
}

SThread::~SThread()
{
}

void SThread::Join()
{
	if (!m_thandle)
		return;

	_JoinThread();
}

THANDLE SThread::CurrentThread()
{
	return pthread_self();
}

void SThread::CreateLock(STHREAD_LOCK *lock)
{
	pthread_init_mutex(lock, NULL);
}

void SThread::DeleteLock(STHREAD_LOCK *lock)
{
	pthread_mutex_destroy(lock);
}

void SThread::AcquireLock(STHREAD_LOCK *lock)
{
	pthread_mutex_lock(lock);
}

void SThread::ReleaseLock(STHREAD_LOCK *lock)
{
	pthread_mutex_unlock(lock);
}

int SThread::_CreateThread(STHREAD_CALLBACK startRoutine, void *arg)
{
	pthread_create(&m_thandle, NULL, startRoutine, arg);
	return 0;
}

void SThread::_JoinThread()
{
	pthread_join(m_thandle, NULL);
}
