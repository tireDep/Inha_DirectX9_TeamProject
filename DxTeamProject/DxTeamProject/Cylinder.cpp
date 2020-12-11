#include "stdafx.h"
#include "IObject.h"
#include "Gimmick.h"
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

	if (m_fRadius >= m_fHeight / 2.0f)
		m_fBoundingSphere = m_fRadius;
	else
		m_fBoundingSphere = m_fHeight / 2.0f;

	//m_vInverseRotationInertia.x = 12.0f / (GetMass() * (m_fHeight * m_fHeight + 3 * m_fRadius * m_fRadius));
	//m_vInverseRotationInertia.y = 2.0f / (GetMass() * m_fRadius * m_fRadius);
	//m_vInverseRotationInertia.z = 12.0f / (GetMass() * (m_fHeight * m_fHeight + 3 * m_fRadius * m_fRadius));
}

void CCylinder::Setup(const ST_MapData & mapData)
{
	Setup();

	m_strObjName = mapData.strObjName;

	m_strFolder = mapData.strFolderPath;
	m_strXFile = mapData.strXFilePath;
	m_strTxtFile = mapData.strTxtPath;

	m_ObjectType = mapData.objType;

	D3DXVECTOR3 vScale, vRotate;
	vScale = mapData.vScale;
	// JW ADD...
	m_vScale = vScale;
	vRotate = mapData.vRotate;
	m_vPosition = mapData.vTranslate;

	m_Color = mapData.dxColor;
	// color change
	this->ChangeObjectColor();

	m_fRadius = vScale.x;
	m_fHeight = vScale.y;
	m_fRadius = vScale.z;

	// ============================================================

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(vRotate.x);
	v.y = D3DXToRadian(vRotate.y);
	v.z = D3DXToRadian(vRotate.z);

	// D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);
	D3DXMatrixRotationX(&matR, v.x);
	D3DXMatrixRotationY(&matR, v.y);
	D3DXMatrixRotationZ(&matR, v.z);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matR * matT;
}

void CCylinder::Update(float duration)
{
	PObject::Update(duration);
	// OBB TEST
	m_pOBB->Update(&m_matWorld);
}

bool CCylinder::hasIntersected(CCylinder * otherCylinder)
{
	if (this->m_pOBB->IsCollision(otherCylinder->GetOBB()))
		return true;
	return false;
}

//bool CCylinder::hasIntersected(CGimmick * otherIObject)
//{
//	if (this->m_pOBB->IsCollision(otherIObject->GetOBB()))
//		return true;
//	return false;
//}

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