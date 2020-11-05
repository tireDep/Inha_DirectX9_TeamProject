#include "stdafx.h"
#include "cPyramid.h"


cPyramid::cPyramid()
{
	D3DXMatrixIdentity(&m_matR); 
}


cPyramid::~cPyramid()
{
}

void cPyramid::Setup(D3DCOLOR c, D3DXMATRIXA16 & mat)
{
	m_matR = mat; 

	ST_PC_VERTEX v; 

	v.c = c; 
	// : front
	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v); 
	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	// : right
	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);
	// : back 
	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1,  1); m_vecVertex.push_back(v);
	// : left 
	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
	// : bottom 1
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(v);
	// : bottom 2
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1, -1,  1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1,  1); m_vecVertex.push_back(v);
}

void cPyramid::Render()
{
	D3DXMATRIXA16 matWorld, matS; 
	D3DXMatrixScaling(&matS, 0.1, 2.0f, 0.1f); 

	matWorld = matS * m_matR; 

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF); 
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
