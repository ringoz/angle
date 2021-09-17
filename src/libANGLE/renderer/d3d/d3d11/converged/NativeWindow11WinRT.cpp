//
// Copyright 2018 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// NativeWindow11WinRT.cpp: Implementation of NativeWindow11 using ISwapChainPanelNative
// which work in both Win32 and WinRT contexts.

#include "libANGLE/renderer/d3d/d3d11/converged/NativeWindow11WinRT.h"
#include "libANGLE/renderer/d3d/d3d11/renderer11_utils.h"

#include "common/debug.h"

using namespace Microsoft::WRL;

namespace rx
{

NativeWindow11WinRT::NativeWindow11WinRT(EGLNativeWindowType window, bool hasAlpha)
    : NativeWindow11(window), mHasAlpha(hasAlpha)
{
    reinterpret_cast<IUnknown *>(window)->QueryInterface(mSurface.GetAddressOf());
}

NativeWindow11WinRT::~NativeWindow11WinRT() = default;

bool NativeWindow11WinRT::initialize()
{
    return true;
}

bool NativeWindow11WinRT::getClientRect(LPRECT rect) const
{
    return false;
}

bool NativeWindow11WinRT::isIconic() const
{
    return false;
}

HRESULT NativeWindow11WinRT::createSwapChain(ID3D11Device *device,
                                                  IDXGIFactory *factory,
                                                  DXGI_FORMAT format,
                                                  UINT width,
                                                  UINT height,
                                                  UINT samples,
                                                  IDXGISwapChain **swapChain)
{
    if (device == nullptr || factory == nullptr || swapChain == nullptr || width == 0 ||
        height == 0)
    {
        return E_INVALIDARG;
    }

    HRESULT hr{E_FAIL};

    ComPtr<IDXGIFactory2> factory2;
    hr = factory->QueryInterface(factory2.GetAddressOf());
    if (FAILED(hr))
    {
        return hr;
    }

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.Width                 = width;
    swapChainDesc.Height                = height;
    swapChainDesc.Format                = format;
    swapChainDesc.SampleDesc.Count      = 1;
    swapChainDesc.SampleDesc.Quality    = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_SHADER_INPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.SwapEffect  = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.AlphaMode   = mHasAlpha ? DXGI_ALPHA_MODE_PREMULTIPLIED : DXGI_ALPHA_MODE_IGNORE;

    Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
    hr = factory2->CreateSwapChainForComposition(device, &swapChainDesc, nullptr, &swapChain1);
    if (SUCCEEDED(hr))
    {
        swapChain1.CopyTo(swapChain);
    }

    static IDXGISwapChain1 *lastSwapChain = nullptr;
    if (lastSwapChain)
    {
        DXGI_MATRIX_3X2_F transform;
        if (SUCCEEDED(static_cast<IDXGISwapChain2 *>(lastSwapChain)->GetMatrixTransform(&transform)))
            static_cast<IDXGISwapChain2 *>(swapChain1.Get())->SetMatrixTransform(&transform);
    }

    lastSwapChain = swapChain1.Get();
    return mSurface->SetSwapChain(swapChain1.Get());
}

void NativeWindow11WinRT::commitChange()
{
}

// static
bool NativeWindow11WinRT::IsValidNativeWindow(EGLNativeWindowType window)
{
    ComPtr<ISwapChainPanelNative> swapChainPanelNative;
    return SUCCEEDED(reinterpret_cast<IUnknown *>(window)->QueryInterface(swapChainPanelNative.GetAddressOf()));
}

}  // namespace rx
