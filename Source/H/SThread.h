#ifndef __STHREAD_H__
#define __STHREAD_H__

#include "SLock.h"

typedef unsigned long(__stdcall *SThreadProc)(void *);

class SThread : public SSyncObject
{
public:
	SThread(SThreadProc threadProc, void *param);
	void Join();

private:
	unsigned long m_threadId;
};

#endif /* __STHREAD_H__ */
