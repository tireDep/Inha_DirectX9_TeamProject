#include "stdafx.h"
#include "Dragon.h"
#include "Character.h"


CDragon::CDragon() :
	m_pMesh(NULL),
	m_adjBuffer(NULL),
	m_numMtrls(0),
	m_isTrue(false),
	m_vPosition(0, 0, 0),
	Drangon_y(4.5f),
	m_vDrangonPos(0, 0, 0),
	m_vDirection(0,0,1)
{
	D3DXMatrixIdentity(&m_matRotY);
}


CDragon::~CDragon()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
}

void CDragon::Update(D3DXVECTOR3 pos)
{
	m_vPosition = pos;

	//m_DrangonPos.y = m_position.y + Drangon_y;

	// >> testRotation
	if (m_isTrue == false)
	{
		m_vDrangonPos.y += 0.0005f;
		if (m_vDrangonPos.y >= 1.0f)
			m_isTrue = true;

	}
	else if (m_isTrue == true)
	{
		m_vDrangonPos.y -= 0.0005f;
		if (m_vDrangonPos.y <= 0.0f)
			m_isTrue = false;
	}
	m_vPosition.y += Drangon_y+ m_vDrangonPos.y;
}

void CDragon::Setup()
{

	if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Crayon", "crayon.X", xfile))
	{
		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
		return;
	}
	g_pFileLoadManager->FileLoad_Texture("Resource/XFile/Crayon", "default_T_Dragon_30(new).png", m_pTexture);

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;


	
	delete xfile;

}

void CDragon::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIXA16 matS, matT;
	D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.7f);
	// D3DXMatrixTranslation(&matT, 0, 5, 0);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	matWorld = matS *m_matRotY* matT;

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

void CDragon::ChangeColor(D3DXCOLOR color)
{
	if (color == RED)
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

void CDragon::DoRotation(const float & radian, D3DXVECTOR3 cameradirection)
{
	m_vDirection = cameradirection;
	m_vDirection.y = 0;
	D3DXMatrixRotationY(&m_matRotY, radian);

	cout << radian << endl;

	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &m_matRotY);
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);

	D3DXVECTOR3 tempPos(0, 0, 0);
	D3DXVECTOR3 tempUp(0, 1, 0);
	D3DXMatrixLookAtLH(&m_matRotY, &tempPos, &m_vDirection, &tempUp);
	D3DXMatrixTranspose(&m_matRotY, &m_matRotY);
}

void CDragon::DirectionSet(D3DXVECTOR3 cameradirection)
{
	m_vDirection = cameradirection;
}
