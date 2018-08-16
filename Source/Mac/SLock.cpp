#include <SLock.h>

SSyncObject::SSyncObject()
{
	m_handle = 0;
}

SSyncObject::~SSyncObject()
{
	;
}

void SSyncObject::Close()
{
	;
}

// Copy *rhs into SSyncObject *this
void SSyncObject::Copy(SSyncObject *rhs)
{
	;
}

int SSyncObject::Valid()
{
	return m_handle != 0;
}

unsigned long SSyncObject::Wait(unsigned int timeoutMs)
{
	;
}

SSyncObject * SSyncObject::operator=(SSyncObject *rhs)
{
	return 0;
}
