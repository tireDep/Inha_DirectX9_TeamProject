#include "stdafx.h"
#include "Orb.h"


COrb::COrb()
{
}


COrb::~COrb()
{
}

void COrb::Setup()
{
	g_pFileLoadManager->FileLoad_Texture("Resource/Sprite/Orb", "Orb_Blue.png", m_pTex0);

	ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0); v.t = D3DXVECTOR2(0, 0.2); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(0, 2, 0); v.t = D3DXVECTOR2(0, 0); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(2, 0, 0); v.t = D3DXVECTOR2(0.2, 0.2); m_vecVertex_Multi.push_back(v);

	v.p = D3DXVECTOR3(2, 2, 0); v.t = D3DXVECTOR2(0.2, 0); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(2, 0, 0); v.t = D3DXVECTOR2(0.2, 0.2); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(0, 2, 0); v.t = D3DXVECTOR2(0, 0); m_vecVertex_Multi.push_back(v);
}

void COrb::Render()
{
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex_Multi.size() / 3,
		&m_vecVertex_Multi[0],
		sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetTexture(0, NULL);
}

void COrb::Update()
{

}

void COrb::SetBillbord()
{
	D3DXMATRIXA16 matBillBoard, matView;
	D3DXMatrixIdentity(&matBillBoard);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	// view 매트릭스를 구해서 y축 회전
	matBillBoard._11 = matView._11;
	matBillBoard._13 = matView._13;
	matBillBoard._31 = matView._31;
	matBillBoard._33 = matView._33;

	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 1, 0, 0);
	matBillBoard *= matT;

	D3DXMatrixInverse(&matBillBoard, NULL, &matBillBoard);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matBillBoard);
}
