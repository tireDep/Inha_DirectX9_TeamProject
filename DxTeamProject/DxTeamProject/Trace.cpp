#include "stdafx.h"
#include "Trace.h"

CTrace::CTrace()
{
	render = true;
}

CTrace::~CTrace()
{
	
}

void CTrace::Setup(ST_MapData setData)
{
	CItem::Setup(setData);

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
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);

	g_pD3DDevice->SetMaterial(&m_stMtl);

	if (m_pTexture)
		g_pD3DDevice->SetTexture(0, m_pTexture);
	
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

	g_pD3DDevice->SetTexture(0, NULL);
}
