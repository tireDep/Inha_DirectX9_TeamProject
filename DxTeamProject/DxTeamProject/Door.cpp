#include "stdafx.h"
#include "Door.h"

CDoor::CDoor()
	: m_pMesh(NULL)
	, m_adjBuffer(NULL)
	, m_numMtrls(0)
{
}

CDoor::~CDoor()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
}

void CDoor::Setup(string folder, string file)
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

	//g_pFileLoadManager->FileLoad_Texture(folder, file, m_pTexture);
	for (int i = 0; i < m_vecTextures.size(); i++)
	{
		string filePath;
		filePath = string(folder) + "/cubeworld_texture.tga";
		if (m_vecTextures[i] == NULL)
			D3DXCreateTextureFromFileA(g_pD3DDevice, filePath.c_str(), &m_vecTextures[i]);
	}
	delete xfile;
}

void CDoor::Update()
{
}

void CDoor::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);

		D3DXMATRIXA16 matS, matT;
		D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
		D3DXMatrixTranslation(&matT, -25, 0, 0);
		matWorld = matS * matT;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		if (m_pMesh == NULL)
			return;
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			g_pD3DDevice->SetMaterial(m_vecMtrls[i]);
		}
		m_pMesh->DrawSubset(0);
		g_pD3DDevice->SetTexture(0, NULL);
	}
}