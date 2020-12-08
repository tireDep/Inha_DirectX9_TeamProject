#include "stdafx.h"
#include "Switch.h"


CSwitch::CSwitch()
	:m_pMesh(NULL)
	,m_adjBuffer(NULL)
	,m_numMtrls(0)
{
}


CSwitch::~CSwitch()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
}

void CSwitch::Setup(string folder, string file)
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
}

void CSwitch::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIXA16 matS, matT;
	D3DXMatrixScaling(&matS, 0.3f, 0.3f, 0.3f);
	D3DXMatrixTranslation(&matT, 5, 0, 0);
	matWorld = matS * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	if (m_pMesh == NULL)
		return;
	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		if (m_vecTextures[i] != 0)
			g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
		g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
		m_pMesh->DrawSubset(i);
	}
	g_pD3DDevice->SetTexture(0, NULL);
}
