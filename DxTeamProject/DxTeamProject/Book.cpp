#include "stdafx.h"
#include "Book.h"


CBook::CBook():
	m_pMesh(NULL),
	m_adjBuffer(NULL),
	m_numMtrls(0)
{
}


CBook::~CBook()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
}

void CBook::Update()
{
}

void CBook::Setup()
{
	ST_XFile* xfile = new ST_XFile;

	if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Book", "book.X", xfile))
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

void CBook::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIXA16 matS, matR ,matT;
	static float Rot = 0;
	Rot++;
	D3DXMatrixScaling(&matS, 0.3f, 0.3f, 0.3f);
	D3DXMatrixRotationY(&matR,Rot*0.01f);
	D3DXMatrixTranslation(&matT, 12, 0, 0);
	matWorld = matS* matR * matT;

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
