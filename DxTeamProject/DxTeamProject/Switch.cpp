#include "stdafx.h"
#include "Switch.h"
#include "OBB.h"

CSwitch::CSwitch()
	: m_scale(1,1,1)
	, m_position(10,0.5f,0)
	, istrue(false)
	, m_pColl(NULL)
	, m_pBox(NULL)
{
	D3DXMatrixIdentity(&matWorld);
}

CSwitch::~CSwitch()
{
	SafeRelease(m_pBox);
	SafeDelete(m_pColl);
}

void CSwitch::Setup()
{
	{

		D3DXCreateBox(g_pD3DDevice, 2.5, 0.3f, 2.5, &m_pBox, NULL);

		D3DXVECTOR3* pVertices;

		m_pBox->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
		D3DXComputeBoundingBox(pVertices, m_pBox->GetNumVertices(), m_pBox->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
		m_pBox->UnlockVertexBuffer();

		m_pColl = new COBB;
		m_pColl->SetupMesh(m_vMin, m_vMax, 0.3f);
		

	}
	ST_XFile* xfile = new ST_XFile;

	if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Gimmick/Switch", "Force_switch.X", xfile))
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
			filePath = string(folder) + "/cubeworld_texture.tga";
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

void CSwitch::Setup(ST_MapData setData)
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
	{
		g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);
		// m_vecTextures.push_back(m_pTexture);
	}

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	delete xfile;

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&m_matS, vScale.x, vScale.y, vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(vRotate.x);
	v.y = D3DXToRadian(vRotate.y);
	v.z = D3DXToRadian(vRotate.z);
	D3DXMatrixRotationYawPitchRoll(&m_matR, v.x, v.y, v.z);

	D3DXMatrixTranslation(&m_matT, vTranslate.x, vTranslate.y, vTranslate.z);

	m_matWorld = m_matS * m_matR * m_matT;

	 m_pOBB = new COBB;
	 m_pOBB->Setup(*this);
	 g_pObjectManager->AddOBBbox(m_pOBB);
	 g_pObjectManager->AddGimmick(this);

	//// OBB TEST
	/*m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);*/
}


void CSwitch::Update()
{
	 D3DXMatrixScaling(&matS, m_scale.x, m_scale.y, m_scale.z);
	 D3DXMatrixTranslation(&matT, m_position.x, m_position.y, m_position.z);
	 collWorld = matS *matT;
	 
	 m_pColl->Update(&collWorld);
	 m_pOBB->Update(&m_matWorld);
}

void CSwitch::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	{
		// g_pD3DDevice->SetTransform(D3DTS_WORLD, &collWorld);
		// m_pColl->Render();
	}

	{
	/*	D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matS, 0.3f, 0.3f, 0.3f);
		D3DXMatrixTranslation(&matT, 10, 0, 0);
		matWorld = matS * matT;*/

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetmatWorld());
		// m_pOBB->Render();

		if (m_pMesh == NULL)
			return;

		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			else
				g_pD3DDevice->SetTexture(0, m_pTexture);

			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

			if (istrue == false)
				m_pMesh->DrawSubset(i);
			else
				m_pMesh->DrawSubset(0);
		}

		g_pD3DDevice->SetTexture(0, NULL);
	}
	
}
