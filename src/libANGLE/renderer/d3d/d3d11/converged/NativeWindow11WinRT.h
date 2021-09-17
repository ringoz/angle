//
// Copyright 2018 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// NativeWindow11WinRT.h: Implementation of NativeWindow11 using ISwapChainPanelNative
// which work in both Win32 and WinRT contexts.

#ifndef LIBANGLE_RENDERER_D3D_D3D11_CONVERGED_NATIVEWINDOW11WINRT_H_
#define LIBANGLE_RENDERER_D3D_D3D11_CONVERGED_NATIVEWINDOW11WINRT_H_

#include "libANGLE/renderer/d3d/d3d11/NativeWindow11.h"

#include <Windows.UI.Xaml.Media.DXInterop.h>
#include <wrl.h>

namespace rx
{

class NativeWindow11WinRT : public NativeWindow11
{
  public:
    NativeWindow11WinRT(EGLNativeWindowType window, bool hasAlpha);
    ~NativeWindow11WinRT() override;

    bool initialize() override;
    bool getClientRect(LPRECT rect) const override;
    bool isIconic() const override;

    HRESULT createSwapChain(ID3D11Device *device,
                            IDXGIFactory *factory,
                            DXGI_FORMAT format,
                            UINT width,
                            UINT height,
                            UINT samples,
                            IDXGISwapChain **swapChain) override;

    void commitChange() override;

    static bool IsValidNativeWindow(EGLNativeWindowType window);

    static bool IsSupportedWinRelease();

  private:
    bool mHasAlpha;

    Microsoft::WRL::ComPtr<ISwapChainPanelNative> mSurface;
};

}  // namespace rx

#endif  // LIBANGLE_RENDERER_D3D_D3D11_CONVERGED_NATIVEWINDOW11WINRT_H_
