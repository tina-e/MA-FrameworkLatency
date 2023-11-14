// WinDupAPI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <d3d11.h>
#include <combaseapi.h>


#include <Windows.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <dxgi.h>


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")


int main() {
    // Initialize DirectX
    ID3D11Device* pDevice = nullptr;
    ID3D11DeviceContext* pDeviceContext = nullptr;

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &pDevice,
        &featureLevel,
        &pDeviceContext
    );

    if (FAILED(hr)) {
        // Handle error
        return -1;
    }

    // Create DXGI Output Duplication
    IDXGIFactory1* pFactory = nullptr;
    hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory);

    if (FAILED(hr)) {
        pDevice->Release();
        pDeviceContext->Release();
        // Handle error
        return -1;
    }


    IDXGIOutput* pOutput = nullptr;
    IDXGIAdapter* pAdapter = nullptr;
    IDXGIOutputDuplication* pDeskDupl = nullptr;

    hr = pAdapter->EnumOutputs(0, &pOutput);

    // Release pAdapter after EnumOutputs call
    pAdapter->Release();

    if (SUCCEEDED(hr)) {
        IDXGIOutput1* pOutput1 = nullptr;
        hr = pOutput->QueryInterface(__uuidof(IDXGIOutput1), (void**)&pOutput1);

        if (SUCCEEDED(hr)) {
            IDXGIOutputDuplication* pDeskDupl = nullptr;
            hr = pOutput1->DuplicateOutput(pDevice, &pDeskDupl);

            // Release pOutput1 after DuplicateOutput call
            pOutput1->Release();
        }

        // Release pOutput after QueryInterface call
        pOutput->Release();
    }

    if (FAILED(hr)) {
        pOutput->Release();
        pFactory->Release();
        pDevice->Release();
        pDeviceContext->Release();
        // Handle error
        return -1;
    }

    // Acquire Next Frame
    IDXGIResource* pDesktopResource = nullptr;
    DXGI_OUTDUPL_FRAME_INFO frameInfo;
    hr = pDeskDupl->AcquireNextFrame(500, &frameInfo, &pDesktopResource);

    if (FAILED(hr)) {
        pDeskDupl->Release();
        pOutput->Release();
        pFactory->Release();
        pDevice->Release();
        pDeviceContext->Release();
        // Handle error
        return -1;
    }

    // Map the Resource
    ID3D11Texture2D* pTexture = nullptr;
    hr = pDesktopResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&pTexture);

    if (FAILED(hr)) {
        pDesktopResource->Release();
        pDeskDupl->Release();
        pOutput->Release();
        pFactory->Release();
        pDevice->Release();
        pDeviceContext->Release();
        // Handle error
        return -1;
    }

    D3D11_MAPPED_SUBRESOURCE resource;
    hr = pDeviceContext->Map(pTexture, 0, D3D11_MAP_READ, 0, &resource);

    if (SUCCEEDED(hr)) {
        // Access pixel data using resource.pData
        pDeviceContext->Unmap(pTexture, 0);
    }

    // Release resources
    pTexture->Release();
    pDesktopResource->Release();
    pDeskDupl->Release();
    pOutput->Release();
    pFactory->Release();
    pDevice->Release();
    pDeviceContext->Release();

    return 0;


    //std::cout << "Hello World!\n";
    ////Variable Declaration
    //IDXGIOutputDuplication* IDeskDupl;
    //IDXGIResource* lDesktopResource = nullptr;
    //DXGI_OUTDUPL_FRAME_INFO IFrameInfo;
    //ID3D11Texture2D* IAcquiredDesktopImage;
    //ID3D11Texture2D* lDestImage;
    //ID3D11DeviceContext* lImmediateContext;
    //UCHAR* g_iMageBuffer = nullptr;

    ////Screen capture start here
    //hr = IDeskDupl->AcquireNextFrame(20, &IFrameInfo, &lDesktopResource);

    //// >QueryInterface for ID3D11Texture2D
    //hr = lDesktopResource->QueryInterface(IID_PPV_ARGS(&lAcquiredDesktopImage));
    //lDesktopResource.Release();

    //// Copy image into GDI drawing texture
    //lImmediateContext->CopyResource(lDestImage, lAcquiredDesktopImage);
    //lAcquiredDesktopImage.Release();
    //lDeskDupl->ReleaseFrame();

    //// Copy GPU Resource to CPU
    //D3D11_TEXTURE2D_DESC desc;
    //lDestImage->GetDesc(&desc);
    //D3D11_MAPPED_SUBRESOURCE resource;
    //UINT subresource = D3D11CalcSubresource(0, 0, 0);
    //lImmediateContext->Map(lDestImage, subresource, D3D11_MAP_READ_WRITE, 0, &resource);

    //std::unique_ptr<BYTE> pBuf(new BYTE[resource.RowPitch * desc.Height]);
    //UINT lBmpRowPitch = lOutputDuplDesc.ModeDesc.Width * 4;
    //BYTE* sptr = reinterpret_cast<BYTE*>(resource.pData);
    //BYTE* dptr = pBuf.get() + resource.RowPitch * desc.Height - lBmpRowPitch;
    //UINT lRowPitch = std::min<UINT>(lBmpRowPitch, resource.RowPitch);

    //for (size_t h = 0; h < lOutputDuplDesc.ModeDesc.Height; ++h)
    //{
    //    memcpy_s(dptr, lBmpRowPitch, sptr, lRowPitch);
    //    sptr += resource.RowPitch;
    //    dptr -= lBmpRowPitch;
    //}

    //lImmediateContext->Unmap(lDestImage, subresource);
    //long g_captureSize = lRowPitch * desc.Height;
    //g_iMageBuffer = new UCHAR[g_captureSize];
    //g_iMageBuffer = (UCHAR*)malloc(g_captureSize);

    ////Copying to UCHAR buffer 
    //memcpy(g_iMageBuffer, pBuf, g_captureSize);
}

