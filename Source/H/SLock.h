#ifndef _SLOCK__H_
#define _SLOCK__H_
#include "Windows.h"

class SSyncObject
{
public:
	~SSyncObject();
	SSyncObject *operator=(SSyncObject *rhs);
	unsigned long Wait(unsigned int timeoutMs);

protected:
	SSyncObject();
	SSyncObject(SSyncObject *rhs);
	bool Valid();
	void Copy(SSyncObject *rhs);
	void Close();

	void *m_opaqueData;
};

class SMutex : public SSyncObject
{
public:
	void Create(int initialOwner, const char *name);
	void Open(const char *name);
	bool Release();
	void Close();
};

class SCritSect
{
public:
	SCritSect();
	~SCritSect();

	void Enter();
	void Leave();
	void TryEnter();

private:
	char m_opaqueData[24]; // TODO: different sizes on 32bit and 64bit platforms. (and not portable on linux?)
};

#endif // _SLOCK__H_
