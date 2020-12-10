#include "stdafx.h"
#include "ColliderObject.h"
#include "OBB.h"

CColliderObject::CColliderObject()
	: m_vDirection(0, 0, 1)
	, m_fRotY(0.0f)
	, m_pOBB(NULL)
	, m_vCPosition(0, 0, 0)
{

}

CColliderObject::~CColliderObject()
{
	SafeDelete(m_pOBB);
}

void CColliderObject::Setup(D3DXVECTOR3 position)
{
	ST_PC_VERTEX v;
	float cubeSize = 1.0f;
	m_vCPosition = position;

	// : front
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// : back 
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);

	// : left
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// : right 
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);

	// : top 
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// : bottom
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);

	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		m_vecVertex[i].isPicked = false;
	}

	/*m_pOBB = new COBB;
	m_pOBB->SetupCube(m_vecVertex[0], m_vecVertex[11],cubeSize);*/
	m_color = WHITE;
}

void CColliderObject::Update(D3DXCOLOR c)
{
	m_color = c;

	D3DXMatrixTranslation(&m_matWorldTM, m_vCPosition.x,
		m_vCPosition.y, m_vCPosition.z);

	//if (m_pOBB)
	//	m_pOBB->Update(&m_matWorldTM);

	for (unsigned int i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i].c = m_color;
	}
}

void CColliderObject::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, nullptr);

	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		if (m_vecVertex[i].isPicked == true)
		{
			/*if (m_pOBB)
				m_pOBB->OBBBOX_RENDER(D3DCOLOR_XRGB(255, 0, 0));*/

		}
	}

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

D3DXCOLOR CColliderObject::GetColor()
{
	return m_color;
}

COBB* CColliderObject::GetOBB()
{
	return m_pOBB;
}

D3DXVECTOR3 & CColliderObject::GetPosition()
{
	return  m_vCPosition;
}

D3DXVECTOR3 & CColliderObject::GetVecPosition(int index)
{
	return m_vecVertex[index].p;
}

int CColliderObject::GetVecSize()
{
	return m_vecVertex.size();
}

void CColliderObject::GetVecPick(bool pick)
{
	for(int i = 0; i < 36; ++i)
	 m_vecVertex[i].isPicked = pick;
}
