#ifndef __STPL_H__
#define __STPL_H__

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501
#include "Windows.h"
#endif

#include <SStr.inl>
#include <SErr.inl>
#include <SFile.inl>

#include <SLock.h>
#include <SThread.h>

#endif
