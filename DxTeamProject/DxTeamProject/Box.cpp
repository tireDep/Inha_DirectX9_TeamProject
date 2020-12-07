#include "stdafx.h"
#include "Box.h"

CBox::CBox()
	: m_fWidth(1.0f)
	, m_fHeight(1.0f)
	, m_fDepth(1.0f)
	//, resolver(maxContacts * 8)
{
	m_strName = string("Box") + to_string(m_nRefCount);
	//cData.contactArray = contacts;
}

CBox::~CBox()
{
}

void CBox::Setup()
{
	D3DXCreateBox(g_pD3DDevice, m_fWidth, m_fHeight, m_fDepth, &m_pMesh, NULL);

	float maxLength = max(m_fWidth, m_fHeight);
	maxLength = max(maxLength, m_fDepth);
	m_fBoundingSphere = maxLength / 2.0f;

	// modify? 12.0f -> 48.0f?
	m_vInverseRotationInertia.x = 12.0f / (GetMass() * (m_fHeight * m_fHeight + m_fDepth  * m_fDepth));
	m_vInverseRotationInertia.y = 12.0f / (GetMass() * (m_fWidth  * m_fWidth  + m_fDepth  * m_fDepth));
	m_vInverseRotationInertia.z = 12.0f / (GetMass() * (m_fWidth  * m_fWidth  + m_fHeight * m_fHeight));

	// Collide
	//m_vPosition.x = -2;
	//m_vPosition.y = 15;
	//D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//collisionbox.m_pObject = this;
	//collisionbox.halfSize.x = m_fWidth;
	//collisionbox.halfSize.y = m_fHeight;
	//collisionbox.halfSize.z = m_fDepth;
	//collisionbox.calculateInternals();
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
	
	// Collide
	//collisionbox.m_pObject = this;
	//collisionbox.halfSize.x = m_fWidth;
	//collisionbox.halfSize.y = m_fHeight;
	//collisionbox.halfSize.z = m_fDepth;
	//collisionbox.calculateInternals();
}

//void CBox::Update(float duration)
//{
//	D3DXVECTOR3 linearforce, angularforce;
//	if (m_isForceApplied)
//	{
//		if (!hasFiniteMass()) return;
//		linearforce = m_vForceVector * GetMass();
//		D3DXVec3Cross(&angularforce, &m_vForceLocation, &m_vForceVector);
//		m_isForceApplied = false;
//	}
//	else
//	{
//		linearforce = D3DXVECTOR3(0, 0, 0);
//		angularforce = D3DXVECTOR3(0, 0, 0);
//	}
//
//	if (m_finverseMass <= 0.0f) return;
//	assert(duration > 0.0f);
//
//	m_vLinearAcceleration = (linearforce + GRAVITY) * m_finverseMass;
//	//m_vLinearAcceleration = (linearforce) * m_finverseMass;
//	m_vLinearVelocity += (m_vLinearAcceleration * duration);
//	m_vLinearVelocity *= powf(m_fDamping, duration);
//	m_vLinearVelocity *= m_fLinearDrag;
//	if (CloseToZero(m_vLinearVelocity.x) && CloseToZero(m_vLinearVelocity.y) && CloseToZero(m_vLinearVelocity.z))
//	{
//		m_vLinearVelocity.x = m_vLinearVelocity.y = m_vLinearVelocity.z = 0.0f;
//	}
//	else
//		m_vPosition += (m_vLinearVelocity * duration);
//
//	D3DXMATRIXA16 totalTransaltion;
//	D3DXMatrixTranslation(&totalTransaltion, m_vPosition.x, m_vPosition.y, m_vPosition.z);
//
//	// Need to modify
//	//m_vTorque = angularforce * 10000000.0f;
//	m_vTorque = angularforce;
//
//	m_vAngularAcceleration.x = m_vTorque.x * m_vInverseRotationInertia.x;
//	m_vAngularAcceleration.y = m_vTorque.y * m_vInverseRotationInertia.y;
//	m_vAngularAcceleration.z = m_vTorque.z * m_vInverseRotationInertia.z;
//
//	m_vAngularVelocity += m_vAngularAcceleration * duration;
//	m_vAngularVelocity *= powf(m_fDamping, duration);
//	// tmp Test... Need to AngularDrag
//	m_vAngularVelocity *= 0.995f;
//	if (CloseToZero(m_vAngularVelocity.x) && CloseToZero(m_vAngularVelocity.y) && CloseToZero(m_vAngularVelocity.z))
//	{
//		m_vAngularVelocity.x = m_vAngularVelocity.y = m_vAngularVelocity.z = 0.0f;
//	}
//	else
//		m_vAngularVelocity += (m_vAngularVelocity * duration);
//
//	m_stOrientation.setXAngle(m_stOrientation.getXAngle() + m_vAngularVelocity.x * duration);
//	m_stOrientation.setYAngle(m_stOrientation.getYAngle() + m_vAngularVelocity.y * duration);
//	m_stOrientation.setZAngle(m_stOrientation.getZAngle() + m_vAngularVelocity.z * duration);
//
//	D3DXMATRIXA16 rotationX, rotationY, rotationZ, totalRotation;
//	D3DXMatrixRotationX(&rotationX, m_stOrientation.getXAngle());
//	D3DXMatrixRotationY(&rotationY, m_stOrientation.getYAngle());
//	D3DXMatrixRotationZ(&rotationZ, m_stOrientation.getZAngle());
//	D3DXMatrixMultiply(&totalRotation, &rotationX, &rotationY);
//	D3DXMatrixMultiply(&totalRotation, &totalRotation, &rotationZ);
//
//	D3DXMatrixMultiply(&m_matWorld, &totalRotation, &totalTransaltion);
//
//	// 
//	//collisionbox.calculateInternals();
//	//GenerateContacts();
//	//CollideUpdate(duration);
//}

//void CBox::GenerateContacts()
//{
//	CollisionPlane plane;
//	plane.direction = D3DXVECTOR3(1, 1, 0);
//	plane.offset = 0;
//
//	cData.reset(maxContacts);
//	cData.friction = 0.9f;
//	cData.restitution = 0.6;
//	cData.tolerance = 0.1f;
//
//	CollisionDetector::BoxAndHalfSpace(this->collisionbox, plane, &cData);
//}
//
//void CBox::CollideUpdate(float duration)
//{
//	resolver.resolveContacts(cData.contactArray, cData.contactCount, duration);
//}

string CBox::GetName()
{
	return m_strName;
}