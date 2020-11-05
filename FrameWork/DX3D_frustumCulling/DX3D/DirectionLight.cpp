#include "stdafx.h"
#include "DirectionLight.h"

DirectionLight::DirectionLight() : 
	radian(0.0f)
{
	SetUp();
}

DirectionLight::~DirectionLight()
{

}

void DirectionLight::SetUp()
{
	ZeroMemory(&m_DirLight, sizeof(D3DLIGHT9));

	m_DirLight.Type = D3DLIGHT_DIRECTIONAL;
	m_DirLight.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_DirLight.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f) * 0.3f;
	m_DirLight.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f) * 0.5f;

	D3DXVECTOR3 dir(0.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	m_DirLight.Direction = dir;

	g_pD3DDevice->SetLight(0, &m_DirLight);
	g_pD3DDevice->LightEnable(0, true);

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	// g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	// 조명이 강해짐
}

void DirectionLight::Update()
{
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationX(&matR, D3DX_PI / 360);
	// or D3DXMatrixRotationZ(&matR, D3DX_PI / 180);
	
	D3DXVECTOR3 calcDir = m_DirLight.Direction;
	D3DXVec3TransformCoord(&calcDir, &calcDir, &matR);
	
	m_DirLight.Direction = calcDir;
	g_pD3DDevice->SetLight(0, &m_DirLight);
}

void DirectionLight::Render()
{
}
