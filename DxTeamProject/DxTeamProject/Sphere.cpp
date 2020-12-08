#include "stdafx.h"
#include "Sphere.h"

CSphere::CSphere() 
	: m_fRadius(1.0f)
	//, resolver(maxContacts * 8)
{
	m_strName = string("Sphere") + to_string(m_nRefCount);
	//cData.contactArray = contacts;
}

CSphere::~CSphere()
{
}

void CSphere::Setup()
{
	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMesh, NULL);
	m_fBoundingSphere = m_fRadius;
	m_vInverseRotationInertia.x = 5.0f / (2 * GetMass() * m_fRadius * m_fRadius);
	m_vInverseRotationInertia.y = 5.0f / (2 * GetMass() * m_fRadius * m_fRadius);
	m_vInverseRotationInertia.z = 5.0f / (2 * GetMass() * m_fRadius * m_fRadius);

	/// Collide
	//m_vPosition.y = 15;
	//D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//collisionsphere.m_pObject = this;
	//collisionsphere.radius = m_fRadius;
	//collisionsphere.calculateInternals();
}

void CSphere::Setup(const ST_MapData & mapData)
{
	Setup();

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
	this->ChangeObjectColor();

	m_fRadius = vScale.x;
	m_fRadius = vScale.y;
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

//void CSphere::Update(float duration)
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
//	m_vTorque = angularforce;
//
//	m_vAngularAcceleration.x = m_vTorque.x * m_vInverseRotationInertia.x;
//	m_vAngularAcceleration.y = m_vTorque.y * m_vInverseRotationInertia.y;
//	m_vAngularAcceleration.z = m_vTorque.z * m_vInverseRotationInertia.z;
//
//	m_vAngularVelocity += m_vAngularAcceleration * duration;
//	m_vAngularVelocity *= powf(m_fDamping, duration);
//	// tmp Test... Need to AngularDrag
//	m_vAngularVelocity *= 0.999f;
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
//	collisionsphere.calculateInternals();
//	GenerateContacts();
//	CollideUpdate(duration);
//}
//void CSphere::GenerateContacts()
//{
//	CollisionPlane plane;
//	plane.direction = D3DXVECTOR3(0, 1, 0);
//	plane.offset = 0;
//
//	cData.reset(maxContacts);
//	cData.friction = 0.9f;
//	cData.restitution = 0.6;
//	cData.tolerance = 0.1f;
//
//	CollisionDetector::SphereAndHalfSpace(this->collisionsphere, plane, &cData);
//}
//
//void CSphere::CollideUpdate(float duration)
//{
//	resolver.resolveContacts(cData.contactArray, cData.contactCount, duration);
//}

void CSphere::Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
{
	if (D3DXSphereBoundProbe(&m_vPosition, m_fRadius, &ray.GetOrigin(), &ray.GetDirection()) == true)
	{
		m_isPicked = true;
		m_outLineColor = playerColor;
	}
	else
	{
		m_isPicked = false;
	}
	vecVPos.push_back(m_vPosition);
	vecIsPick.push_back(m_isPicked);
}

string CSphere::GetName()
{
	return m_strName;
}