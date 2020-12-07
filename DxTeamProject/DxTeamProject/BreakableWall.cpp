#include "stdafx.h"
#include "BreakableWall.h"

CBreakableWall::CBreakableWall()
	: m_pMesh(NULL)
	, m_adjBuffer(NULL)
	, m_numMtrls(0)
{
}

CBreakableWall::~CBreakableWall()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
}

void CBreakableWall::Setup(string folder, string file)
{
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

	//for (int i = 0; i < m_vecTextures.size(); i++)
	//{
	//	if (m_vecTextures[i] == NULL)
	//		g_pFileLoadManager->FileLoad_Texture(folder, "cubeworld_texture.tga", m_vecTextures[i]);
	//}

	delete xfile;
}

void CBreakableWall::Update()
{
}

void CBreakableWall::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		// Test
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matWorld, -25, 0, -2);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		if (m_pMesh == NULL)
			return;
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
		}
		m_pMesh->DrawSubset(0);
		g_pD3DDevice->SetTexture(0, NULL);
	}
}
