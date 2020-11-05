#include "stdafx.h"
#include "ColliderObject.h"
#include "OBB.h"

CColliderObject::CColliderObject()
	: m_vDirection(0, 0, 1)
	, m_fRotY(0.0f)
	, m_pOBB(NULL)
	, m_pCharacterController(NULL)
{

}


CColliderObject::~CColliderObject()
{
	SafeRelease(m_pCharacterController);

	SafeDelete(m_pOBB);
}

void CColliderObject::Setup()
{
	ST_PC_VERTEX v;

	v.p = D3DXVECTOR3(-0.5F, -0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5F, 0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, 0.5F, -0.5F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-0.5F, -0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, 0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, -0.5F, -0.5F);
	m_vecVertex.push_back(v);

	// : back 
	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5F, -0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, 0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5F, 0.5F, 0.5F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-0.5F, -0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, -0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, 0.5F, 0.5F);
	m_vecVertex.push_back(v);

	// : left
	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5F, -0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5F, 0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5F, 0.5F, -0.5F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-0.5F, -0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5F, 0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5F, -0.5F, -0.5F);
	m_vecVertex.push_back(v);

	// : right 
	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(0.5F, -0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, 0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, 0.5F, 0.5F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0.5F, -0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, 0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, -0.5F, 0.5F);
	m_vecVertex.push_back(v);

	// : top 
	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5F, 0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5F, 0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, 0.5F, 0.5F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-0.5F, 0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, 0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, 0.5F, -0.5F);
	m_vecVertex.push_back(v);

	// : bottom
	//	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5F, -0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5F, -0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, -0.5F, -0.5F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-0.5F, -0.5F, 0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, -0.5F, -0.5F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5F, -0.5F, 0.5F);
	m_vecVertex.push_back(v);

	m_pOBB = new COBB;
	m_pOBB->SetupCube(m_vecVertex[0], m_vecVertex[11]);
}

void CColliderObject::Update()
{
	if (m_pCharacterController)
		m_pCharacterController->Update();

	if (m_pOBB)
		m_pOBB->Update(m_pCharacterController ?
			m_pCharacterController->GetTransform() : NULL);
}

void CColliderObject::Render(D3DXCOLOR c)
{
	for (unsigned int i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i].c = c;
	}

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, nullptr);

	if (m_pOBB)
		m_pOBB->OBBBOX_RENDER(c);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_pOBB->m_matWorldTM);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}


COBB* CColliderObject::GetOBB()
{
	return m_pOBB;
}

D3DXVECTOR3 & CColliderObject::GetPosition()
{
	return m_pCharacterController->GetPosition();
}
