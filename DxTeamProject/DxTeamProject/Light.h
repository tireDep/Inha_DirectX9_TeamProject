#pragma once
class CLight
{
public:
	CLight();
	~CLight();
private:
	DWORD		m_LightID;
	D3DLIGHT9	m_Light;

	D3DXCOLOR	m_ltDiffuse;
	D3DXCOLOR	m_ltSpecular;
	D3DXCOLOR	m_ltAmbient;

	D3DXVECTOR3	m_vltDirection;
public:
	void Setup();
	void Setup(D3DXVECTOR3 direction);
};