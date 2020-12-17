#include "stdafx.h"
#include "Orb.h"
#include "OBB.h"

COrb::COrb() :
	m_preAni(0.0f),
	m_nowAni(0.0f),
	m_UvX(0.0f),
	m_UvY(0.2f)
	,render(true)
{
}

COrb::~COrb()
{
}

void COrb::Setup()
{
	/*g_pFileLoadManager->FileLoad_Texture("Resource/Sprite/Orb", "제목 없음-1.png", m_pTex0);
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

	D3DXMatrixTranslation(&m_matWorld, 5, 2, 10);*/
}

void COrb::Setup(ST_MapData setData)
{
	CItem::Setup(setData);

	ST_PT_VERTEX v;
	float f = m_vScale.x;
	v.p = D3DXVECTOR3(-f, -f, 0.05);	v.t = D3DXVECTOR2(m_UvX, m_UvY); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-f, f, 0.05);	v.t = D3DXVECTOR2(m_UvX, m_UvX);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(f, -f, 0.05);	v.t = D3DXVECTOR2(m_UvY, m_UvY);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(f, f, 0.05);		v.t = D3DXVECTOR2(m_UvY, m_UvX); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(f, -f, 0.05);		v.t = D3DXVECTOR2(m_UvY, m_UvY); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-f, f, 0.05);		v.t = D3DXVECTOR2(m_UvX, m_UvX); m_vecVertex.push_back(v);

	// g_pFileLoadManager->FileLoad_Texture("Resource/Sprite/Orb", "제목 없음-1.png", m_pTex0);
	// 
	// D3DXVECTOR3 size = setData.vScale;
	// D3DXMatrixTranslation(&m_matWorld ,
	// 	setData.vTranslate.x , 
	// 	setData.vTranslate.y,
	// 	setData.vTranslate.z);
	// 
	// //ST_PT_VERTEX v;
	// v.p = D3DXVECTOR3(0, 0, 0);			  v.t = D3DXVECTOR2(m_Uv_x, m_Uv_y); m_vecVertex_Multi.push_back(v);
	// v.p = D3DXVECTOR3(0, size.y, 0);	  v.t = D3DXVECTOR2(m_Uv_x, m_Uv_x); m_vecVertex_Multi.push_back(v);
	// v.p = D3DXVECTOR3(size.x, 0, 0);	  v.t = D3DXVECTOR2(m_Uv_y, m_Uv_y); m_vecVertex_Multi.push_back(v);
	// 
	// v.p = D3DXVECTOR3(size.x, size.y, 0); v.t = D3DXVECTOR2(m_Uv_y, m_Uv_x); m_vecVertex_Multi.push_back(v);
	// v.p = D3DXVECTOR3(size.x, 0, 0);	  v.t = D3DXVECTOR2(m_Uv_y, m_Uv_y); m_vecVertex_Multi.push_back(v);
	// v.p = D3DXVECTOR3(0, size.y, 0);	  v.t = D3DXVECTOR2(m_Uv_x, m_Uv_x); m_vecVertex_Multi.push_back(v);
	// 
	// 
	// D3DXCreateBox(g_pD3DDevice, size.x + 1, size.y + 1, size.z +3, &m_pMesh, NULL);
	// 
	// D3DXVECTOR3* pVertices;
	// 
	// m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	// D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	// m_pMesh->UnlockVertexBuffer();
	// 
	// m_pOBB = new COBB;
	// m_pOBB->SetupMesh(m_vMin, m_vMax, 0.5f);
	// 
	// ST_PT_VERTEX v;
	// float f = m_vScale.x;
	// v.p = D3DXVECTOR3(-f, -f, 0.05);	v.t = D3DXVECTOR2(m_UvX, m_UvY); m_vecVertex.push_back(v);
	// v.p = D3DXVECTOR3(-f, f, 0.05);	v.t = D3DXVECTOR2(m_UvX, m_UvX); m_vecVertex.push_back(v);
	// v.p = D3DXVECTOR3(f, -f, 0.05);	v.t = D3DXVECTOR2(m_UvY, m_UvY); m_vecVertex.push_back(v);
	// 
	// v.p = D3DXVECTOR3(f, f, 0.05);		v.t = D3DXVECTOR2(m_UvY, m_UvX); m_vecVertex.push_back(v);
	// v.p = D3DXVECTOR3(f, -f, 0.05);		v.t = D3DXVECTOR2(m_UvY, m_UvY); m_vecVertex.push_back(v);
	// v.p = D3DXVECTOR3(-f, f, 0.05);		v.t = D3DXVECTOR2(m_UvX, m_UvX); m_vecVertex.push_back(v);
}

void COrb::Render()
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

	 // m_pOBB->Update(&GetmatWorld());
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

	
	D3DXMATRIXA16 matView, matInvView;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matInvView, 0, &matView);
	matInvView._41 = GetmatWorld()._41;
	matInvView._42 = GetmatWorld()._42;
	matInvView._43 = GetmatWorld()._43;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matInvView);

	
	if (player == true)
	{
		if (m_strConditionName != "")
		{
			ST_EVENT msg;
			msg.eventType = EventType::eConditionChange;
			msg.isCondition = false;
			msg.conditionName = m_strObjName;

			g_pEventManager->CheckEvent(msg);
		}
		render = false;
		g_pObjectManager->RemoveObject(m_pOBB);
			
	}
	
		
	
}
