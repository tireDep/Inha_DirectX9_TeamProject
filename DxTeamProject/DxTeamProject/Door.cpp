#include "stdafx.h"
#include "Door.h"

CDoor::CDoor()
	: m_pMesh(NULL)
	, m_adjBuffer(NULL)
	, m_numMtrls(0)
	, m_fOpeningAngle(D3DX_PI/2.0f)
	, IsOpen(true)
	, m_fRotAngle(0.0f)
	, m_fRotationSpeed(1.0f)
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
		if (m_vecTextures[i] == NULL)
			g_pFileLoadManager->FileLoad_Texture(folder, "cubeworld_texture.tga", m_vecTextures[i]);
	}
	//if (m_vecTextures.size() > 1)
	//{
	//	for (int i = 0; i < m_vecTextures.size(); i++)
	//	{
	//		if (m_vecTextures[i] == NULL)
	//			g_pFileLoadManager->FileLoad_Texture(folder, "cubeworld_texture.tga", m_vecTextures[i]);
	//	}
	//}
	//else
	//{
	//	for (int i = 0; i < m_vecTextures.size(); i++)
	//	{
	//		if (m_vecTextures[i] == NULL)
	//			g_pFileLoadManager->FileLoad_Texture(folder, "cubeworld_metal.tga", m_vecTextures[i]);
	//	}
	//}
	delete xfile;

	/// Later IObject inheritance...
	//m_pOBB = new CPSOBB;
	//m_pOBB->Setup(*this);
	//g_pObjectManager->AddOBBbox(m_pOBB);
}

void CDoor::Update(float duration)
{
	// tmp Test
	static int tmpCount = 0;
	tmpCount++;
	if (tmpCount >= 10000)
	{
		IsOpen = false;
		if (tmpCount >= 20000)
		{
			IsOpen = true;
			tmpCount = 0;
		}
	}

	// tmp
	//if (g_gameManager->getOrb())
	//	IsOpen = true;
	//if (g_gameManager->getBook())
	//	IsOpen = true;
	
	if (IsOpen)
	{
		m_fRotAngle += m_fRotationSpeed * duration;
		if (m_fRotAngle >= m_fOpeningAngle)
			m_fRotationSpeed = 0;
		else
			m_fRotationSpeed = 1.0f;
	}
	else
	{
		m_fRotAngle -= m_fRotationSpeed * duration;
		if (m_fRotAngle <= 0)
			m_fRotationSpeed = 0;
		else
			m_fRotationSpeed = 1.0f;
	}
	D3DXMatrixRotationY(&m_matRotGimmick, m_fRotAngle);
}

void CDoor::Update(float duration, bool isSwitchOn)
{
	if (isSwitchOn)
	{
		IsOpen = true;
		Update(duration);
	}
	else
	{
		IsOpen = false;
		Update(duration);
	}

	/// Later IObject inheritance...
	//m_matWorld = m_matS * m_matRotGimmick * m_matT;
	//m_pOBB->Update(&m_matWorld);
}

void CDoor::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		//D3DXMATRIXA16 matWorld;
		//D3DXMatrixIdentity(&matWorld);
		//D3DXMATRIXA16 matS, matT;
		//D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
		//D3DXMatrixTranslation(&matT, -25, 0, 0);
		//matWorld = matS * m_matRotGimmick * matT;
		//matWorld = matS * matT;
		//matWorld = m_matRotGimmick * matT;
		//if (m_vecTextures.size() == 1)
		//{
		//	D3DXMATRIXA16 matWorld, matT;
		//	D3DXMatrixIdentity(&matWorld);
		//	D3DXMatrixTranslation(&matT, -25, 0, 0);
		//	matWorld = matT;
		//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		//}
		//else
		//{
		D3DXMATRIXA16 matWorld, matT;
		D3DXMatrixIdentity(&matWorld);
		//D3DXMatrixTranslation(&matT, -25, 0, 0);
		//matWorld = m_matRotGimmick * matT;
		matWorld = m_matRotGimmick;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		//}
		if (m_pMesh == NULL)
			return;
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
			m_pMesh->DrawSubset(i);
		}
		//m_pMesh->DrawSubset(0);
		g_pD3DDevice->SetTexture(0, NULL);
	}
}