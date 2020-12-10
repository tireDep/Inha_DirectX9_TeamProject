#include "stdafx.h"
#include "Switch.h"
#include "OBB.h"

CSwitch::CSwitch()
	:m_pMesh(NULL)
	,m_adjBuffer(NULL)
	,m_numMtrls(0)
	, m_pOBB(NULL)
	, m_scale(1,1,1)
	, m_position(10,0.5f,0)
	, istrue(false)
{
	D3DXMatrixIdentity(&collWorld);
}


CSwitch::~CSwitch()
{
	SafeDelete(m_pOBB);
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
}

void CSwitch::Setup(string folder, string file)
{
	{

		D3DXCreateBox(g_pD3DDevice, 2.5, 0.3f, 2.5, &m_pBox, NULL);

		D3DXVECTOR3* pVertices;

		m_pBox->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
		D3DXComputeBoundingBox(pVertices, m_pBox->GetNumVertices(), m_pBox->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
		m_pBox->UnlockVertexBuffer();

		/*m_pOBB = new COBB;
		m_pOBB->Setup(this);*/

	}
	ST_XFile* xfile = new ST_XFile;

	if (!g_pFileLoadManager->FileLoad_XFile(folder, file, xfile))
	{
		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
		return;
	}

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	if (m_vecTextures.size() > 1)
	{
		for (int i = 0; i < m_vecTextures.size(); i++)
		{
			string filePath;
			filePath = string(folder) + "/cubeworld_texture.tga";
			if (m_vecTextures[i] == NULL)
				D3DXCreateTextureFromFileA(g_pD3DDevice, filePath.c_str(), &m_vecTextures[i]);
		}
	}
	delete xfile;
}

void CSwitch::Update()
{
	
	D3DXMatrixScaling(&matS, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixTranslation(&matT, m_position.x, m_position.y, m_position.z);
	collWorld = matS *matT;

	//m_pOBB->Update(&collWorld);
	
}

void CSwitch::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &collWorld);
		//m_pOBB->OBBBOX_RENDER(D3DCOLOR_XRGB(255, 255, 0));
	}

	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matS, 0.3f, 0.3f, 0.3f);
		D3DXMatrixTranslation(&matT, 10, 0, 0);
		matWorld = matS * matT;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		if (m_pMesh == NULL)
			return;
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
			if (istrue == false)
				m_pMesh->DrawSubset(i);
			else
				m_pMesh->DrawSubset(0);
		}
		g_pD3DDevice->SetTexture(0, NULL);
	}
	
}
