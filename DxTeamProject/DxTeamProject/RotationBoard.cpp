#include "stdafx.h"
#include "RotationBoard.h"

CRotationBoard::CRotationBoard()
	: rotationAxial(RotationAxial::NONE)
	, m_fRotationSpeed(1.0)
	, m_fRotAngle(0.0f)
{
	D3DXMatrixIdentity(&m_matRotGimmick);
	m_strName = string("RotationBoard") + to_string(m_nRefCount);
}

CRotationBoard::~CRotationBoard()
{
}

void CRotationBoard::Setup(const ST_MapData & mapData)
{
	m_strObjName = mapData.strObjName;
	m_strFolder = mapData.strFolderPath;
	m_strXFile = mapData.strXFilePath;
	m_strTxtFile = mapData.strTxtPath;
	m_ObjectType = mapData.objType;

	m_vScale = mapData.vScale;
	m_vRotation = mapData.vRotate;
	m_vTranslation = mapData.vTranslate;

	m_fRotationSpeed = mapData.gimmickData.roationSpeed_rotaitonBoard;
	if (mapData.gimmickData.roationAxialIndex_rotaitonBoard == 0)
		rotationAxial = RotationAxial::Rotation_X;
	else if (mapData.gimmickData.roationAxialIndex_rotaitonBoard == 1)
		rotationAxial = RotationAxial::Rotation_Y;
	else if (mapData.gimmickData.roationAxialIndex_rotaitonBoard == 2)
		rotationAxial = RotationAxial::Rotation_Z;
	else if (mapData.gimmickData.roationAxialIndex_rotaitonBoard == 3)
		rotationAxial = RotationAxial::NONE;

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

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = matS * matR * matT;

	// OBB TEST
	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	g_pObjectManager->AddGimmick(this);

	//D3DXVECTOR3 vScale, vRotate, vTranslate;
	//vScale = setData.vScale; // 0.01, 0.03, 0.01, 0.01
	//// JW ADD...
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
	//m_matWorld = matS * matR * matT;
}

//void RotationBoard::Setup(string folder, string file)
//{
//	ST_XFile* xfile = new ST_XFile;
//
//	if (!g_pFileLoadManager->FileLoad_XFile(folder, file, xfile))
//	{
//		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
//		return;
//	}
//	m_pMesh = xfile->pMesh;
//	m_adjBuffer = xfile->adjBuffer;
//	m_vecMtrls = xfile->vecMtrl;
//	m_vecTextures = xfile->vecTextrure;
//	m_numMtrls = xfile->nMtrlNum;
//
//	delete xfile;
//}

void CRotationBoard::Update(float duration)
{
	switch (rotationAxial)
	{
	case RotationAxial::Rotation_X:
		m_fRotAngle += m_fRotationSpeed * duration;
		if (m_fRotAngle > 2 * D3DX_PI)
			m_fRotAngle -= 2 * D3DX_PI;
		D3DXMatrixRotationX(&m_matRotGimmick, m_fRotAngle);
		break;
	case RotationAxial::Rotation_Y:
		m_fRotAngle += m_fRotationSpeed * duration;
		if (m_fRotAngle > 2 * D3DX_PI)
			m_fRotAngle -= 2 * D3DX_PI;
		D3DXMatrixRotationY(&m_matRotGimmick, m_fRotAngle);
		break;
	case RotationAxial::Rotation_Z:
		m_fRotAngle += m_fRotationSpeed * duration;
		if (m_fRotAngle > 2 * D3DX_PI)
			m_fRotAngle -= 2 * D3DX_PI;
		D3DXMatrixRotationZ(&m_matRotGimmick, m_fRotAngle);
		break;
	case RotationAxial::NONE:
			D3DXMatrixIdentity(&m_matRotGimmick);
		break;
	default:
		break;
	}
	
	D3DXMATRIXA16 matS, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);

	// Need to Modify... Rotation
	m_matWorld = matS * m_matRotGimmick * matT;
	m_pOBB->Update(&m_matWorld);
}

void CRotationBoard::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
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
}