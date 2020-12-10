#include "stdafx.h"
#include "Switch.h"

CSwitch::CSwitch()
{
}

CSwitch::~CSwitch()
{
}

void CSwitch::Setup(ST_MapData setData)
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
}

void CSwitch::Render()
{
	IObject::Render_OBB_Box();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetmatWorld());

	if (m_pMesh == NULL)
		return;

	if (!m_isPick && !m_isClick || !m_pShader)
	{
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
		SetShader(GetmatWorld());
		IObject::Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
}

void CSwitch::SetTexture(int index)
{
	switch (index)
	{
	case 0:
		m_strTxtFile = "cubeworld_glow.tga";
		break;

	case 1:
		m_strTxtFile = "cubeworld_metal.tga";
		break;

	case 2:
		m_strTxtFile = "cubeworld_rough.tga";
		break;

	case 3:
		m_strTxtFile = "cubeworld_texture.tga";
		break;
	}

	g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);
	// m_vecTextures.clear(); // 텍스쳐가 없어서 지우면 터짐(0 삭제됨)
	m_vecTextures.push_back(m_pTexture);
}


int CSwitch::GetTextureIndex()
{
	if (m_strTxtFile == "cubeworld_glow.tga")
		return 0;
	if (m_strTxtFile == "cubeworld_metal.tga")
		return 1;
	if (m_strTxtFile == "cubeworld_rough.tga")
		return 2;
	if (m_strTxtFile == "cubeworld_texture.tga")
		return 3;
}

void CSwitch::SetConditionType()
{
}

void CSwitch::SetCondition()
{
}
