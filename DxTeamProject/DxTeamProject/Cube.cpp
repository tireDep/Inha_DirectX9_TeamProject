#include "stdafx.h"
#include "Cube.h"

CCube::	CCube() 
	: m_pMeshCube(NULL)
{
	ZeroMemory(&m_stMtlCube, sizeof(D3DMATERIAL9));
	Setup();
}

CCube::CCube(D3DXVECTOR3 center)
{
	m_vCenter = center;
	Setup();
}

CCube::~CCube()
{
	SafeRelease(m_pMeshCube);
}

void CCube::Setup()
{
	m_strName = string("Cube") + to_string(m_nRefCount);
	m_isClicked = false;
	m_isPicked = false;
	
	D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMeshCube, NULL);
	ZeroMemory(&m_stMtlCube, sizeof(D3DMATERIAL9));
	m_stMtlCube.Ambient =  m_color;
	m_stMtlCube.Diffuse =  m_color;
	m_stMtlCube.Specular = m_color;

	{
		D3DXVECTOR3 v;
		// : front
		v = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, 0.5f, -0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, 0.5f, -0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, -0.5f, -0.5f);	m_vecPos.push_back(v);
		// :back
		v = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, 0.5f, 0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, 0.5f, 0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, -0.5f, 0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, 0.5f, 0.5f);		m_vecPos.push_back(v);
		// : left
		v = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, 0.5f, 0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);	m_vecPos.push_back(v);
		// : right 
		v = D3DXVECTOR3(0.5f, -0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, 0.5f, -0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, 0.5f, 0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, -0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, 0.5f, 0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, -0.5f, 0.5f);		m_vecPos.push_back(v);
		// : top 
		v = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, 0.5f, 0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, 0.5f, 0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, 0.5f, 0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, 0.5f, -0.5f);		m_vecPos.push_back(v);
		// : bottom
		v = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);		m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, -0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, -0.5f, -0.5f);	m_vecPos.push_back(v);
		v = D3DXVECTOR3(0.5f, -0.5f, 0.5f);		m_vecPos.push_back(v);
	}

	for (int i = 0; i < m_vecPos.size(); i++)
	{
		m_vecPos[i] += m_vCenter;
	}
	/// Side Line
	//vector<D3DXVECTOR3> vecVertex;
	//vecVertex.push_back(m_vecPos[0]);
	//vecVertex.push_back(m_vecPos[1]);
	//vecVertex.push_back(m_vecPos[2]);
	//vecVertex.push_back(m_vecPos[5]);
	//vecVertex.push_back(m_vecPos[6]);
	//vecVertex.push_back(m_vecPos[8]);
	//vecVertex.push_back(m_vecPos[7]);
	//vecVertex.push_back(m_vecPos[10]);
	//vector<DWORD> vecIndex;
	////앞면
	//vecIndex.push_back(0);
	//vecIndex.push_back(1);
	//vecIndex.push_back(1);
	//vecIndex.push_back(2);
	//vecIndex.push_back(2);
	//vecIndex.push_back(3);
	//vecIndex.push_back(3);
	//vecIndex.push_back(0);
	////뒷면
	//vecIndex.push_back(4);
	//vecIndex.push_back(5);
	//vecIndex.push_back(5);
	//vecIndex.push_back(6);
	//vecIndex.push_back(6);
	//vecIndex.push_back(7);
	//vecIndex.push_back(7);
	//vecIndex.push_back(4);
	//////왼면
	//vecIndex.push_back(0);
	//vecIndex.push_back(1);
	//vecIndex.push_back(1);
	//vecIndex.push_back(5);
	//vecIndex.push_back(5);
	//vecIndex.push_back(4);
	//vecIndex.push_back(4);
	//vecIndex.push_back(0);
	//////오른면
	//vecIndex.push_back(3);
	//vecIndex.push_back(2);
	//vecIndex.push_back(2);
	//vecIndex.push_back(6);
	//vecIndex.push_back(6);
	//vecIndex.push_back(7);
	//vecIndex.push_back(7);
	//vecIndex.push_back(3);
	//m_vecSideLineVertex.resize(vecIndex.size());
	//for (unsigned int i = 0; i < vecIndex.size(); ++i)
	//{
	//	m_vecSideLineVertex[i].p = vecVertex[vecIndex[i]];
	//	m_vecSideLineVertex[i].c = BLACK;
	//}
}

void CCube::Update(CRay ray)
{
	for (int i = 0; i < m_vecPos.size(); i+=3)
	{
		if (ray.IntersectTri(m_vecPos[i + 0], m_vecPos[i + 1], m_vecPos[i + 2]) == true)
			m_isPicked = true;
		else
			m_isPicked = false;
	}
}

void CCube::Render()
{
	m_stMtlCube.Ambient = m_color;
	m_stMtlCube.Diffuse = m_color;
	m_stMtlCube.Specular = m_color;

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matWorld, m_vCenter.x, m_vCenter.y, m_vCenter.z);
	/// Side Line
	//g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecSideLineVertex.size() / 2,
	//	&m_vecSideLineVertex[0], sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMtlCube);
	g_pD3DDevice->SetTexture(0, 0);

	if (m_isPicked)
	{
		SetShader(matWorld);
		UINT numPasses = 0;
		m_pShader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				m_pShader->BeginPass(i); // 구체를 그린다

				if (i == 0)
					g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW); // 외곽선
				else
					g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// 내부

				m_pMeshCube->DrawSubset(0);

				m_pShader->EndPass();
			}
		}
		m_pShader->End();
	}

	else
	{
		m_pMeshCube->DrawSubset(0);
	}
}

string CCube::GetName()
{
	return m_strName;
}

void CCube::ReceiveEvent(ST_EVENT eventMsg)
{
	CObject::ReceiveEvent(eventMsg);
}