#include "SRand.h"

#include <Windows.h>
#include <Wincrypt.h>
#pragma comment(lib, "crypt32.lib")

int RandomBytes(int length, char *buffer)
{
	HCRYPTPROV hCryptProv;
	int ret;

	CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0);
	ret = CryptGenRandom(hCryptProv, length, (BYTE *)buffer);
	CryptReleaseContext(hCryptProv, 0);
	return ret;
}
