#include <SThread.h>

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501
#include "Windows.h"

SThread::SThread(SThreadProc threadProc, void *param)
{
	HANDLE hndl;
	
	hndl = CreateThread(0, 0, threadProc, param, 0, &m_threadId);
	m_opaqueData = hndl;
	// return hndl != 0; maybe assert?
}

void SThread::Join()
{
	Wait(INFINITE);
}
