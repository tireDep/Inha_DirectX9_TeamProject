#pragma once

#define g_pDeviceManager CDeviceManager::GetInstance()
#define g_pD3DDevice CDeviceManager::GetInstance()->GetDevice()

class CDeviceManager
{
private:
	SingleTone(CDeviceManager);

	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pDevice;
public:
	LPDIRECT3DDEVICE9	GetDevice();
	void Destroy();
};