#include "stdafx.h"
#include "ColliderObject.h"
#include "OBB.h"

CColliderObject::CColliderObject()
	: m_vDirection(0, 0, 1)
	, m_fRotY(0.0f)
	, m_pOBB(NULL)
	, m_vCPosition(0, 0, 0)
	, m_pCharacterController(NULL)
{

}


CColliderObject::~CColliderObject()
{
	SafeRelease(m_pCharacterController);

	SafeDelete(m_pOBB);
}

void CColliderObject::Setup(D3DXVECTOR3 position)
{
	ST_PC_VERTEX v;
	float cubeSize = 0.5f;
	m_vCPosition = position;

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	// : back 
	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	// : left
	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	// : right 
	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	// : top 
	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	// : bottom
	//	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);



	m_pOBB = new COBB;
	m_pOBB->SetupCube(m_vecVertex[0], m_vecVertex[11]);
}

void CColliderObject::Update(D3DXCOLOR c)
{
	D3DXMatrixTranslation(&m_pOBB->m_matWorldTM, m_vCPosition.x,
		m_vCPosition.y, m_vCPosition.z);

	if (m_pCharacterController)
		m_pCharacterController->Update();

	if (m_pOBB)
		m_pOBB->Update(m_pCharacterController ?
			m_pCharacterController->GetTransform() : NULL);

	for (unsigned int i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i].c = c;
	}
}

void CColliderObject::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, nullptr);

	D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);
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
