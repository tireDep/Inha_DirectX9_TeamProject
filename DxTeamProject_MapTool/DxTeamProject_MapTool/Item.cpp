#include "stdafx.h"
#include "Item.h"

CItem::CItem() :
	m_UvX(0),
	m_UvY(0.2f)
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
	}
	else
	{
		// >> orb, trace
		// >> world matrix 계산되므로 기본크기인 1, 1, 1로 박스 생성 후
		//    OBB 박스 생성
		D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMesh, NULL);

		m_pMtrl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_pMtrl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_pMtrl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	IObject::Setup_OBB_Box();

	if (m_strTxtFile != "")
		g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

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
		SetShaderColor(D3DXVECTOR4(0, 0, 0, 1), D3DXVECTOR4(0, 0.5, 0.5, 1));
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


int CItem::GetSpriteIndex()
{
	// >> Orb, Trace
	if (strstr(m_strTxtFile.c_str(), "Black"))			return 0;
	else if (strstr(m_strTxtFile.c_str(), "White"))		return 1;
	else if (strstr(m_strTxtFile.c_str(), "Yellow"))	return 2;
	else if (strstr(m_strTxtFile.c_str(), "Green"))		return 3;
	else if (strstr(m_strTxtFile.c_str(), "Red"))		return 4;
	else if (strstr(m_strTxtFile.c_str(), "Blue"))		return 5;
}

void CItem::SetSpriteIndex(int index)
{
	string temp;

	// >> Orb
	if(m_ObjectType == ObjectType::eOrb)
	{
		if (index == 0)			m_strTxtFile = "Orb_Black.png";
		else if (index == 1)	m_strTxtFile = "Orb_White.png";
		else if (index == 2)	m_strTxtFile = "Orb_Yellow.png";
		else if (index == 3)	m_strTxtFile = "Orb_Green.png";
		else if (index == 4)	m_strTxtFile = "Orb_Red.png";
		else if (index == 5)	m_strTxtFile = "Orb_Blue.png";

		int search = 0;
		for (int i = 0; i < m_strObjName.length(); i++)
		{
			if (m_strObjName[i] >= 48 && m_strObjName[i] <= 57)
			{
				search = i;
				break;
			}
		}
		// << refCnt 추출

		temp = m_strTxtFile;
		temp = temp.substr(0, temp.length() - 4); // 이름 언더바 위치(refNum 위치)
		m_strObjName = temp + m_strObjName.substr(search, m_strObjName.length());
	}

	// >> Trace
	if (m_ObjectType == ObjectType::eTrace)
	{
		switch (index)
		{
		case 0:
			m_strTxtFile = "WaterColor_Black.png";		
			temp = "Black";
			break;

		case 1:
			m_strTxtFile = "WaterColor_White.png";		
			temp = "White";
			break;

		case 2:
			m_strTxtFile = "WaterColor_Yellow.png";		
			temp = "Yellow";
			break;

		case 3:
			m_strTxtFile = "WaterColor_Green.png";		
			temp = "Green";
			break;

		case 4:
			m_strTxtFile = "WaterColor_Red.png";		
			temp = "Red";
			break;

		case 5:
			m_strTxtFile = "WaterColor_Blue.png";		
			temp = "Blue";
			break;
		}
		
		int search = 0;
		for (int i = 0; i < m_strObjName.length(); i++)
		{
			if (m_strObjName[i] >= 48 && m_strObjName[i] <= 57)
			{
				search = i;
				break;
			}
		}
		// << refCnt 추출

		m_strObjName = "Trace_" + temp + m_strObjName.substr(search, m_strObjName.length());
	}

	g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);
}

