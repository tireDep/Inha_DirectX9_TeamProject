#include "stdafx.h"
#include "Background.h"

bool CBackground::CheckIsGetColorOrb()
{
	// >> 태그와 맞는 색상 오브가 있는지 판별
	// >> 하나라도 존재 하지 않을 경우 false

	for (int i = 0; i < m_vecColorTag.size(); i++)
	{
		if (!g_pGameManager->GetIsHasOrb(m_vecColorTag[i]))
			return false;
	}

	return true;
}

CBackground::CBackground()
{
	render = false;
	m_strName = string("Background") + to_string(m_nRefCount);
}

CBackground::~CBackground()
{
}

//void CBackground::Update(CRay ray, D3DXCOLOR & playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
//{
//	// >> 터짐 방지
//	vecVPos.push_back(D3DXVECTOR3(0, 0, 0));
////	vecIsPick.push_back(m_isPicked);
//}

void CBackground::Setup(const ST_MapData & mapData)
{
	m_strObjName = mapData.strObjName;
	m_strFolder = mapData.strFolderPath;
	m_strXFile = mapData.strXFilePath;
	m_strTxtFile = mapData.strTxtPath;
	m_ObjectType = mapData.objType;

	m_vScale = mapData.vScale;
	m_vRotation = mapData.vRotate;
	m_vTranslation = mapData.vTranslate;
	
	m_vecColorTag = mapData.vecColorTag;

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
		m_vTranslation.y = 0.5f;
		//vTranslate.y = 0.5f;
		D3DXCreateBox(g_pD3DDevice, m_vScale.x, m_vScale.y, m_vScale.z, &m_pMesh, NULL);

		m_stMtl.Ambient = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
		m_stMtl.Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
		m_stMtl.Specular = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);

		m_vecMtrls.push_back(m_stMtl);
	}

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = matS * matR * matT;

	// OBB Test
	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);

	//D3DXVECTOR3 vScale, vRotate, vTranslate;
	//vScale = setData.vScale;
	//// JW ADD...
	//m_vScale = vScale;
	//vRotate = setData.vRotate;
	//vTranslate = setData.vTranslate;
	// ====================================================
	//D3DXMATRIXA16 matS, matR, matT;
	//D3DXMatrixScaling(&matS, vScale.x,vScale.y, vScale.z);
	//D3DXVECTOR3 v;
	//v.x = D3DXToRadian(vRotate.x);
	//v.y = D3DXToRadian(vRotate.y);
	//v.z = D3DXToRadian(vRotate.z);
	//D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);
	//D3DXMatrixTranslation(&matT, vTranslate.x, vTranslate.y, vTranslate.z);
	//m_matWorld = matS * matR * matT;
}

void CBackground::Render()
{
	if (m_ObjectType == ObjectType::eInvisibleWall)
		return; // >> 투명벽 랜더하지 않음

	// if (m_ObjectType == ObjectType::eFlower) // || m_ObjectType == ObjectType::eInvisibleWall)
	// {
	// 	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	// 	// todo : setTexture
	// }
	// else
	// 	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (m_pMesh == NULL)
		return;

	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

		if (m_ObjectType != ObjectType::eFlower) // && m_ObjectType != ObjectType::eInvisibleWall)
		{
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

			if (!CheckIsGetColorOrb())
				g_pD3DDevice->SetTexture(0, g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "BasicGray_127.png"));
			else
			{
				if (m_vecTextures[i] != 0)
					g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
				else if (m_pTexture != NULL)
					g_pD3DDevice->SetTexture(0, m_pTexture);
			}
		}
		else
		{
			// >> 투명벽, 꽃은 텍스쳐 없고 매터리얼 값으로만 이루어져 있음
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

			if (!CheckIsGetColorOrb())
				g_pD3DDevice->SetTexture(0,
					g_pFileLoadManager->GetFileNameTexture("Resource/Texture","BasicGray_127.png"));
		}

		m_pMesh->DrawSubset(i);
	}
	g_pD3DDevice->SetTexture(0, NULL);
}