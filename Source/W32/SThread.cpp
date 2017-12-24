#include "SThread.h"

static DWORD WINAPI ThreadProc(LPVOID lpParam);

SThread::SThread(void *startAddr, void *arg)
{
	m_startAddr = startAddr;
	m_arg = arg;
	m_thandle = nullptr;
	m_threadId = NULL;
	_CreateWinThread();
}

SThread::~SThread()
{
	if (m_thandle)
		CloseHandle(m_thandle);
}

void SThread::Join()
{
	if (!m_thandle)
		return;
	_JoinWinThread();
}

THANDLE SThread::CurrentThread()
{
	return GetCurrentThread();
}

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
	InitializeCriticalSection(lock);
}

void SThread::DeleteLock(STHREAD_LOCK *lock)
{
	DeleteCriticalSection(lock);
}

void SThread::AcquireLock(STHREAD_LOCK *lock)
{
	EnterCriticalSection(lock);
}

void SThread::ReleaseLock(STHREAD_LOCK *lock)
{
	LeaveCriticalSection(lock);
}

static DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	SThread *thread = (SThread *)lpParam;
	STHREAD_CALLBACK *callback = (STHREAD_CALLBACK *)&thread->m_startAddr;
	(*callback)(&thread->m_arg);
	return 0;
}
