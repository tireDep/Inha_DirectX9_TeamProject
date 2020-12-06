#include "stdafx.h"
#include "PSBox.h"

CPSBox::CPSBox()
	: m_fWidth(1.0f)
	, m_fHeight(1.0f)
	, m_fDepth(1.0f)
{
	m_strName = string("Box") + to_string(m_nRefCount);
}

CPSBox::~CPSBox()
{
}

void CPSBox::Setup()
{
	//D3DXCreateBox(g_pD3DDevice, m_fWidth, m_fHeight, m_fDepth, &m_pMesh, NULL);
	//// tmp BoundingSphere
	//float maxLength = max(m_fWidth, m_fHeight);
	//maxLength = max(maxLength, m_fDepth);
	////m_fBoundingSphere = maxLength / 2.0f;
	//m_fBoundingSphere = maxLength;
	//// modify? 12.0f -> 48.0f?
	//m_vRotationInertia.x = (GetMass() * (m_fHeight * m_fHeight + m_fDepth  * m_fDepth)) / 12.0f;
	//m_vRotationInertia.y = (GetMass() * (m_fWidth  * m_fWidth  + m_fDepth  * m_fDepth)) / 12.0f;
	//m_vRotationInertia.z = (GetMass() * (m_fWidth  * m_fWidth  + m_fHeight * m_fHeight)) / 12.0f;
	////SetMass(m_fWidth * m_fHeight * m_fDepth);
	////m_vRotationInertia.x = 0.3f * (GetMass() * (m_fHeight + m_fDepth));
	////m_vRotationInertia.y = 0.3f * (GetMass() * (m_fWidth  + m_fDepth));
	////m_vRotationInertia.z = 0.3f * (GetMass() * (m_fWidth  + m_fHeight));
}

void CPSBox::Setup(D3DXVECTOR3 center)
{
	//Setup();
	//m_vPosition = center;
	//D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CPSBox::Setup(const ST_MapData & mapData)
{
	//m_strObjName = mapData.strObjName;

	//m_strFolder = mapData.strFolderPath;
	//m_strXFile = mapData.strXFilePath;
	//m_strTxtFile = mapData.strTxtPath;

	//m_ObjectType = mapData.objType;

	//D3DXVECTOR3 vScale, vRotate;
	//vScale = mapData.vScale;
	//vRotate = mapData.vRotate;
	//m_vPosition = mapData.vTranslate;

	//m_Color = mapData.dxColor;
	//// color change
	//this->ChangeObjectColor();

	//m_fWidth = vScale.x;
	//m_fHeight = vScale.y;
	//m_fDepth = vScale.z;
	//
	//Setup();

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
}

void CPSBox::Update(float duration)
{
	//D3DXVECTOR3 linearforce;
	//if (m_isForceApplied)
	//{
	//	if (!hasFiniteMass()) return;
	//	linearforce = m_vForceVector * GetMass();
	//	m_isForceApplied = false;
	//}
	//else
	//	linearforce = D3DXVECTOR3(0, 0, 0);

	//if (m_finverseMass <= 0.0f) return;
	//assert(duration > 0.0f);

	//m_vLinearAcceleration = linearforce * m_finverseMass;
	//m_vLinearVelocity += (m_vLinearAcceleration * duration);
	//m_vLinearVelocity *= powf(m_fDamping, duration);
	//m_vLinearVelocity *= m_fLinearDrag;
	//if (CloseToZero(m_vLinearVelocity.x) && CloseToZero(m_vLinearVelocity.y) && CloseToZero(m_vLinearVelocity.z))
	//{
	//	m_vLinearVelocity.x = m_vLinearVelocity.y = m_vLinearVelocity.z = 0.0f;
	//}
	//else
	//	m_vPosition += (m_vLinearVelocity * duration);
	//D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CPSBox::Update3D(float duration)
{
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
////	m_vLinearAcceleration = (linearforce) * m_finverseMass;
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
//	m_vTorque = angularforce * 10000000.0f;
//
//	m_vAngularAcceleration.x = m_vTorque.x / m_vRotationInertia.x;
//	m_vAngularAcceleration.y = m_vTorque.y / m_vRotationInertia.y;
//	m_vAngularAcceleration.z = m_vTorque.z / m_vRotationInertia.z;
//
//	m_vAngularVelocity += m_vAngularAcceleration * duration;
//	m_vAngularVelocity *= powf(m_fDamping, duration);
//	// tmp Test... Need to AngularDrag
//	m_vAngularVelocity *= m_fLinearDrag;
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
}

void CPSBox::Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
{
	//D3DXVECTOR3* pVertices;

	//m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	//D3DXVECTOR3 m_vMin, m_vMax;
	//D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	//// later.. rotation add
	//m_vMin.x += m_matWorld._41;			m_vMax.x += m_matWorld._41;
	//m_vMin.y += m_matWorld._42;			m_vMax.y += m_matWorld._42;
	//m_vMin.z += m_matWorld._43;			m_vMax.z += m_matWorld._43;

	//if (D3DXBoxBoundProbe(&m_vMin, &m_vMax, &ray.GetOrigin(), &ray.GetDirection()) == true)
	//{
	//	m_isPicked = true;
	//	m_outLineColor = playerColor;
	//}
	//else
	//{
	//	m_isPicked = false;
	//}
	//vecVPos.push_back(m_vPosition);
	//vecIsPick.push_back(m_isPicked);
	//m_pMesh->UnlockVertexBuffer();
}

void CPSBox::Render()
{
	//m_stMtl.Ambient = m_Color;
	//m_stMtl.Diffuse = m_Color;
	//m_stMtl.Specular = m_Color;

	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//g_pD3DDevice->SetTexture(0, 0);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//g_pD3DDevice->SetMaterial(&m_stMtl);

	//if (m_isPicked && m_pShader)
	//{
	//	OutlineRender();
	//}
	//else
	//{
	//	m_pMesh->DrawSubset(0);
	//}
}

void CPSBox::SetPickState(bool set)
{
//	m_isPicked = set;
}

string CPSBox::GetName()
{
	return m_strName;
}

void CPSBox::ReceiveEvent(ST_EVENT eventMsg)
{
	CObject::ReceiveEvent(eventMsg);
}

void CPSBox::SetPusingForce(D3DXVECTOR3 forcedirection)
{
	////D3DXVec3Normalize(&m_vForceVector, &forcedirection);
	////m_vForceVector *= 100.0f;
	////SetForceApplied(true);

	//D3DXVECTOR3 forcePosition = forcedirection * m_fBoundingSphere;
	//m_vForceLocation = forcePosition;
	//m_vForceVector = forcedirection * 100.0f;
	//SetForceApplied(true);
}

void CPSBox::AddForce(const D3DXVECTOR3& force)
{
	//m_vForceAccum += force;
}

void CPSBox::ClearAccumulator()
{
	//m_vForceAccum.x = m_vForceAccum.y = m_vForceAccum.z = 0.0f;
}

void CPSBox::Integrate(float duration)
{
	///// physics edting
	//if (m_finverseMass <= 0.0f) return;
	//assert(duration > 0.0f);

	//D3DXVECTOR3 resultingAcc = m_vLinearAcceleration;
	//resultingAcc += (m_vForceAccum * m_finverseMass);
	//m_vLinearVelocity += (resultingAcc * duration);
	//m_vLinearVelocity *= powf(m_fDamping, duration);
	//m_vPosition += (m_vLinearVelocity * duration);

	//ClearAccumulator();
}

void CPSBox::RunPhysics(float duration)
{
	///// physics edting
	//if (!hasFiniteMass()) return;
	//AddForce(m_vForceVector * GetMass());
	////AddForce(m_vForceDirection);
	//Integrate(duration);
}

void CPSBox::Update(float duration, CHeight* pMap)
{
	/// physics edting
	//RunPhysics(duration);
	//Integrate(duration);
	//if (pMap)
	//{
	//	pMap->GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//}
	//D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//ClearAccumulator();
}

bool CPSBox::hasIntersected(CObject* otherobject)
{
	return false;
	//if (this == otherobject)
	//	return false;

	//D3DXVECTOR3 direction = this->GetPosition() - otherobject->GetPosition();
	//float distanceSq = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;

	//if (((this->GetBoundingSphere() + otherobject->GetBoundingSphere()) * (this->GetBoundingSphere() + otherobject->GetBoundingSphere())) < distanceSq)
	//	return false;
	//else
	//	return true;
}

void CPSBox::CollisionOtherObject(CObject* otherobject)
{
	//// declare variable, for performance I set them as static
	//static D3DXVECTOR3 direction;
	//static D3DXVECTOR3 warpVector;
	//static const float fix = 1.1f;
	//static float distance;
	//static float overlapInterval;

	////static D3DXVECTOR3 totalVelocity;
	////static D3DXVECTOR3 normalizedDirection;
	////static D3DXVECTOR3 ballVelocity;
	////static D3DXVECTOR3 thisVelocity;
	//// 2 dimension -> 3 dimension later editing...
	////if (hasIntersected(otherobject))
	////{
	////	direction = this->GetPosition() - otherobject->GetPosition();
	////	// 2 dimension -> 3 dimension later editing...
	////	distance = sqrt(direction.x * direction.x + direction.z * direction.z);
	////	overlapInterval = 2 * otherobject->GetRadius() - distance;
	////	warpVector = fix * direction * (overlapInterval / (2 * otherobject->GetRadius() - overlapInterval));
	////	// implementation of collision
	////	if (((otherobject->GetVelocity().x * otherobject->GetVelocity().x) + (otherobject->GetVelocity().z * otherobject->GetVelocity().z)) >= ((this->GetVelocity().x * this->GetVelocity().x) + (this->GetVelocity().z * this->GetVelocity().z)))
	////	{
	////		otherobject->CollisionOtherObject(this);
	////		return;
	////	}
	////	else
	////	{
	////		// 2 dimension -> 3 dimension later editing...
	////		D3DXVECTOR3 p;
	////		p.x = this->GetPosition().x + warpVector.x;
	////		p.y = this->GetPosition().y;
	////		p.z = this->GetPosition().z + warpVector.z;
	////		this->SetPosition(p);
	////		D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	////	}
	////	// 2 dimension -> 3 dimension later editing...
	////	D3DXVECTOR3 v;
	////	v.x = this->GetVelocity().x + otherobject->GetVelocity().x;
	////	v.y = 0;
	////	v.z = this->GetVelocity().z + otherobject->GetVelocity().z;
	////	totalVelocity = v;
	////	normalizedDirection = (-1) * direction / distance;
	////	ballVelocity = normalizedDirection * (normalizedDirection.x * totalVelocity.x + normalizedDirection.z * totalVelocity.z);
	////	thisVelocity = -ballVelocity + totalVelocity;
	////	v.x = thisVelocity.x;
	////	v.z = thisVelocity.z;
	////	this->SetVelocity(v);
	////	v.x = ballVelocity.x;
	////	v.z = ballVelocity.z;
	////	otherobject->SetVelocity(v);
	////}

	//// mass applying
	//if (hasIntersected(otherobject))
	//{
	//	direction = this->GetPosition() - otherobject->GetPosition();
	//	// 2 dimension -> 3 dimension later editing...
	//	distance = sqrt(direction.x * direction.x + direction.z * direction.z);
	//	overlapInterval = 2 * otherobject->GetBoundingSphere() - distance;
	//	warpVector = fix * direction * (overlapInterval / (2 * otherobject->GetBoundingSphere() - overlapInterval));

	//	// implementation of collision
	//	if (((otherobject->GetLinearVelocity().x * otherobject->GetLinearVelocity().x) + (otherobject->GetLinearVelocity().z * otherobject->GetLinearVelocity().z)) >= ((this->GetLinearVelocity().x * this->GetLinearVelocity().x) + (this->GetLinearVelocity().z * this->GetLinearVelocity().z)))
	//	{
	//		otherobject->CollisionOtherObject(this);
	//		return;
	//	}
	//	else
	//	{
	//		// 2 dimension -> 3 dimension later editing...
	//		D3DXVECTOR3 p;
	//		p.x = this->GetPosition().x + warpVector.x;
	//		p.y = this->GetPosition().y;
	//		p.z = this->GetPosition().z + warpVector.z;
	//		this->SetPosition(p);
	//		D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//	}

	//	// 2 dimension -> 3 dimension later editing...
	//	float v1, v2;
	//	D3DXVECTOR3 massdirection;
	//	massdirection = this->GetPosition() - otherobject->GetPosition();
	//	D3DXVec3Normalize(&massdirection, &massdirection);
	//	v1 = D3DXVec3Dot(&this->GetLinearVelocity(), &massdirection);
	//	v2 = D3DXVec3Dot(&otherobject->GetLinearVelocity(), &massdirection);
	//	/// perfect elastic collision
	//	//float elasticity = 1.0f;
	//	float elasticity = (this->GetElasticity() + otherobject->GetElasticity()) / 2;
	//	float finalv1, finalv2;
	//	finalv1 = (((this->GetMass() - (elasticity * otherobject->GetMass()))*v1) + ((1 + elasticity)*otherobject->GetMass()*v2)) 
	//				/ (this->GetMass() + otherobject->GetMass());
	//	finalv2 = (((otherobject->GetMass() - (elasticity * this->GetMass()))*v2) + ((1 + elasticity)*this->GetMass()*v1))
	//		/ (this->GetMass() + otherobject->GetMass());

	//	D3DXVECTOR3 collisionV1, collisionV2;
	//	collisionV1 = this->GetLinearVelocity() + (finalv1 - v1) * massdirection;
	//	collisionV2 = otherobject->GetLinearVelocity() + (finalv2 - v2) * massdirection;

	//	this->SetLinearVelocity(collisionV1);
	//	otherobject->SetLinearVelocity(collisionV2);
	//}
}