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
	m_vRotate = setData.vRotate;
	m_vTranslate = setData.vTranslate;

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

	IObject::Setup_OBB_Box();

	// ====================

	m_strConditionName = setData.gimmickData.conditionName;
}

void CItem::Render()
{
	IObject::Render_OBB_Box();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetmatWorld());

	if (m_pMesh == NULL)
		return;

	if (g_pObjectManager->GetPickObjName() == m_strConditionName && m_strConditionName != "" && m_pShader)
	{
		// >> 조건 오브젝트가 선택되었을 경우
		SetShader(GetmatWorld());
		SetShader_ConditionColor();
		IObject::Render();
	}
	else if (!m_isPick && !m_isClick || !m_pShader)
	{
		// >> 오브젝트가 선택되지 않거나 셰이더가 없을 경우
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			else if (m_pTexture != NULL)
				g_pD3DDevice->SetTexture(0, m_pTexture);
			// >> 텍스처 매치 안되있을 때

			m_pMesh->DrawSubset(i);
		}
	}
	else
	{
		// >> 오브젝트가 선택되었을 경우
		SetShader(GetmatWorld());
		IObject::Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
}
