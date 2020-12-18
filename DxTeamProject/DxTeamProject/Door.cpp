#include "stdafx.h"
#include "Door.h"

CDoor::CDoor()
	: m_fOpeningAngle(D3DX_PI / 2.0f)
	, IsOpen(false)
	, m_fRotAngle(0.0f)
	, m_fRotationSpeed(1.0f)
	,render(true)
{
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
	D3DXMatrixIdentity(&m_matRotGimmick);
	m_strName = string("Door") + to_string(m_nRefCount);
}

CDoor::~CDoor()
{
}

void CDoor::Setup(const ST_MapData & mapData)
{
	CGimmick::SetLoadData(mapData);
	ResetPosition = mapData.vTranslate;
	//m_fOpeningAngle = mapData. XXX
	//m_strObjName = mapData.strObjName;
	//m_strFolder = mapData.strFolderPath;
	//m_strXFile = mapData.strXFilePath;
	//m_strTxtFile = mapData.strTxtPath;
	//m_ObjectType = mapData.objType;
	//
	//m_vScale = mapData.vScale;
	//m_vRotation = mapData.vRotate;
	//m_vTranslation = mapData.vTranslate;
	//
	//CGimmick::SetGimmickCondition(mapData);
	//
	//ST_XFile* xfile = new ST_XFile;
	//
	//g_pFileLoadManager->FileLoad_XFile(m_strFolder, m_strXFile, xfile);
	//
	//if (m_strTxtFile != "")
	//	g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);
	//
	//m_pMesh = xfile->pMesh;
	//m_adjBuffer = xfile->adjBuffer;
	//m_vecMtrls = xfile->vecMtrl;
	//m_vecTextures = xfile->vecTextrure;
	//m_numMtrls = xfile->nMtrlNum;
	//
	//delete xfile;
	//
	//D3DXMATRIXA16 matS, matR, matT;
	//D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	//D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	//D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	//m_matWorld = matS * matR * matT;
	//
	//// OBB TEST
	//m_pOBB = new COBB;
	//m_pOBB->Setup(*this);
	//g_pObjectManager->AddOBBbox(m_pOBB);
	//g_pObjectManager->AddGimmick(this);
	//
	//D3DXVECTOR3 vScale, vRotate, vTranslate;
	//vScale = setData.vScale; // 0.01, 0.03, 0.01, 0.01
	//						 // JW ADD...
	//m_vScale = vScale;
	//vRotate = setData.vRotate;
	//vTranslate = setData.vTranslate;
	//D3DXMATRIXA16 matS, matR, matT;
	//D3DXMatrixScaling(&m_matS, vScale.x, vScale.y, vScale.z);
	//D3DXVECTOR3 v;
	//v.x = D3DXToRadian(vRotate.x);
	//v.y = D3DXToRadian(vRotate.y);
	//v.z = D3DXToRadian(vRotate.z);
	//D3DXMatrixRotationYawPitchRoll(&m_matR, v.x, v.y, v.z);
	//D3DXMatrixTranslation(&m_matT, vTranslate.x, vTranslate.y, vTranslate.z);
	//m_matWorld = m_matS * m_matR * m_matT;
}

void CDoor::Update(float duration)
{
	if (m_ObjectType == eG_Door)
	{
		if (m_isCondition)
		{
			m_fRotAngle += m_fRotationSpeed * duration;
			if (m_fRotAngle >= m_fOpeningAngle)
				m_fRotationSpeed = 0;
			else
				m_fRotationSpeed = 1.0f;
		}
		else
		{
			m_fRotAngle -= m_fRotationSpeed * duration;
			if (m_fRotAngle <= 0)
				m_fRotationSpeed = 0;
			else
				m_fRotationSpeed = 1.0f;
		}

		D3DXMatrixRotationY(&m_matRotGimmick, m_fRotAngle);

		D3DXMATRIXA16 matS, matT;
		D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);

		// Need to Modify... Rotation
		m_matWorld = matS * m_matRotGimmick * matT;

		m_pOBB->Update(&m_matWorld);
	}
	else
	{
		m_pOBB->Update(&m_matWorld);
	}


	// tmp Test
	// static int tmpCount = 0;
	// tmpCount++;
	// if (tmpCount >= 10000)
	// {
	// 	IsOpen = false;
	// 	if (tmpCount >= 20000)
	// 	{
	// 		IsOpen = true;
	// 		tmpCount = 0;
	// 	}
	// }
	//
	// tmp
	//if (g_pGameManager->getOrb())
	//	IsOpen = true;
	//if (g_pGameManager->getBook())
	//	IsOpen = true;
	//
	// if (IsOpen)
	// {
	// 	m_fRotAngle += m_fRotationSpeed * duration;
	// 	if (m_fRotAngle >= m_fOpeningAngle)
	// 		m_fRotationSpeed = 0;
	// 	else
	// 		m_fRotationSpeed = 1.0f;
	// }
	// else
	// {
	// 	m_fRotAngle -= m_fRotationSpeed * duration;
	// 	if (m_fRotAngle <= 0)
	// 		m_fRotationSpeed = 0;
	// 	else
	// 		m_fRotationSpeed = 1.0f;
	// }
}

void CDoor::Update(float duration, bool isSwitchOn)
{
	// if (isSwitchOn)
	// {
	// 	IsOpen = true;
	// 	Update(duration);
	// }
	// else
	// {
	// 	IsOpen = false;
	// 	Update(duration);
	// }
	//m_matWorld = m_matS * m_matRotGimmick * m_matT;
	//m_pOBB->Update(&m_matWorld);
}

void CDoor::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		if (m_ObjectType == eG_DoorFrame)
		{
			D3DXMATRIXA16 matS, matT;
			D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
			D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
			m_matWorld = matS * matT;
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		}
		else if(m_ObjectType == eG_Door)
		{
			D3DXMATRIXA16 matS, matT;
			D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
			D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
			// Need to Modify... Rotation
			m_matWorld = matS * m_matRotGimmick * matT;
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		}
		if (m_pMesh == NULL)
			return;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			else
				g_pD3DDevice->SetTexture(0, m_pTexture);

			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
			m_pMesh->DrawSubset(i);
		}
		g_pD3DDevice->SetTexture(0, NULL);
	}
}
/// Delete Later...
//void CDoor::Setup(string folder, string file)
//{
//	ST_XFile* xfile = new ST_XFile;
//
//	if (!g_pFileLoadManager->FileLoad_XFile(folder, file, xfile))
//	{		
//		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
//		return;
//	}
//
//	m_pMesh = xfile->pMesh;
//	m_adjBuffer = xfile->adjBuffer;
//	m_vecMtrls = xfile->vecMtrl;
//	m_vecTextures = xfile->vecTextrure;
//	m_numMtrls = xfile->nMtrlNum;
//
//	//g_pFileLoadManager->FileLoad_Texture(folder, file, m_pTexture);
//	for (int i = 0; i < m_vecTextures.size(); i++)
//	{
//		if (m_vecTextures[i] == NULL)
//			g_pFileLoadManager->FileLoad_Texture(folder, "cubeworld_texture.tga", m_vecTextures[i]);
//	}
//	//if (m_vecTextures.size() > 1)
//	//{
//	//	for (int i = 0; i < m_vecTextures.size(); i++)
//	//	{
//	//		if (m_vecTextures[i] == NULL)
//	//			g_pFileLoadManager->FileLoad_Texture(folder, "cubeworld_texture.tga", m_vecTextures[i]);
//	//	}
//	//}
//	//else
//	//{
//	//	for (int i = 0; i < m_vecTextures.size(); i++)
//	//	{
//	//		if (m_vecTextures[i] == NULL)
//	//			g_pFileLoadManager->FileLoad_Texture(folder, "cubeworld_metal.tga", m_vecTextures[i]);
//	//	}
//	//}
//	delete xfile;
//
//	/// Later IObject inheritance...
//	m_pOBB = new COBB;
//	m_pOBB->Setup(*this);
//	g_pObjectManager->AddOBBbox(m_pOBB);
//	//g_pObjectManager->AddGimmick(this);
//}
//D3DXMATRIXA16 matWorld;
//D3DXMatrixIdentity(&matWorld);
//D3DXMATRIXA16 matS, matT;
//D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
//D3DXMatrixTranslation(&matT, -25, 0, 0);
//matWorld = matS * m_matRotGimmick * matT;
//matWorld = matS * matT;
//matWorld = m_matRotGimmick * matT;