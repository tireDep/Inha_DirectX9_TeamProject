#include "stdafx.h"
#include "Skydome.h"

void CSkydome::Render_Sky(const D3DXMATRIXA16 & matWorld)
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		if (m_vecTextures[i] != 0)
			g_pD3DDevice->SetTexture(0, m_vecTextures[i]);

		g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

		// if (i == 0 || i == 2)
		if (i == 0)
			m_pMesh->DrawSubset(i);
		// 0 : Skydome / 1 : Star / 2 : Sun / 3 : Moon
	}
}

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
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false); // zbuffer off
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		if (m_pMesh == NULL)
			return;
		D3DXMATRIXA16 matS, matR, matT, matWorld;
		D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
		D3DXMatrixRotationZ(&matR, D3DX_PI);
		D3DXMatrixTranslation(&matT, vCamEye.x, vCamEye.y, vCamEye.z);

		matWorld = matS * matT;
		Render_Sky(matWorld);	// >> 위 반구

		matWorld = matS * matR * matT;
		Render_Sky(matWorld);	// >> 아래 반구

		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true); // zbuffer on
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
}