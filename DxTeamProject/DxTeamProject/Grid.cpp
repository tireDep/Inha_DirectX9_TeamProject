#include "stdafx.h"
#include "Grid.h"
#include "Pyramid.h"

CGrid::CGrid()
{
}


CGrid::~CGrid()
{
	for each(auto p in m_vecPyramid)
	{
		SafeDelete(p);
	}
	m_vecPyramid.clear();
}

void CGrid::Setup(int nNumHalfTile, float fInterval)
{
	float fMax = nNumHalfTile * fInterval;
	float fMin = -fMax;
	ST_PC_VERTEX v;
	for (int i = 1; i <= nNumHalfTile; i++)
	{
		if (i % 5 == 0)
			v.c = WHITE;
		else
			v.c = D3DCOLOR_XRGB(128, 128, 128);

		v.p = D3DXVECTOR3(fMin, 0, i*fInterval);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i*fInterval);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i*fInterval);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i*fInterval);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i*fInterval, 0, fMin);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval, 0, fMax);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i*fInterval, 0, fMin);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMax);
		m_vecVertex.push_back(v);
	}

	v.c = RED;
	v.p = D3DXVECTOR3(fMin, 0, 0);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0);
	m_vecVertex.push_back(v);

	v.c = GREEN;
	v.p = D3DXVECTOR3(0, fMin, 0);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0);
	m_vecVertex.push_back(v);

	v.c = BLUE;
	v.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); m_vecVertex.push_back(v);

	CPyramid* pPyramid = NULL;
	D3DXMATRIXA16 matR;

	pPyramid = new CPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0F);
	pPyramid->Setup(RED, matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new CPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	pPyramid->Setup(GREEN, matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new CPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	pPyramid->Setup(BLUE, matR);
	m_vecPyramid.push_back(pPyramid);
}

void CGrid::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	for each(auto p in m_vecPyramid)
		p->Render();
}
