#include "stdafx.h"
#include "MovingCube.h"
#include "OBB.h"

MovingCube::MovingCube()
: IndexNum(1)
, m_vPosition(0, 0, 0)
, istrue(false)
, speed(0.005)
, startpos(0)
, endpos(8)
{
}


MovingCube::~MovingCube()
{
	
}

void MovingCube::Setup(string folder, string file)
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
			filePath = string(folder) + "/moving_cube_1.png";
			if (m_vecTextures[i] == NULL)
				D3DXCreateTextureFromFileA(g_pD3DDevice, filePath.c_str(), &m_vecTextures[i]);
		}
	}

	D3DXVECTOR3* pVertices;

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	m_pMesh->UnlockVertexBuffer();

	delete xfile;

	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	g_pObjectManager->AddGimmick(this);

}

void MovingCube::Update()
{
	if (IndexNum == 0 && istrue == false)
	{
		m_vPosition.y += speed;
		if (m_vPosition.y > endpos)
			istrue = true;
	}
	else if (IndexNum == 0 && istrue == true)
	{
		m_vPosition.y -= speed;
		if (m_vPosition.y < startpos)
			istrue = false;
	}

	if (IndexNum == 1 && istrue == false)
	{
		m_vPosition.x += speed;
		if (m_vPosition.x > endpos)
			istrue = true;
	}
	else if (IndexNum == 1 && istrue == true)
	{
		m_vPosition.x -= speed;
		if (m_vPosition.x < startpos)
			istrue = false;
	}


	if (IndexNum == 2 && istrue == false)
	{
		m_vPosition.z += speed;
		if (m_vPosition.z > endpos)
			istrue = true;
	}
	else if (IndexNum == 2 && istrue == true)
	{
		m_vPosition.z -= speed;
		if (m_vPosition.z < startpos)
			istrue = false;
	}

	D3DXMatrixRotationY(&matR, 0);
	D3DXMatrixScaling(&matS, 0.3, 0.3, 0.3);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matR * matT;

	m_pOBB->Update(&m_matWorld);
}

void MovingCube::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	m_pOBB->Render();

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
