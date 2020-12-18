#include "stdafx.h"
#include "Trace.h"

CTrace::CTrace()
{
}

CTrace::~CTrace()
{
}

void CTrace::Setup(ST_MapData setData)
{
	CItem::Setup(setData);

	m_vecColorTag = setData.vecColorTag;

	ST_PT_VERTEX v;
	float f = m_vScale.x;
	v.p = D3DXVECTOR3(-f, 0, -f);	v.t = D3DXVECTOR2(1, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-f, 0, f);	v.t = D3DXVECTOR2(0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(f, 0, f);		v.t = D3DXVECTOR2(0, 1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-f, 0, -f);	v.t = D3DXVECTOR2(1, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(f, 0, f);		v.t = D3DXVECTOR2(0, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(f, 0, -f);	v.t = D3DXVECTOR2(1, 1); m_vecVertex.push_back(v);
}

void CTrace::Render()
{
	IObject::Render_OBB_Box();

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

		SetShaderColor(D3DXVECTOR4(0.5, 0.5, 0.5, 1), color);
		IObject::Render();
	}

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

	g_pD3DDevice->SetTexture(0, NULL);
}

void CTrace::SetDiffScale(D3DXVECTOR3 set)
{
	IObject::SetDiffScale(set);
	m_vScale.y = 0.5;

	float f = m_vScale.x * 0.5;
	m_vecVertex[0].p = D3DXVECTOR3(-f, 0, -f);
	m_vecVertex[1].p = D3DXVECTOR3(-f, 0, f);
	m_vecVertex[2].p = D3DXVECTOR3(f, 0, f);
	m_vecVertex[3].p = D3DXVECTOR3(-f, 0, -f);
	m_vecVertex[4].p = D3DXVECTOR3(f, 0, f);
	m_vecVertex[5].p = D3DXVECTOR3(f, 0, -f);
}

void CTrace::SetTranslate(D3DXVECTOR3 set)
{
	if (!g_pObjectManager->GetIsAnotherPos(set))
	{
		set.y += 0.15;
	}

	IObject::SetTranslate(set);
}
