#include "stdafx.h"
#include "DeviceManager.h"

CDeviceManager::CDeviceManager()
	: m_pD3D(NULL)
	, m_pDevice(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	// ÇÈ¼¿ Æ÷¸ä
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	m_pDevice = 0;
	HRESULT hr = m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		vp,
		&d3dpp,
		&m_pDevice
	);

	if (FAILED(hr))
	{
		MessageBox(0, L"CreateDevice Fail", L"ERROR", MB_OK);
		return;
	}
}

CDeviceManager::~CDeviceManager()
{
	Destroy();
}

LPDIRECT3DDEVICE9 CDeviceManager::GetDevice()
{
	return m_pDevice;
}

void CDeviceManager::Destroy()
{
	SafeRelease(m_pD3D);
	SafeRelease(m_pDevice);
}