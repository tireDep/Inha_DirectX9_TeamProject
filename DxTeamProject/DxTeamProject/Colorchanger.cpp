#include "stdafx.h"
#include "Colorchanger.h"
#include "MeshTile.h"
Color_changer::Color_changer()
    : m_pMesh(NULL)
	, istrue(false)
{
    D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	ZeroMemory(&m_stMtlSphere2, sizeof(D3DMATERIAL9));
}

Color_changer::~Color_changer()
{
    SafeRelease(m_pMesh);
	
}

void Color_changer::Setup()
{
    D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMesh, NULL);
	
	m_position = D3DXVECTOR3(0, 10, 0);
	m_direction = D3DXVECTOR3(1, 0, 0);

 
	m_stMtlSphere.Ambient = RED;
	m_stMtlSphere.Diffuse = RED;
	m_stMtlSphere.Specular = RED;

	
		
	D3DXCreateBox(g_pD3DDevice, 1.5f, 0.3f, 0.3f, &m_pBarrel, NULL);
	
	
	
}

void Color_changer::Render()
{
	
	g_pD3DDevice->SetMaterial(&m_stMtlSphere);
    g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
    m_pMesh->DrawSubset(0);
	m_pBarrel->DrawSubset(0);
}

void Color_changer::Update()
{
	if (istrue == false)
	{
	
		m_position.y += 0.001f;
		if(m_position.y > 5)
			istrue = true;
		
	}
	else if(istrue == true)
	{
		m_position.y -= 0.001f;
		if (m_position.y < -5)
			istrue = false;
	}

	D3DXMatrixTranslation(&m_matT, m_position.x, m_position.y, m_position.z);
	m_matWorld = m_matT;

}



bool Color_changer::RayCheck(MeshTile& meshtile)
{
	BOOL Hit = false;
	DWORD FaceIndex;
	float U, V;
	float Dist;
	D3DXVECTOR3 rayOrigin = m_position;
	rayOrigin.x -= meshtile.GetMatWorld()._41;
	rayOrigin.y -= meshtile.GetMatWorld()._42;
	rayOrigin.z -= meshtile.GetMatWorld()._43;

	D3DXIntersect(meshtile.GetMesh(), &rayOrigin, &m_direction,
		&Hit, &FaceIndex, &U, &V, &Dist, NULL, NULL);
	if (Hit)
	{
		m_stMtlSphere2.Ambient = YELLOW;
		m_stMtlSphere2.Diffuse = YELLOW;
		m_stMtlSphere2.Specular = YELLOW;
		return true;
	}
	else
	{
		m_stMtlSphere2.Ambient = RED;
		m_stMtlSphere2.Diffuse = RED;
		m_stMtlSphere2.Specular = RED;
		return false;

	}
	
}
