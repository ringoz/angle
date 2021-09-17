//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// system_utils_winuwp.cpp: Implementation of OS-specific functions for Windows UWP

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

}  // namespace angle
