#include "stdafx.h"
#include "RotationBoard.h"

CRotationBoard::CRotationBoard() :
	m_fRotationSpeed(0.0f),
	m_rotationAxial(RotationAxial::NONE),
	m_NowState(RotationAxial::NONE),
	m_fRotAngle(0.0f)
{
	m_pMesh = NULL;
	m_pTexture = NULL;
}

CRotationBoard::~CRotationBoard()
{
}

void CRotationBoard::Setup(ST_MapData setData)
{
	m_fRotationSpeed = 0.0f;
	m_rotationAxial = RotationAxial::NONE;
	m_NowState = RotationAxial::NONE;

	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;
	m_vScale = setData.vScale;
	m_vRotate = setData.vRotate;
	m_vTranslate = setData.vTranslate;

	m_fRotationSpeed = setData.gimmickData.roationSpeed;
	if (setData.gimmickData.roationAxialIndex == 0)
		m_rotationAxial = RotationAxial::Rotation_X; 
	else if (setData.gimmickData.roationAxialIndex == 1)
		m_rotationAxial = RotationAxial::Rotation_Y;
	else if (setData.gimmickData.roationAxialIndex == 2)
		m_rotationAxial = RotationAxial::Rotation_Z;
	else if (setData.gimmickData.roationAxialIndex == 3)
		m_rotationAxial = RotationAxial::NONE;

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

void CRotationBoard::Update()
{
	switch (m_rotationAxial)
	{
	case RotationAxial::Rotation_X:
		m_fRotAngle += m_fRotationSpeed * 0.001f;
		if (m_fRotAngle > 2 * D3DX_PI)
			m_fRotAngle -= 2 * D3DX_PI;
		// D3DXMatrixRotationX(&m_matRotGimmick, m_fRotAngle);
		break;
	case RotationAxial::Rotation_Y:
		m_fRotAngle += m_fRotationSpeed * 0.001f;
		if (m_fRotAngle > 2 * D3DX_PI)
			m_fRotAngle -= 2 * D3DX_PI;
		// D3DXMatrixRotationY(&m_matRotGimmick, m_fRotAngle);
		break;
	case RotationAxial::Rotation_Z:
		m_fRotAngle += m_fRotationSpeed * 0.001f;
		if (m_fRotAngle > 2 * D3DX_PI)
			m_fRotAngle -= 2 * D3DX_PI;
		// D3DXMatrixRotationZ(&m_matRotGimmick, m_fRotAngle);
		break;
	case RotationAxial::NONE:
		// D3DXMatrixIdentity(&m_matRotGimmick);
		break;
	}
}

void CRotationBoard::Render()
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

void CRotationBoard::SetRotationAxialIndex(int index)
{
	if (index == 0)
		m_rotationAxial = RotationAxial::Rotation_X;
	else if (index == 1)
		m_rotationAxial = RotationAxial::Rotation_Y;
	else if (index == 2)
		m_rotationAxial = RotationAxial::Rotation_Z;
}

int CRotationBoard::GetRotationAxialIndex()
{
	if (m_rotationAxial == RotationAxial::Rotation_X)
		return 0;
	else if (m_rotationAxial == RotationAxial::Rotation_Y)
		return 1;
	else if (m_rotationAxial == RotationAxial::Rotation_Z)
		return 2;
	else if (m_rotationAxial == RotationAxial::NONE)
		return 3;
}
