#include "stdafx.h"
#include "Grid.h"
#include "Gizmo.h"

CGrid::CGrid()
{
}

CGrid::~CGrid()
{
	for each(auto p in m_vecGizmo)
	{
		SafeDelete(p);
	}

	m_vecGizmo.clear();
}

void CGrid::Setup(int nNumHalfTile, float fInterval)
{
	float fMax = nNumHalfTile * fInterval;
	float fMin = -fMax;
	ST_PN_VERTEX v;
	for (int i = 1; i <= nNumHalfTile; ++i)
	{
		v.n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
		v.p = D3DXVECTOR3(fMin, 0, i*fInterval); m_vecVertex.push_back(v); 
		v.p = D3DXVECTOR3(fMax, 0, i*fInterval); m_vecVertex.push_back(v);
	
		v.p = D3DXVECTOR3(fMin, 0, -i*fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i*fInterval); m_vecVertex.push_back(v);
		
		v.p = D3DXVECTOR3(i*fInterval , 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval, 0, fMax); m_vecVertex.push_back(v);
		
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMax); m_vecVertex.push_back(v);
	}
	
	v.n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v.p = D3DXVECTOR3(fMin, 0, 0); m_vecVertex.push_back(v); 
	v.p = D3DXVECTOR3(fMax, 0, 0); m_vecVertex.push_back(v);
	
	v.p = D3DXVECTOR3(0,fMin, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0,fMax, 0); m_vecVertex.push_back(v);
	
	v.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); m_vecVertex.push_back(v);

	CGizmo* gizmo = NULL;
	D3DXMATRIXA16 matR;

	gizmo = new CGizmo;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0F);
	gizmo->Setup(D3DCOLOR_XRGB(255, 0, 0), matR);
	m_vecGizmo.push_back(gizmo);

	gizmo = new CGizmo;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	gizmo->Setup(D3DCOLOR_XRGB(0, 255, 0), matR);
	m_vecGizmo.push_back(gizmo);

	gizmo = new CGizmo;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	gizmo->Setup(D3DCOLOR_XRGB(0, 0, 255), matR);
	m_vecGizmo.push_back(gizmo);

	ZeroMemory(&m_mtrl, sizeof(D3DMATERIAL9));
	m_mtrl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_mtrl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_mtrl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void CGrid::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetMaterial(&m_mtrl);
	g_pD3DDevice->SetTexture(0, NULL);

	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(ST_PN_VERTEX));

	for each (auto p in m_vecGizmo)
		p->Render();
}
