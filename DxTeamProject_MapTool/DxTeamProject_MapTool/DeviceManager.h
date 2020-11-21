#pragma once
#include "Singleton.h"

#define g_pDeviceManager CDeviceManager::GetInstance()
#define g_pD3DDevice CDeviceManager::GetInstance()->GetDevice()
#define g_pD3DPP CDeviceManager::GetInstance()->GetD3DPP()

class CDeviceManager : public CSingleton<CDeviceManager>
{
private:

	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pDevice;
	D3DPRESENT_PARAMETERS m_d3dpp;

public:
	D3DPRESENT_PARAMETERS GetD3DPP();
	LPDIRECT3DDEVICE9 GetDevice();

	void Setup();
	void ResetDevice();
	void Destroy();
};

