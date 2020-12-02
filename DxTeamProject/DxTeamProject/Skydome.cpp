#include "stdafx.h"
#include "Skydome.h"

CSkydome::CSkydome() :
	m_pMesh(NULL),
	m_adjBuffer(NULL),
	m_numMtrls(0)
{
}

CSkydome::~CSkydome()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
}

void CSkydome::Setup(string folder, string file)
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

	delete xfile;
}

void CSkydome::Render(D3DXVECTOR3 vCamEye)
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false); // zbuffer off
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		D3DXMATRIXA16 matS, matT;
		D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
		D3DXMatrixTranslation(&matT, vCamEye.x, vCamEye.y, vCamEye.z);
		
		D3DXMATRIXA16 matWorld = matS * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		if (m_pMesh == NULL)
			return;

		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
		
			g_pD3DDevice->SetMaterial(m_vecMtrls[i]);

			if (i == 0 || i == 2)
				m_pMesh->DrawSubset(i);
			// 0 : Skydome / 1 : Star / 2 : Sun / 3 : Moon
			// todo : uvÁÂÇ¥ ÁöÁ¤?
		}
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true); // zbuffer on
	}
}
