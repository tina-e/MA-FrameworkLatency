#pragma once

//#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdint.h>
#include <string>
#include <functional>
#include <vector>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <iostream>
#include <SDKDDKVer.h>

typedef std::string Error;

// BGRA U8 Bitmap
struct Bitmap {
	int Width  = 0;
	int Height = 0;
	std::vector<uint8_t> Buf;
};

// WinDesktopDup hides the gory details of capturing the screen using the
// Windows Desktop Duplication API
class WinDesktopDup {
public:
	Bitmap Latest;
	int OutputNumber = 0;

	~WinDesktopDup();

	Error Initialize();
	void Close();
	int GetColorValueAt(int x, int y);
	bool  HaveFrameLock = false;

private:
	ID3D11Device* D3DDevice = nullptr;
	ID3D11DeviceContext* D3DDeviceContext = nullptr;
	IDXGIOutputDuplication* DeskDupl = nullptr;
	DXGI_OUTPUT_DESC OutputDesc;
	
};