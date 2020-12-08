#include "stdafx.h"
#include "Dragon.h"


CDragon::CDragon() :
	m_pMesh(NULL),
	m_adjBuffer(NULL),
	m_numMtrls(0),
	m_isTrue(false),
	m_position(0,3,0)
{
}


CDragon::~CDragon()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
}

void CDragon::Update(D3DXCOLOR color)
{
	if(color == RED)
		g_pFileLoadManager->FileLoad_Texture("Resource/XFile/Crayon", "T_Dragon_01(red).png", m_pTexture);

	if (color == YELLOW)
		g_pFileLoadManager->FileLoad_Texture("Resource/XFile/Crayon", "T_Dragon_08(yellow).png", m_pTexture);

	if (color == GREEN)
		g_pFileLoadManager->FileLoad_Texture("Resource/XFile/Crayon", "T_Dragon_04(green).png", m_pTexture);

	if (color == BLUE)
		g_pFileLoadManager->FileLoad_Texture("Resource/XFile/Crayon", "T_Dragon_16(blue).png", m_pTexture);

	if (color == BLACK)
		g_pFileLoadManager->FileLoad_Texture("Resource/XFile/Crayon", "T_Dragon_05(black).png", m_pTexture);

	if (color == WHITE)
		g_pFileLoadManager->FileLoad_Texture("Resource/XFile/Crayon", "T_Dragon_17(white).png", m_pTexture);

}

void CDragon::Setup()
{
	//ST_XFile* xfile = new ST_XFile;

	if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Crayon", "crayon.X", xfile))
	{
		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
		return;
	}
	g_pFileLoadManager->FileLoad_Texture("Resource/XFile/Crayon", "T_Dragon_17(white).png", m_pTexture);

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	
	delete xfile;

}

void CDragon::Render()
{
	// >> testRotation
	if (m_isTrue == false)
	{
		m_position.y += 0.0005f;
		if (m_position.y >= 4)
			m_isTrue = true;

	}
	else if (m_isTrue == true)
	{
		m_position.y -= 0.0005f;
		if (m_position.y <= 3)
			m_isTrue = false;
	}
	// << testRotation

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIXA16 matS, matT;
	D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.7f);
	// D3DXMatrixTranslation(&matT, 0, 5, 0);
	D3DXMatrixTranslation(&matT, 1, m_position.y, 1);
	matWorld = matS * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	if (m_pMesh == NULL)
		return;

	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		if (m_vecTextures[i] != 0)
			g_pD3DDevice->SetTexture(0, m_pTexture);

		g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

		m_pMesh->DrawSubset(i);
	}
	g_pD3DDevice->SetTexture(0, NULL);
}
