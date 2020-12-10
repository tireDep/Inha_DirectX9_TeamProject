#include "stdafx.h"
#include "MovingCube.h"
#include "OBB.h"

MovingCube::MovingCube() :m_pMesh(NULL)
, m_adjBuffer(NULL)
, m_numMtrls(0)
, IndexNum(1)
, m_position(0, 0, 0)
, istrue(false)
, speed(0.005)
, startpos(0)
, endpos(8)
, m_pOBB(NULL)
{
}


MovingCube::~MovingCube()
{
	SafeDelete(m_pOBB);
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
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

	m_pOBB = new COBB;
	m_pOBB->SetUpXFile(m_vMin, m_vMax);

	delete xfile;

}

void MovingCube::Update()
{
	if (IndexNum == 0 && istrue == false)
	{
		m_position.y += speed;
		if (m_position.y > endpos)
			istrue = true;
	}
	else if (IndexNum == 0 && istrue == true)
	{
		m_position.y -= speed;
		if (m_position.y < startpos)
			istrue = false;
	}

	if (IndexNum == 1 && istrue == false)
	{
		m_position.x += speed;
		if (m_position.x > endpos)
			istrue = true;
	}
	else if (IndexNum == 1 && istrue == true)
	{
		m_position.x -= speed;
		if (m_position.x < startpos)
			istrue = false;
	}


	if (IndexNum == 2 && istrue == false)
	{
		m_position.z += speed;
		if (m_position.z > endpos)
			istrue = true;
	}
	else if (IndexNum == 2 && istrue == true)
	{
		m_position.z -= speed;
		if (m_position.z < startpos)
			istrue = false;
	}

	m_pOBB->Update(&matWorld);
}

void MovingCube::Render()
{
	D3DXMatrixRotationY(&matR, 0);
	D3DXMatrixScaling(&matS, 0.3, 0.3, 0.3);
	D3DXMatrixTranslation(&matT, m_position.x, m_position.y, m_position.z);
	matWorld = matS * matR * matT;

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
	m_pOBB->OBBBOX_RENDER(D3DCOLOR_XRGB(255, 255, 0));
	g_pD3DDevice->SetTexture(0, NULL);

}
