#include "stdafx.h"
#include "RotationBoard.h"

CRotationBoard::CRotationBoard()
	//: m_pMesh(NULL)
	//, m_adjBuffer(NULL)
	//, m_numMtrls(0)
	: rotationAxial(RotationAxial::NONE)
	// Test Y Rotation
	//: rotationAxial(RotationAxial::Rotation_Y)
	, m_fRotationSpeed(1.0)
	, m_fRotAngle(0.0f)
{
	//D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRotGimmick);
}

CRotationBoard::~CRotationBoard()
{
	//SafeRelease(m_pMesh);
	//SafeRelease(m_adjBuffer);
}

void CRotationBoard::Setup(ST_MapData setData)
{
	m_fRotationSpeed = 0.0f;
	rotationAxial = RotationAxial::NONE;

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

	m_fRotationSpeed = setData.gimmickData.roationSpeed;
	if (setData.gimmickData.roationAxialIndex == 0)
		rotationAxial = RotationAxial::Rotation_X;
	else if (setData.gimmickData.roationAxialIndex == 1)
		rotationAxial = RotationAxial::Rotation_Y;
	else if (setData.gimmickData.roationAxialIndex == 2)
		rotationAxial = RotationAxial::Rotation_Z;
	else if (setData.gimmickData.roationAxialIndex == 3)
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

	//D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&m_matS, vScale.x, vScale.y, vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(vRotate.x);
	v.y = D3DXToRadian(vRotate.y);
	v.z = D3DXToRadian(vRotate.z);

	D3DXMatrixRotationYawPitchRoll(&m_matR, v.x, v.y, v.z);

	D3DXMatrixTranslation(&m_matT, vTranslate.x, vTranslate.y, vTranslate.z);
	//m_matWorld = matS * matR * matT;

	// OBB TEST
	m_pOBB = new CPSOBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	g_pObjectManager->AddGimmick(this);
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
	
	m_matWorld = m_matS * m_matRotGimmick * m_matT;
	m_pOBB->Update(&m_matWorld);
}

void CRotationBoard::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		// Test
		//D3DXMATRIXA16 matS, matT;
		//D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
		//D3DXMatrixTranslation(&matT, -25, 0, 0);
		
		// need to Modify... Roation
		m_matR = m_matRotGimmick;
		m_matWorld = m_matS * m_matR * m_matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		if (m_pMesh == NULL)
			return;
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
		}
		m_pMesh->DrawSubset(0);
		g_pD3DDevice->SetTexture(0, NULL);
	}
}