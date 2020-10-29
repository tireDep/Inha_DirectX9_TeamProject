#include "stdafx.h"
#include "Light.h"

CLight::CLight()
	: m_LightID(0)
	, m_ltDiffuse(1.0f, 1.0f, 1.0f, 1.0f)
	, m_ltSpecular(1.0f, 1.0f, 1.0f, 1.0f)
	, m_ltAmbient(1.0f, 1.0f, 1.0f, 1.0f)
	, m_vltDirection(0, -1, 0)
{
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
}

CLight::~CLight()
{
}

void CLight::Setup()
{
	m_Light.Type = D3DLIGHT_DIRECTIONAL;
	m_Light.Diffuse = m_ltDiffuse;
	m_Light.Specular = m_ltSpecular;
	m_Light.Ambient = m_ltAmbient;
	m_Light.Direction = m_vltDirection;
	g_pD3DDevice->SetLight(m_LightID, &m_Light);
	g_pD3DDevice->LightEnable(m_LightID, true);
}

void CLight::Setup(D3DXVECTOR3 direction)
{
	m_vltDirection = direction;
	CLight::Setup();
}

void CLight::SetDiffuse(float r, float g, float b)
{
	m_ltDiffuse.r = r;
	m_ltDiffuse.g = g;
	m_ltDiffuse.b = b;
}

void CLight::SetSpecular(float r, float g, float b)
{
	m_ltSpecular.r = r;
	m_ltSpecular.g = g;
	m_ltSpecular.b = b;
}

void CLight::SetAmbient(float r, float g, float b)
{
	m_ltAmbient.r = r;
	m_ltAmbient.g = g;
	m_ltAmbient.b = b;
}