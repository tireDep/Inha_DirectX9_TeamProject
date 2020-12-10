#include "stdafx.h"
#include "Background.h"
// OBB Test
#include "PSOBB.h"

CBackground::CBackground()
	// OBB Test
	//: m_pOBB(NULL)
{
	//m_isPicked = false;
	//m_isClicked = false;

	m_strName = string("Background") + to_string(m_nRefCount);
}

CBackground::~CBackground()
{
	// OBB Test
	//SafeDelete(m_pOBB);
}

//void CBackground::Update(CRay ray, D3DXCOLOR & playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
//{
//	// >> 터짐 방지
//	vecVPos.push_back(D3DXVECTOR3(0, 0, 0));
////	vecIsPick.push_back(m_isPicked);
//}

void CBackground::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;

	D3DXVECTOR3 vScale, vRotate, vTranslate;
	vScale = setData.vScale;
	// JW ADD...
	m_vScale = vScale;
	vRotate = setData.vRotate;
	vTranslate = setData.vTranslate;

	if (m_strXFile != "")
	{
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
	}
	else
	{
		vTranslate.y = 0.5f;
		D3DXCreateBox(g_pD3DDevice, m_vScale.x, m_vScale.y, m_vScale.z, &m_pMesh, NULL);

		m_stMtl.Ambient = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
		m_stMtl.Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
		m_stMtl.Specular = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);

		m_vecMtrls.push_back(m_stMtl);
	}

	// ====================================================

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, vScale.x,vScale.y, vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(vRotate.x);
	v.y = D3DXToRadian(vRotate.y);
	v.z = D3DXToRadian(vRotate.z);

	D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);

	D3DXMatrixTranslation(&matT, vTranslate.x, vTranslate.y, vTranslate.z);
	m_matWorld = matS * matR * matT;

	// OBB Test
	m_pOBB = new CPSOBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
}

void CBackground::Render()
{
	// >> 투명벽, 꽃은 텍스쳐 없고 매터리얼 값으로만 이루어져 있음

	if (m_ObjectType == ObjectType::eInvisibleWall)
		return; // >> 투명벽 랜더하지 않음

	if(m_ObjectType == ObjectType::eFlower || m_ObjectType == ObjectType::eInvisibleWall)
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	else
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	// if(m_pMtrl!=NULL)
	// 	g_pD3DDevice->SetMaterial(&m_pMtrl);

	if (m_pMesh == NULL)
		return;

	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

		if (m_ObjectType != ObjectType::eFlower && m_ObjectType != ObjectType::eInvisibleWall)
		{
			// >> 
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			else if (m_pTexture != NULL)
			{
				g_pD3DDevice->SetTexture(0, m_pTexture);
				// >> 텍스처 매치 안되있을 때
			}
		}

		m_pMesh->DrawSubset(i);
	}

	g_pD3DDevice->SetTexture(0, NULL);
}