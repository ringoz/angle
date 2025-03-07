//
// Copyright 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// tls.h: Simple cross-platform interface for thread local storage.

#ifndef COMMON_TLS_H_
#define COMMON_TLS_H_

#include "common/angleutils.h"
#include "common/platform.h"

#ifdef ANGLE_PLATFORM_WINDOWS
#    include <windows.h>
#endif

namespace gl
{
class Context;
}

#ifdef ANGLE_PLATFORM_WINDOWS
typedef DWORD TLSIndex;
#    define TLS_INVALID_INDEX (TLS_OUT_OF_INDEXES)
#elif defined(ANGLE_PLATFORM_POSIX)
#    include <errno.h>
#    include <pthread.h>
#    include <semaphore.h>
typedef pthread_key_t TLSIndex;
#    define TLS_INVALID_INDEX (static_cast<TLSIndex>(-1))
#else
#    error Unsupported platform.
#endif

using PthreadKeyDestructor = void (*)(void *);
TLSIndex CreateTLSIndex(PthreadKeyDestructor destructor);
bool DestroyTLSIndex(TLSIndex index);

bool SetTLSValue(TLSIndex index, void *value);
void *GetTLSValue(TLSIndex index);

#endif  // COMMON_TLS_H_
