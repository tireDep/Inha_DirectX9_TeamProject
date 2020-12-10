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

void MovingCube::Setup()
{
	ST_XFile* xfile = new ST_XFile;

	if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Gimmick/MovingCube", "moving_cube.X", xfile))
	{
		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
		return;
	}

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	/*if (m_vecTextures.size() > 1)
	{
		for (int i = 0; i < m_vecTextures.size(); i++)
		{
			string filePath;
			filePath = string(folder) + "/moving_cube_1.png";
			if (m_vecTextures[i] == NULL)
				D3DXCreateTextureFromFileA(g_pD3DDevice, filePath.c_str(), &m_vecTextures[i]);
		}
	}*/


	delete xfile;

	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	g_pObjectManager->AddGimmick(this);

}

void MovingCube::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;

	D3DXVECTOR3 vScale, vRotate, vTranslate;

	vScale = setData.vScale; // 0.01, 0.03, 0.01, 0.01
							 // JW ADD...
	m_vScale = vScale;
	vRotate = setData.vRotate;
	vTranslate = setData.vTranslate;

	ST_XFile* xfile = new ST_XFile;

	g_pFileLoadManager->FileLoad_XFile(m_strFolder, m_strXFile, xfile);

	if (m_strTxtFile != "")
		g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	delete xfile;

	//D3DXMATRIXA16 matS, matR, matT;
	//D3DXMatrixScaling(&m_matS, vScale.x, vScale.y, vScale.z);

	//D3DXVECTOR3 v;
	//v.x = D3DXToRadian(vRotate.x);
	//v.y = D3DXToRadian(vRotate.y);
	//v.z = D3DXToRadian(vRotate.z);

	//D3DXMatrixRotationYawPitchRoll(&m_matR, v.x, v.y, v.z);

	//D3DXMatrixTranslation(&m_matT, vTranslate.x, vTranslate.y, vTranslate.z);
	//m_matWorld = matS * matR * matT;

	//// OBB TEST
	/*m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);*/
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
