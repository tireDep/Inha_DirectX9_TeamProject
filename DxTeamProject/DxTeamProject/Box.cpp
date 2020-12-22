#include "stdafx.h"
#include "IObject.h"
#include "Box.h"
#include "Cylinder.h"

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

	//float maxLength = max(m_fWidth, m_fHeight);
	//maxLength = max(maxLength, m_fDepth);
	//m_fBoundingSphere = maxLength / 2.0f;
}

void CBox::Setup(const ST_MapData & mapData)
{
	Setup();

	m_strObjName = mapData.strObjName;
	m_strFolder = mapData.strFolderPath;
	m_strXFile = mapData.strXFilePath;
	m_strTxtFile = mapData.strTxtPath;
	m_ObjectType = mapData.objType;

	m_vScale = mapData.vScale;
	m_vRotation = mapData.vRotate;
	m_vTranslation = mapData.vTranslate;

	//---ÀúÀå
	saveRotation = mapData.vRotate;
	saveTranslation = mapData.vTranslate; 
	
	m_vPosition = m_vTranslation;

	m_Color = mapData.dxColor;
	ResetColor = mapData.dxColor;
	this->ChangeObjectColor();

	m_fWidth *= m_vScale.x;
	m_fHeight *= m_vScale.y;
	m_fDepth *= m_vScale.z;

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = matS * matR * matT;

	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	g_pObjectManager->AddBox(this);
}

void CBox::Update(float duration)
{
	PObject::Update(duration);
	m_pOBB->Update(&m_matWorld);
}

bool CBox::hasIntersected(CBox * otherBox)
{
	if (this == otherBox)
		return false;
	if (this->m_pOBB->IsCollision(otherBox->GetOBB()))
		return true;
	return false;
}

bool CBox::hasIntersected(CCylinder * otherCylinder)
{
	if (this->m_pOBB->IsCollision(otherCylinder->GetOBB()))
		return true;
	return false;
}

bool CBox::hasIntersected(IObject * otherIObject)
{
	if (this->m_pOBB->IsCollision(otherIObject->GetOBB()))
		return true;
	else
		return false;
}

string CBox::GetName()
{
	return m_strName;
}