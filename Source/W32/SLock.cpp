#include "SLock.h"
#include <cstdio>

/* SSyncObject */

SSyncObject::SSyncObject()
{
	m_opaqueData = 0;
}

SSyncObject::SSyncObject(SSyncObject *rhs)
{
	Copy(rhs);
}

SSyncObject::~SSyncObject()
{
	if (m_opaqueData)
		Close();
}

SSyncObject *SSyncObject::operator=(SSyncObject *rhs)
{
	Close();
	Copy(rhs);
	return this;
}

void SSyncObject::Close()
{
	if (m_opaqueData)
	{
		CloseHandle(m_opaqueData);
		m_opaqueData = 0;
	}
}

void SSyncObject::Copy(SSyncObject *rhs)
{
	HANDLE hTargetProcessHandle;
	HANDLE hSourceProcessHandle;
	HANDLE hSourceHandle;

	hTargetProcessHandle = GetCurrentProcess();
	hSourceHandle = (HANDLE)rhs->m_opaqueData;
	hSourceProcessHandle = GetCurrentProcess();
	if (!DuplicateHandle(hSourceProcessHandle, hSourceHandle, hTargetProcessHandle, (LPHANDLE)m_opaqueData, 0, 0, 2u))
	{
		// TODO: SErrDisplayError("Something went terribly wrong!", "Error");
		printf("Something went wrong in SSyncObject::Copy()!!\n");
		printf("\tGetLastError() returned %d\n", GetLastError());
	}
}

DWORD SSyncObject::Wait(unsigned int timeoutMs)
{
	return WaitForSingleObject(m_opaqueData, timeoutMs);
}

bool SSyncObject::Valid()
{
	return m_opaqueData != 0;
}

/* SMutex */

void SMutex::Create(int initialOwner, const char* name)
{
	m_opaqueData = CreateMutexA(0, initialOwner, name);
}

void SMutex::Open(const char* name)
{
	;
}

bool SMutex::Release()
{
	return ReleaseMutex(m_opaqueData);
}

void SMutex::Close()
{
	SSyncObject::Close();
}

/* SCritSect */

SCritSect::SCritSect()
{
	InitializeCriticalSection((LPCRITICAL_SECTION)this);
}

SCritSect::~SCritSect()
{
	DeleteCriticalSection((LPCRITICAL_SECTION)this);
}

void SCritSect::Enter()
{
	EnterCriticalSection((LPCRITICAL_SECTION)this);
}

void SCritSect::Leave()
{
	LeaveCriticalSection((LPCRITICAL_SECTION)this);
}

void SCritSect::TryEnter()
{
	TryEnterCriticalSection((LPCRITICAL_SECTION)this);
}
