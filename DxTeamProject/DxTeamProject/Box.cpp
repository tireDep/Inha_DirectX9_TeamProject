#include "stdafx.h"
#include "IObject.h"
#include "Gimmick.h"
//#include "Sphere.h"
#include "Box.h"
#include "Cylinder.h"

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

	//float maxLength = max(m_fWidth, m_fHeight);
	//maxLength = max(maxLength, m_fDepth);
	//m_fBoundingSphere = maxLength / 2.0f;

	// modify? 12.0f -> 48.0f?
	//m_vInverseRotationInertia.x = 12.0f / (GetMass() * (m_fHeight * m_fHeight + m_fDepth  * m_fDepth));
	//m_vInverseRotationInertia.y = 12.0f / (GetMass() * (m_fWidth  * m_fWidth  + m_fDepth  * m_fDepth));
	//m_vInverseRotationInertia.z = 12.0f / (GetMass() * (m_fWidth  * m_fWidth  + m_fHeight * m_fHeight));
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

	//m_strObjName = mapData.strObjName;
	//m_strFolder = mapData.strFolderPath;
	//m_strXFile = mapData.strXFilePath;
	//m_strTxtFile = mapData.strTxtPath;
	//m_ObjectType = mapData.objType;
	//D3DXVECTOR3 vScale, vRotate;
	//vScale = mapData.vScale;
	//// JW ADD...
	//m_vScale = vScale;
	//vRotate = mapData.vRotate;
	//m_vPosition = mapData.vTranslate;
	//m_Color = mapData.dxColor;
	//// color change
	//this->ChangeObjectColor();
	//m_fWidth = vScale.x;
	//m_fHeight = vScale.y;
	//m_fDepth = vScale.z;
	//// ============================================================
	//D3DXMATRIXA16 matS, matR, matT;
	//D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);
	//D3DXVECTOR3 v;
	//v.x = D3DXToRadian(vRotate.x);
	//v.y = D3DXToRadian(vRotate.y);
	//v.z = D3DXToRadian(vRotate.z);
	//D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);
	//D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//m_matWorld = matS * matR * matT;
	// Collide
	//collisionbox.m_pObject = this;
	//collisionbox.halfSize.x = m_fWidth;
	//collisionbox.halfSize.y = m_fHeight;
	//collisionbox.halfSize.z = m_fDepth;
	//collisionbox.calculateInternals();

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = matS * matR * matT;

	// OBB TEST
	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	g_pObjectManager->AddBox(this);
}

void CBox::Update(float duration)
{
	PObject::Update(duration);
	
	// OBB TEST
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
	{
		return true;
	}
	else
	{
		return false;
	}
	//if (this->m_pOBB->IsCollision(otherIObject->GetOBB()))
	//{
	//	D3DXVECTOR3 v;
	//	v = this->GetPosition() - otherIObject->GetOBB()->GetCenter();
	//	D3DXVec3Normalize(&v, &v);
	//	this->SetPusingForce(v);
	//	//this->SetLinearVelocity(-1 * this->GetLinearVelocity());
	//	return true;
	//}
	//return false;
}

//bool CBox::hasIntersected(CGimmick * otherIObject)
//{
//	if (this->m_pOBB->IsCollision(otherIObject->GetOBB()))
//		return true;
//	return false;
//	//if (this->m_pOBB->IsCollision(otherIObject->GetOBB()))
//	//{
//	//	D3DXVECTOR3 v;
//	//	v = this->GetPosition() - otherIObject->GetOBB()->GetCenter();
//	//	D3DXVec3Normalize(&v, &v);
//	//	this->SetPusingForce(v);
//	//	//this->SetLinearVelocity(-1 * this->GetLinearVelocity());
//	//	return true;
//	//}
//	//return false;
//}

string CBox::GetName()
{
	return m_strName;
}

/// Delete Later...
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
//bool CBox::hasIntersected(CSphere & otherSphere)
//{
//	D3DXVECTOR3 center = otherSphere.GetPosition();
//	D3DXMATRIXA16 inverseBoxMatrix;
//	D3DXMatrixInverse(&inverseBoxMatrix, NULL, &m_matWorld);
//	D3DXVECTOR3 SphereToBoxCenter;
//	D3DXVec3TransformCoord(&SphereToBoxCenter, &center, &inverseBoxMatrix);
//
//	if (fabsf(SphereToBoxCenter.x) - otherSphere.GetRadius() > m_fWidth / 2.0f ||
//		fabsf(SphereToBoxCenter.y) - otherSphere.GetRadius() > m_fHeight / 2.0f ||
//		fabsf(SphereToBoxCenter.z) - otherSphere.GetRadius() > m_fDepth / 2.0f)
//		return false;
//
//	D3DXVECTOR3 closestPt(0, 0, 0);
//	float dist;
//
//	dist = SphereToBoxCenter.x;
//	if (dist > m_fWidth / 2.0f) dist = m_fWidth / 2.0f;
//	if (dist < -m_fWidth / 2.0f) dist = -m_fWidth / 2.0f;
//	closestPt.x = dist;
//
//	dist = SphereToBoxCenter.y;
//	if (dist > m_fHeight / 2.0f) dist = m_fHeight / 2.0f;
//	if (dist < -m_fHeight / 2.0f) dist = -m_fHeight / 2.0f;
//	closestPt.y = dist;
//
//	dist = SphereToBoxCenter.z;
//	if (dist > m_fDepth / 2.0f) dist = m_fDepth / 2.0f;
//	if (dist < -m_fDepth / 2.0f) dist = -m_fDepth / 2.0f;
//	closestPt.z = dist;
//
//	D3DXVECTOR3 tmp = closestPt - SphereToBoxCenter;
//	dist = D3DXVec3LengthSq(&tmp);
//	if (dist > otherSphere.GetRadius()*otherSphere.GetRadius())
//		return false;
//
//	return true;
//}