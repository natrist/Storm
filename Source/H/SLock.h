#ifndef __SLOCK_H__
#define __SLOCK_H__

#ifdef _WIN32	/* _WIN32 */
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501
#include "Windows.h"
#endif	/* _WIN32 */

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

	// The 'h' prefix here stands for HANDLE (Windows specific)
	void *m_opaqueData;
};

class SMutex : public SSyncObject
{
public:
	void Create(int initialOwner, const char *name);
	void Open(const char *name);
	int Release();
	void Close();
};

// TODO: Move to its own file (SCritSect.h, SCritSect.cpp)?
class SCritSect
{
public:
	SCritSect();
	~SCritSect();

	void Enter();
	void Leave();
	void TryEnter();

private:
	// TODO: This might not exist on Linux and Mac systems, so we need to figure out what structure the two platforms use for Critical Sections
	#ifdef _WIN32
	char m_opaqueData[sizeof(RTL_CRITICAL_SECTION)];
	#else
	char m_opaqueData[48];
	#endif // _WIN32
};

#endif // __SLOCK_H__
