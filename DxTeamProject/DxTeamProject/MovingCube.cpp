#include "stdafx.h"
#include "MovingCube.h"
#include "OBB.h"

CMovingCube::CMovingCube()
: m_indexNum(1)
, m_vPosition(0, 0, 0)
, m_istrue(false)
, m_fSpeed(1.0f)
, m_fStartPos(0.0f)
, m_fEndPos(8.0f)
{
	render = true;
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
}


CMovingCube::~CMovingCube()
{
}

void CMovingCube::Setup()
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

void CMovingCube::Setup(ST_MapData setData)
{
	CGimmick::SetLoadData(setData);

	m_vPosition = m_vTranslation;

	if (setData.gimmickData.startPos_movingCube < setData.gimmickData.endPos_movingCube)
	{
		m_fStartPos = setData.gimmickData.startPos_movingCube;
		m_fEndPos = setData.gimmickData.endPos_movingCube;
	}
	else
	{
		m_fStartPos = setData.gimmickData.endPos_movingCube;
		m_fEndPos = setData.gimmickData.startPos_movingCube;
	}
	// >> 끝 점이 시작점보다 클 경우 그대로, 작을 경우 반대로 저장

	m_fSpeed = setData.gimmickData.speed_movingCube;
	m_indexNum = setData.gimmickData.directionIndex_movingCube;

	
	ResetPosition = setData.vTranslate;
	//m_strObjName = setData.strObjName;
	//m_strFolder = setData.strFolderPath;
	//m_strXFile = setData.strXFilePath;
	//m_strTxtFile = setData.strTxtPath;
	//m_ObjectType = setData.objType;
	//
	//// D3DXVECTOR3 vScale, vRotate, vTranslate;
	//// 
	//// vScale = setData.vScale; // 0.01, 0.03, 0.01, 0.01
	//// 						 // JW ADD...
	//// m_vScale = vScale;
	//// vRotate = setData.vRotate;
	//// vTranslate = setData.vTranslate;
	//
	//m_vScale = setData.vScale;
	//m_vRotation = setData.vRotate;
	//m_vTranslation = setData.vTranslate;
	//
	//m_vPosition = m_vTranslation;
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
	//m_fStartPos = setData.gimmickData.startPos_movingCube;
	//m_fEndPos = setData.gimmickData.endPos_movingCube;
	//m_fSpeed = setData.gimmickData.speed_movingCube;
	//m_indexNum = setData.gimmickData.directionIndex_movingCube;
	//
	//m_vPosition.y += m_fStartPos;
	//
	//D3DXMATRIXA16 matS, matR, matT;
	//D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	//D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	//D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	//
	//m_matS = matS;
	//m_matR = matR;
	//m_matT = matT;
	//
	//m_matWorld = matS * matR * matT;
	//
	//m_pOBB = new COBB;
	//m_pOBB->Setup(*this);
	//g_pObjectManager->AddOBBbox(m_pOBB);
	//g_pObjectManager->AddGimmick(this);
	//
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

void CMovingCube::Update(float duration)
{
	D3DXVECTOR3 start_pos, end_pos;
	if (m_indexNum == 0)
	{
		float start = m_vPosition.x + m_fStartPos;
		float end = m_vPosition.x + m_fEndPos;
		start_pos = m_vPosition + D3DXVECTOR3(start, 0, 0);
		end_pos = m_vPosition + D3DXVECTOR3(end, 0, 0);
	}
	else if(m_indexNum == 1)
	{
		float start = m_vPosition.y + m_fStartPos;
		float end = m_vPosition.y + m_fEndPos;
		start_pos = m_vPosition + D3DXVECTOR3(0, start, 0);
		end_pos = m_vPosition + D3DXVECTOR3(0, end, 0);
	}
	else if (m_indexNum == 2)
	{
		float start = m_vPosition.z + m_fStartPos;
		float end = m_vPosition.z + m_fEndPos;
		start_pos = m_vPosition + D3DXVECTOR3(0, 0, start);
		end_pos = m_vPosition + D3DXVECTOR3(0, 0, end);
	}
		
	if (m_indexNum == 0)
	{
		if (m_istrue == false)
		{
			m_vPosition.x += m_fSpeed * duration;
			if (m_vPosition.x >= m_fEndPos)
				m_istrue = true;
		}
		else
		{
			m_vPosition.x -= m_fSpeed * duration;
			if (m_vPosition.x <= m_fStartPos)
				m_istrue = false;
		}
	}
	else if (m_indexNum == 1)
	{
		if (m_istrue == false)
		{
			m_vPosition.y += m_fSpeed * duration;
			if (m_vPosition.y >= m_fEndPos)
				m_istrue = true;
		}
		else
		{
			m_vPosition.y -= m_fSpeed * duration;
			if (m_vPosition.y <= m_fStartPos)
				m_istrue = false;
		}
	}
	else if (m_indexNum == 2)
	{
		if (m_istrue == false)
		{
			m_vPosition.z += m_fSpeed * duration;
			if (m_vPosition.z >= m_fEndPos)
				m_istrue = true;
		}
		else
		{
			m_vPosition.z -= m_fSpeed * duration;
			if (m_vPosition.z <= m_fStartPos)
				m_istrue = false;
		}
	}

	if(g_pObjectManager->ResetCube  == true)
		m_vPosition = PresentPosition;
	// MJ Code
	//if (m_indexNum == 0 && m_istrue == false)
	//{
	//	m_vPosition.y += m_fSpeed * duration;
	//	if (m_vPosition.y > m_fStartPos)
	//		m_istrue = true;
	//}
	//else if (m_indexNum == 0 && m_istrue == true)
	//{
	//	m_vPosition.y -= m_fSpeed * duration;
	//	if (m_vPosition.y < m_fEndPos)
	//		m_istrue = false;
	//}
	//if (m_indexNum == 1 && m_istrue == false)
	//{
	//	m_vPosition.x += m_fSpeed * duration;
	//	if (m_vPosition.x > m_fStartPos)
	//		m_istrue = true;
	//}
	//else if (m_indexNum == 1 && m_istrue == true)
	//{
	//	m_vPosition.x -= m_fSpeed * duration;
	//	if (m_vPosition.x < m_fEndPos)
	//		m_istrue = false;
	//}
	//if (m_indexNum == 2 && m_istrue == false)
	//{
	//	m_vPosition.z += m_fSpeed * duration;
	//	if (m_vPosition.z > m_fStartPos)
	//		m_istrue = true;
	//}
	//else if (m_indexNum == 2 && m_istrue == true)
	//{
	//	m_vPosition.z -= m_fSpeed * duration;
	//	if (m_vPosition.z < m_fEndPos)
	//		m_istrue = false;
	//}
	
	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = m_matS * m_matR * m_matT;

	

	m_pOBB->Update(&m_matWorld);
}

void CMovingCube::Update()
{
}

void CMovingCube::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

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
