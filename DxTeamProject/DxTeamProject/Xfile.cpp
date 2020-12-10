#include "stdafx.h"
#include "Xfile.h"
#include "OBB.h"

CXfile::CXfile() :
	m_pMesh(NULL),
	m_adjBuffer(NULL),
	m_numMtrls(0),
	m_vScale(0.01,0.01,0.01),
	m_vRotate(0,0,0),
	m_vTranslate(0,0,0)
{
}

CXfile::~CXfile()
{
	SafeDelete(m_pOBB);

	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
	// SafeRelease(m_pTexture);
}

void CXfile::Setup()
{
	ST_XFile* xfile = new ST_XFile;

	/*if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Brush", "brush.X", xfile))
	{
		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
		return;
	}*/

	//if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Tile", "Tile_01.X", xfile))
	//{
	//	MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
	//	return;
	//}


	/*if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Tree", "autumn_tree_01.X", xfile))
	{
		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
		return;
	}*/

	if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Brush", "brush.X", xfile))
	{
		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
		return;
	}

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	delete xfile;

	//g_pFileLoadManager->FileLoad_Texture("Resource/XFile/Brush", "brush_red.png", m_pTexture);

	D3DXVECTOR3* pVertices;
	D3DXVECTOR3 m_vMin, m_vMax;

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	m_pMesh->UnlockVertexBuffer();

	/*m_pOBB = new COBB;
	m_pOBB->SetUpXFile(m_vMin * 0.01, m_vMax * 0.01);*/
}

void CXfile::Update()
{
	//m_pOBB->Update(&World);
}

void CXfile::Render(D3DXVECTOR3 eye)
{
	if (g_pD3DDevice)
	{
		/*if (m_pOBB)
			m_pOBB->OBBBOX_RENDER(D3DCOLOR_XRGB(255, 0, 0));*/
		
		D3DXMATRIXA16 matS, matR, matT;

		D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
		
		D3DXMatrixRotationX(&matR, m_vRotate.x);
		D3DXMatrixRotationY(&matR, m_vRotate.y);
		D3DXMatrixRotationZ(&matR, m_vRotate.z);

		D3DXMatrixTranslation(&matT, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);
		// D3DXMatrixTranslation(&matT, eye.x, eye.y, eye.z);

		D3DXMATRIXA16 matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		if (m_pMesh == NULL)
			return;

		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
			
			if(m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);

			//g_pD3DDevice->SetTexture(0, m_pTexture);
			// >> 텍스처 매치 안되있을 때

			m_pMesh->DrawSubset(i);
		}
		g_pD3DDevice->SetTexture(0, NULL);
		
	}
}
