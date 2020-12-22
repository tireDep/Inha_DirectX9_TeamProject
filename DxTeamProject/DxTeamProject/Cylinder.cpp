#include "stdafx.h"
#include "IObject.h"
#include "Cylinder.h"

CCylinder::CCylinder()
	: m_fRadius(0.5f)
	, m_fHeight(1.0f)
{
	m_strName = string("Cylinder") + to_string(m_nRefCount);
}

CCylinder::~CCylinder()
{
}

void CCylinder::Setup()
{
	D3DXCreateCylinder(g_pD3DDevice, m_fRadius, m_fRadius, m_fHeight, 10, 10, &m_pMesh, NULL);

	//if (m_fRadius >= m_fHeight / 2.0f)
	//	m_fBoundingSphere = m_fRadius;
	//else
	//	m_fBoundingSphere = m_fHeight / 2.0f;
}

void CCylinder::Setup(const ST_MapData & mapData)
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
	m_vPosition = m_vTranslation;

	//---ÀúÀå
	saveRotation = mapData.vRotate;
	saveTranslation = mapData.vTranslate;

	m_Color = mapData.dxColor;
	ResetColor = mapData.dxColor;
	this->ChangeObjectColor();

	m_fRadius *= m_vScale.x;
	m_fHeight *= m_vScale.y;

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = matS * matR * matT;

	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	g_pObjectManager->AddCylinder(this);
}

void CCylinder::Update(float duration)
{
	PObject::Update(duration);
	m_pOBB->Update(&m_matWorld);
}

bool CCylinder::hasIntersected(CCylinder * otherCylinder)
{
	if (this == otherCylinder)
		return false;
	if (this->m_pOBB->IsCollision(otherCylinder->GetOBB()))
		return true;
	return false;
}

bool CCylinder::hasIntersected(IObject * otherIObject)
{
	if (this->m_pOBB->IsCollision(otherIObject->GetOBB()))
		return true;
	return false;
}

string CCylinder::GetName()
{
	return m_strName;
}