#include "stdafx.h"
#include "Orb.h"
#include "OBB.h"

COrb::COrb() :
	m_preAni(0.0f),
	m_nowAni(0.0f),
	m_UvX(0.0f),
	m_UvY(0.2f),
	render(true),
	pBox(false), 
	pCylinder(false),
	pSphere(false),
	player(false)
{
}

COrb::~COrb()
{
}

void COrb::Setup()
{
}

void COrb::Setup(ST_MapData setData)
{
	CItem::Setup(setData);

	ST_PT_VERTEX v;
	float f = 1.0f;
	v.p = D3DXVECTOR3(-f, -f, 0.05);	v.t = D3DXVECTOR2(m_UvX, m_UvY); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-f, f, 0.05);		v.t = D3DXVECTOR2(m_UvX, m_UvX);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(f, -f, 0.05);		v.t = D3DXVECTOR2(m_UvY, m_UvY);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(f, f, 0.05);		v.t = D3DXVECTOR2(m_UvY, m_UvX); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(f, -f, 0.05);		v.t = D3DXVECTOR2(m_UvY, m_UvY); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-f, f, 0.05);		v.t = D3DXVECTOR2(m_UvX, m_UvX); m_vecVertex.push_back(v);
}

void COrb::Render()
{
	if (player == true) // Ãæµ¹
	{
		render = false;
		g_pGameManager->SetGetOrb(m_strConditionName);
		g_pObjectManager->RemoveObject(m_pOBB);
	}

	if (render == true)
	{
		SetBillbord();

		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		g_pD3DDevice->SetMaterial(&m_stMtl);

		g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
		g_pD3DDevice->SetTexture(0, m_pTexture);

		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));

		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

		g_pD3DDevice->SetTexture(0, NULL);
	}
}

void COrb::Update(float duration)
{
	m_nowAni += duration;
	if (m_nowAni - m_preAni > 0.0001f)
	{
		m_preAni = m_nowAni;
		m_nowAni = 0;

		m_UvX += 0.2;
		m_UvY += 0.2;

		if (m_UvX == 1)
		{
			m_UvX = 0;
			m_UvY = m_UvY + 0.2;
		}
		if (m_UvY == 1)
		{
			m_UvX = 0;
			m_UvY = 0.2;
		}

		m_vecVertex[0].t = D3DXVECTOR2(m_UvX, m_UvY);
		m_vecVertex[1].t = D3DXVECTOR2(m_UvX, m_UvX);
		m_vecVertex[2].t = D3DXVECTOR2(m_UvY, m_UvY);
		m_vecVertex[3].t = D3DXVECTOR2(m_UvY, m_UvX);
		m_vecVertex[4].t = D3DXVECTOR2(m_UvY, m_UvY);
		m_vecVertex[5].t = D3DXVECTOR2(m_UvX, m_UvX);
	}
}

void COrb::SetBillbord()
{
	D3DXMATRIXA16 matView, matInvView;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matInvView, 0, &matView);
	matInvView._41 = GetmatWorld()._41;
	matInvView._42 = GetmatWorld()._42;
	matInvView._43 = GetmatWorld()._43;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matInvView);
}