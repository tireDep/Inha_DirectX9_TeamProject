#include <assert.h>
#include "stdafx.h"
#include "DeviceManager.h"

CDeviceManager::CDeviceManager() : 
	m_pD3D(NULL),
	m_pDevice(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	m_pD3D->GetDeviceCaps(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		&caps
	);

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	// D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&m_d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	m_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	// ÇÈ¼¿ Æ÷¸ä
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.hDeviceWindow = g_hWnd;
	m_d3dpp.Windowed = true;
	m_d3dpp.EnableAutoDepthStencil = true;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dpp.Flags = 0;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	m_pDevice = 0;
	HRESULT hr = m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		vp,
		&m_d3dpp,
		&m_pDevice
	);

	if (FAILED(hr))
	{
		MessageBox(0, L"CreatDeivce Fail", L"ERROR", MB_OK);
		return;
	}
}

CDeviceManager::~CDeviceManager()
{
	Destroy();
}

D3DPRESENT_PARAMETERS CDeviceManager::GetD3DPP()
{
	return m_d3dpp;
}

LPDIRECT3DDEVICE9 CDeviceManager::GetDevice()
{
	return m_pDevice;
}

void CDeviceManager::ResetDevice()
{
	// m_d3dpp.BackBufferWidth = LOWORD(lParam);
	// m_d3dpp.BackBufferHeight = HIWORD(lParam);

	HRESULT hr = g_pD3DDevice->Reset(&g_pD3DPP);
	if (hr == D3DERR_INVALIDCALL)
		assert(0);
}

void CDeviceManager::Destroy()
{
	SafeRelease(m_pD3D);
	SafeRelease(m_pDevice);
}
