#include "stdafx.h"
#include "Box.h"

CBox::CBox()
	: m_fWidth(1.0f)
	, m_fHeight(1.0f)
	, m_fDepth(1.0f)
{
	m_strName = string("Box") + to_string(m_nRefCount);
}

CBox::~CBox()
{
}

void CBox::Setup()
{
	D3DXCreateBox(g_pD3DDevice, m_fWidth, m_fHeight, m_fDepth, &m_pMesh, NULL);

	float maxLength = max(m_fWidth, m_fHeight);
	maxLength = max(maxLength, m_fDepth);
	m_fBoundingSphere = maxLength;

	// modify? 12.0f -> 48.0f?
	m_vInverseRotationInertia.x = 12.0f / (GetMass() * (m_fHeight * m_fHeight + m_fDepth  * m_fDepth));
	m_vInverseRotationInertia.y = 12.0f / (GetMass() * (m_fWidth  * m_fWidth  + m_fDepth  * m_fDepth));
	m_vInverseRotationInertia.z = 12.0f / (GetMass() * (m_fWidth  * m_fWidth  + m_fHeight * m_fHeight));
}

void CBox::Setup(const ST_MapData & mapData)
{
	m_strObjName = mapData.strObjName;

	m_strFolder = mapData.strFolderPath;
	m_strXFile = mapData.strXFilePath;
	m_strTxtFile = mapData.strTxtPath;

	m_ObjectType = mapData.objType;

	D3DXVECTOR3 vScale, vRotate;
	vScale = mapData.vScale;
	vRotate = mapData.vRotate;
	m_vPosition = mapData.vTranslate;

	m_Color = mapData.dxColor;
	// color change
	this->ChangeObjectColor();

	m_fWidth = vScale.x;
	m_fHeight = vScale.y;
	m_fDepth = vScale.z;

	Setup();

	// ============================================================

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(vRotate.x);
	v.y = D3DXToRadian(vRotate.y);
	v.z = D3DXToRadian(vRotate.z);

	D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matR * matT;
}

string CBox::GetName()
{
	return m_strName;
}