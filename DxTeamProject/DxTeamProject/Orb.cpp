#include "stdafx.h"
#include "Orb.h"
#include "OBB.h"

COrb::COrb() : 
	m_Uv_x(0),
	m_Uv_y(0.2),
	m_pTex0(NULL),
	m_pMesh(NULL)
{
	v.t = { 0,0 };
	v.p = D3DXVECTOR3{ 0,0,0 };

	D3DXMatrixIdentity(&m_matWorld);
}


COrb::~COrb()
{

}

void COrb::Setup()
{
	g_pFileLoadManager->FileLoad_Texture("Resource/Sprite/Orb", "제목 없음-1.png", m_pTex0);
	D3DXVECTOR3 size = D3DXVECTOR3(2,2,0);
	v.p = D3DXVECTOR3(0, 0, 0);			  v.t = D3DXVECTOR2(m_Uv_x, m_Uv_y); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(0, size.y, 0);	  v.t = D3DXVECTOR2(m_Uv_x, m_Uv_x); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(size.x, 0, 0);	  v.t = D3DXVECTOR2(m_Uv_y, m_Uv_y); m_vecVertex_Multi.push_back(v);

	v.p = D3DXVECTOR3(size.x, size.y, 0); v.t = D3DXVECTOR2(m_Uv_y, m_Uv_x); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(size.x, 0, 0);	  v.t = D3DXVECTOR2(m_Uv_y, m_Uv_y); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(0, size.y, 0);	  v.t = D3DXVECTOR2(m_Uv_x, m_Uv_x); m_vecVertex_Multi.push_back(v);
	
	D3DXCreateBox(g_pD3DDevice, size.x , size.y , size.z +3, &m_pMesh, NULL);

	D3DXVECTOR3* pVertices;

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	m_pMesh->UnlockVertexBuffer();

	m_pOBB = new COBB;
	m_pOBB->SetupMesh(m_vMin, m_vMax, 0.5f);

	D3DXMatrixTranslation(&m_matWorld, 5, 2, 10);

}

void COrb::Setup(ST_MapData setData)
{
	g_pFileLoadManager->FileLoad_Texture("Resource/Sprite/Orb", "제목 없음-1.png", m_pTex0);
	
	D3DXVECTOR3 size = setData.vScale;
	D3DXMatrixTranslation(&m_matWorld ,
		setData.vTranslate.x , 
		setData.vTranslate.y,
		setData.vTranslate.z);

	//ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0);			  v.t = D3DXVECTOR2(m_Uv_x, m_Uv_y); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(0, size.y, 0);	  v.t = D3DXVECTOR2(m_Uv_x, m_Uv_x); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(size.x, 0, 0);	  v.t = D3DXVECTOR2(m_Uv_y, m_Uv_y); m_vecVertex_Multi.push_back(v);

	v.p = D3DXVECTOR3(size.x, size.y, 0); v.t = D3DXVECTOR2(m_Uv_y, m_Uv_x); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(size.x, 0, 0);	  v.t = D3DXVECTOR2(m_Uv_y, m_Uv_y); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(0, size.y, 0);	  v.t = D3DXVECTOR2(m_Uv_x, m_Uv_x); m_vecVertex_Multi.push_back(v);


	D3DXCreateBox(g_pD3DDevice, size.x + 1, size.y + 1, size.z +3, &m_pMesh, NULL);

	D3DXVECTOR3* pVertices;

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	m_pMesh->UnlockVertexBuffer();

	m_pOBB = new COBB;
	m_pOBB->SetupMesh(m_vMin, m_vMax, 0.5f);

}

void COrb::Render()
{
	D3DMATERIAL9 temp;
	/*D3DXMATRIXA16 matworld, matT;

	D3DXMatrixTranslation(&matT, 5, 0, 5);

	matworld = matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matworld);
*/
	ZeroMemory(&temp,sizeof( D3DMATERIAL9));
	temp.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	temp.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	temp.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	g_pD3DDevice->SetMaterial(&temp);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex_Multi.size() / 3,
		&m_vecVertex_Multi[0],
		sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pD3DDevice->SetTexture(0, NULL);
}

void COrb::Update()
{
	m_Uv_x += 0.2;
	m_Uv_y += 0.2;
	if (m_Uv_x == 1)
	{
		m_Uv_x = 0;
		m_Uv_y = m_Uv_y + 0.2;
	}
	if (m_Uv_y == 1)
	{
		m_Uv_x = 0;
		m_Uv_y = 0.2;
	}

	 m_vecVertex_Multi[0].t = D3DXVECTOR2(m_Uv_x, m_Uv_y);
	 m_vecVertex_Multi[1].t = D3DXVECTOR2(m_Uv_x, m_Uv_x);
	 m_vecVertex_Multi[2].t = D3DXVECTOR2(m_Uv_y, m_Uv_y);
	 
	 m_vecVertex_Multi[3].t = D3DXVECTOR2(m_Uv_y, m_Uv_x);
	 m_vecVertex_Multi[4].t = D3DXVECTOR2(m_Uv_y, m_Uv_y);
	 m_vecVertex_Multi[5].t = D3DXVECTOR2(m_Uv_x, m_Uv_x);

	 
	 m_pOBB->Update(&m_matWorld);
}

void COrb::SetBillbord()
{
	//D3DXMATRIXA16 matBillBoard, matView,matWorld;
	//D3DXMatrixIdentity(&matBillBoard);
	//g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	//// view 매트릭스를 구해서 y축 회전
	//matBillBoard._11 = matView._11;
	//matBillBoard._13 = matView._13;
	//matBillBoard._31 = matView._31;
	//matBillBoard._33 = matView._33;
	//D3DXMATRIXA16 matR,matT2;
	//D3DXMatrixIdentity(&matR);
	//D3DXMatrixIdentity(&matT2);
	//D3DXMatrixTranslation(&matR, 1, 0, 0);
	//D3DXMatrixTranslation(&matT2, 10, 0, 0);
	//matBillBoard *= matR;
	//D3DXMatrixInverse(&matBillBoard, NULL, &matBillBoard);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matBillBoard);

	
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &mView);

	m_pOBB->Render();

	D3DXMatrixInverse(&mInvView, 0, &mView);
	mInvView._41 = m_matWorld._41;
	mInvView._42 = m_matWorld._42 -1;
	mInvView._43 = m_matWorld._43;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mInvView);
}
