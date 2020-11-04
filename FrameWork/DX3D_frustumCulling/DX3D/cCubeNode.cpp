#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	: m_fRotDeltaX(0.0f)
	, m_pParentWorldTM(NULL)
	, m_vLocalPos(0, 0, 0)
	, m_fRotX(0.0f) 
{
	D3DXMatrixIdentity(&m_matLocalTM); 
	D3DXMatrixIdentity(&m_matWorldTM); 
}


cCubeNode::~cCubeNode()
{
}

void cCubeNode::AddChild(cCubeNode * pChild)
{
	pChild->m_pParentWorldTM = &m_matWorldTM; 
	m_vecChild.push_back(pChild); 
}

void cCubeNode::Destroy()
{
	for each(auto p  in m_vecChild)
	{
		p->Destroy(); 
	}
	delete this; 
}

void cCubeNode::Setup()
{
	cCubePNT::Setup(); 
}

void cCubeNode::Update()
{
	cCubePNT::Update(); 

	// >> 걷는 경우에만 애니메이션 실행
	if (GetKeyState('W') >= 0 && GetKeyState('S') >= 0)
	{
		m_fRotX = 0;
	}
	else
	{
		m_fRotX += m_fRotDeltaX;
		if (m_fRotX > D3DX_PI / 6.0F)
		{
			m_fRotX = D3DX_PI / 6.0F;
			m_fRotDeltaX *= -1;
		}
		if (m_fRotX < -D3DX_PI / 6.0F)
		{
			m_fRotX = -D3DX_PI / 6.0F;
			m_fRotDeltaX *= -1;
		}
	}


	D3DXMATRIXA16 matR, matT; 
	D3DXMatrixIdentity(&matR); 
	D3DXMatrixIdentity(&matT);

	D3DXMatrixRotationX(&matR, m_fRotX); 

	D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z); 
	m_matLocalTM = matR * matT; 

	m_matWorldTM = m_matLocalTM; 
	if (m_pParentWorldTM)
	{
		m_matWorldTM *= *m_pParentWorldTM; 
	}

	for each(auto p in m_vecChild)
	{
		p->Update(); // cCubeNode -> Update()
	}
}

void cCubeNode::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM); 
	cCubePNT::Render(); // 실제로 그려주는 곳
	for each(auto p in m_vecChild)
	{
		p->Render();	// cCubeNode -> Render()
	}
}
