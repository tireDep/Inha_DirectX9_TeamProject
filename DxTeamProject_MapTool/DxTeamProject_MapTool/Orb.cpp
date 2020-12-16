#include "stdafx.h"
#include "Orb.h"

COrb::COrb()
{
}

COrb::~COrb()
{
}

void COrb::Setup(ST_MapData setData)
{
	CItem::Setup(setData);

	ST_PT_VERTEX v;
	float f = m_vScale.x;
	v.p = D3DXVECTOR3(-f, -f, 0.05);	v.t = D3DXVECTOR2(m_UvX, m_UvY); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-f,  f, 0.05);	v.t = D3DXVECTOR2(m_UvX, m_UvX); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( f, -f, 0.05);	v.t = D3DXVECTOR2(m_UvY, m_UvY); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(f,  f, 0.05);		v.t = D3DXVECTOR2(m_UvY, m_UvX); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(f, -f, 0.05);		v.t = D3DXVECTOR2(m_UvY, m_UvY); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-f, f, 0.05);		v.t = D3DXVECTOR2(m_UvX, m_UvX); m_vecVertex.push_back(v);
}

void COrb::Render()
{
	IObject::Render_OBB_Box();

	SetBillBoard();

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);

	g_pD3DDevice->SetMaterial(&m_pMtrl);

	if (m_pTexture)
		g_pD3DDevice->SetTexture(0, m_pTexture);
	if (!m_isPick && !m_isClick || !m_pShader)
	{
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));
	}
	else
	{
		SetShader(GetmatWorld());

		D3DXVECTOR4 color;
		if (GetSpriteIndex() == 0)		color = D3DXVECTOR4(0, 0, 0, 1);
		else if (GetSpriteIndex() == 1)	color = D3DXVECTOR4(1, 1, 1, 1);
		else if (GetSpriteIndex() == 2)	color = D3DXVECTOR4(1, 1, 0, 1);
		else if (GetSpriteIndex() == 3)	color = D3DXVECTOR4(0, 1, 0, 1);
		else if (GetSpriteIndex() == 4)	color = D3DXVECTOR4(1, 0, 0, 1);
		else if (GetSpriteIndex() == 5)	color = D3DXVECTOR4(0, 0, 1, 1);

		SetShaderColor(D3DXVECTOR4(0, 0, 0, 0), color);
		IObject::Render();
	}

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

	g_pD3DDevice->SetTexture(0, NULL);
}

void COrb::SetBillBoard()
{
	D3DXMATRIXA16 matView,matInvView;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matInvView, 0, &matView);
	matInvView._41 = GetmatWorld()._41;
	matInvView._42 = GetmatWorld()._42;
	matInvView._43 = GetmatWorld()._43;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matInvView);
}

void COrb::SetDiffScale(D3DXVECTOR3 set)
{
	IObject::SetDiffScale(set);

	float f = m_vScale.x;
	m_vecVertex[0].p = D3DXVECTOR3(-f, -f, 0.05);
	m_vecVertex[1].p = D3DXVECTOR3(-f,  f, 0.05);
	m_vecVertex[2].p = D3DXVECTOR3( f, -f, 0.05);
	m_vecVertex[3].p = D3DXVECTOR3( f,  f, 0.05);
	m_vecVertex[4].p = D3DXVECTOR3( f, -f, 0.05);
	m_vecVertex[5].p = D3DXVECTOR3(-f,  f, 0.05);
}
