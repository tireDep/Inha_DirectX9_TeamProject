#include "stdafx.h"
#include "Item.h"

CItem::CItem()
{
}

CItem::~CItem()
{
}

void CItem::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;

	m_vScale = setData.vScale;
	m_vRotation = setData.vRotate;
	m_vTranslation = setData.vTranslate;

	m_strConditionName = setData.gimmickData.conditionName;

	if (m_strXFile != "")
	{
		ST_XFile* xfile = new ST_XFile;

		g_pFileLoadManager->FileLoad_XFile(m_strFolder, m_strXFile, xfile);

		m_pMesh = xfile->pMesh;
		m_adjBuffer = xfile->adjBuffer;
		m_vecMtrls = xfile->vecMtrl;
		m_vecTextures = xfile->vecTextrure;
		m_numMtrls = xfile->nMtrlNum;

		delete xfile;

		m_pMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)m_adjBuffer->GetBufferPointer(),
			(DWORD*)m_adjBuffer->GetBufferPointer(),
			0, 0);
	}
	else
	{
		// >> orb, trace
		// >> world matrix 계산되므로 기본크기인 1, 1, 1로 박스 생성 후
		//    OBB 박스 생성
		D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMesh, NULL);

		m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_stMtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	if (m_strTxtFile != "")
		g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(m_vRotation.x);
	v.y = D3DXToRadian(m_vRotation.y);
	v.z = D3DXToRadian(m_vRotation.z);

	D3DXMatrixRotationYawPitchRoll(&m_matR, v.y, v.x, v.z);

	D3DXMatrixTranslation(&m_matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = m_matS * m_matR * m_matT;

	if (m_ObjectType != eTrace)
	{
		// OBB TEST
		m_pOBB = new COBB;
		m_pOBB->Setup(*this);
		g_pObjectManager->AddOBBbox(m_pOBB);
		m_pOBB->Update(&m_matWorld);
	}
	else
	{
		// >> 흔적은 obb 필요하지 않음
		m_pOBB = new COBB;
		m_pOBB->Setup(*this);
		g_pObjectManager->AddOBBbox(NULL);
	}

}

