#ifndef __SLOCK_H__
#define __SLOCK_H__

#ifdef _WIN32
#include <Windows.h>
#endif /* _WIN32 */

class SSyncObject{
public:
	SSyncObject();
	~SSyncObject();

	void Close();
	void Copy(SSyncObject *rhs);
	SSyncObject *operator=(SSyncObject *rhs);
	int Valid();
	unsigned long Wait(unsigned int timeoutMs);

	void *m_handle;
};

#endif /* __SLOCK_H__ */
