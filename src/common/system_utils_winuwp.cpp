//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// system_utils_winuwp.cpp: Implementation of OS-specific functions for Windows UWP

#include "common/debug.h"
#include "system_utils.h"

namespace angle
{

bool SetEnvironmentVar(const char *variableName, const char *value)
{
    // Not supported for UWP
    return false;
}

std::string GetEnvironmentVar(const char *variableName)
{
    // Not supported for UWP
    return "";
}

Library *OpenSharedLibrary(const char *libraryName, SearchType searchType)
{
    return nullptr;
}

Library *OpenSharedLibraryWithExtension(const char *libraryName, SearchType searchType)
{
    return nullptr;
}

Library *OpenSharedLibraryWithExtensionAndGetError(const char *libraryName,
                                                   SearchType searchType,
                                                   std::string *errorOut)
{
    return nullptr;
}

namespace
{
class UwpPageFaultHandler : public PageFaultHandler
{
  public:
    UwpPageFaultHandler(PageFaultCallback callback) : PageFaultHandler(callback) {}
    ~UwpPageFaultHandler() override {}

    bool enable() override;
    bool disable() override;
};

bool UwpPageFaultHandler::disable()
{
    UNIMPLEMENTED();
    return true;
}

bool UwpPageFaultHandler::enable()
{
    UNIMPLEMENTED();
    return true;
}
}  // namespace

bool ProtectMemory(uintptr_t start, size_t size)
{
    UNIMPLEMENTED();
    return true;
}

bool UnprotectMemory(uintptr_t start, size_t size)
{
    UNIMPLEMENTED();
    return true;
}

size_t GetPageSize()
{
    UNIMPLEMENTED();
    return 4096;
}

PageFaultHandler *CreatePageFaultHandler(PageFaultCallback callback)
{
    return new UwpPageFaultHandler(callback);
}
}  // namespace angle
