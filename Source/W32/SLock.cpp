#include <SLock.h>
#include <SErr.inl>
#include <stdio.h>

SSyncObject::SSyncObject()
{
	m_handle = 0;
}

SSyncObject::~SSyncObject()
{
	CloseHandle(m_handle);
}

void SSyncObject::Close()
{
	if (m_handle)
	{
		CloseHandle(m_handle);
		m_handle = 0;
	}
}

// Copy *rhs into SSyncObject *this
void SSyncObject::Copy(SSyncObject *rhs)
{
	void *sourceH = rhs->m_handle;
	if (!DuplicateHandle(GetCurrentProcess(), sourceH, GetCurrentProcess(), (LPHANDLE)m_handle, 0, 0, 2u))
	{
		SErrDisplayError("SSyncObject::Copy: DuplicateHandle failed", "Fatal Error");
		printf("\t%d\n", GetLastError());
		// TODO:
		// Force quit the program
	}
}

int SSyncObject::Valid()
{
	return m_handle != 0;
}

unsigned long SSyncObject::Wait(unsigned int timeoutMs)
{
	return WaitForSingleObject(m_handle, timeoutMs);
}

SSyncObject * SSyncObject::operator=(SSyncObject *rhs)
{
	Close();
	Copy(rhs);
	return this;
}
