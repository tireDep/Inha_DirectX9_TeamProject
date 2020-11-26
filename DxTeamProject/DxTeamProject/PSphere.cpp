#include "stdafx.h"
#include "PSphere.h"

CPSphere::CPSphere()
	: m_vAcceleration(0, 0, 0)
	, m_vForceDirection(0, 0, 0)
	, m_vForceAccum(0, 0, 0)
{
	m_strName = string("Sphere") + to_string(m_nRefCount);
}

CPSphere::~CPSphere()
{
}

void CPSphere::Setup()
{
	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMesh, NULL);
}

void CPSphere::Setup(D3DXVECTOR3 center)
{
	Setup();
	m_vPosition = center;
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CPSphere::Update(float duration)
{
	D3DXVECTOR3 linearforce;
	if (m_isForceApplied)
	{
		if (!hasFiniteMass()) return;
		linearforce = m_vForceDirection * GetMass();
		m_isForceApplied = false;
	}
	else
		linearforce = D3DXVECTOR3(0, 0, 0);

	if (m_finverseMass <= 0.0f) return;
	assert(duration > 0.0f);

	m_vAcceleration = linearforce * m_finverseMass;
	m_vVelocity += (m_vAcceleration * duration);
	m_vVelocity *= powf(m_fDamping, duration);
	//m_vPosition += (m_vVelocity * duration);
	m_vVelocity *= m_fDrag;
	if (m_vVelocity.x > 0.001f || m_vVelocity.y > 0.001f || m_vVelocity.z > 0.001f)
	{
		m_vPosition += (m_vVelocity * duration);
	}
	else
	{
		m_vVelocity.x = m_vVelocity.y = m_vVelocity.z = 0.0f;
	}
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CPSphere::Update(float duration, CHeight* pMap)
{
	ClearAccumulator();
	RunPhysics(duration);
	Integrate(duration);
	if (pMap)
	{
		pMap->GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	}
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CPSphere::Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
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

void CPSphere::Render()
{
	m_stMtl.Ambient = m_Color;
	m_stMtl.Diffuse = m_Color;
	m_stMtl.Specular = m_Color;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMtl);

	if (m_isPicked && m_pShader)
	{
		OutlineRender();
	}
	else
	{
		m_pMesh->DrawSubset(0);
	}
}

void CPSphere::ClearAccumulator()
{
	m_vForceAccum.x = m_vForceAccum.y = m_vForceAccum.z = 0.0f;
}

void CPSphere::RunPhysics(float duration)
{
	if (!hasFiniteMass()) return;
	AddForce(m_vForceDirection * GetMass());
	Integrate(duration);
}

void CPSphere::AddForce(const D3DXVECTOR3& force)
{
	m_vForceAccum += force;
}

void CPSphere::Integrate(float duration)
{
	if (m_finverseMass <= 0.0f) return;
	assert(duration > 0.0f);

	m_vPosition += (m_vVelocity * duration);

	D3DXVECTOR3 resultingAcc = m_vAcceleration;
	resultingAcc += (m_vForceAccum * m_finverseMass);
	m_vVelocity += (resultingAcc * duration);
	m_vVelocity *= powf(m_fDamping, duration);

	ClearAccumulator();
}

void CPSphere::SetPickState(bool set)
{
	m_isPicked = set;
}

string CPSphere::GetName()
{
	return m_strName;
}

void CPSphere::ReceiveEvent(ST_EVENT eventMsg)
{
	CObject::ReceiveEvent(eventMsg);
}

void CPSphere::SetMass(const float mass)
{
	assert(mass != 0);
	m_finverseMass = ((float)1.0) / mass;
}

float CPSphere::GetMass() const
{
	if (m_finverseMass == 0) { return FLT_MAX; }
	else { return ((float)1.0) / m_finverseMass; }
}

bool CPSphere::hasFiniteMass() const
{
	return m_finverseMass >= 0.0f;
}

void CPSphere::SetPusingForce(D3DXVECTOR3 forcedirection)
{
	D3DXVec3Normalize(&m_vForceDirection, &forcedirection);
	m_vForceDirection *= 100.0f;
	SetForceApplied(true);
}

bool CPSphere::hasIntersected(CObject* otherobject)
{
	if (this == otherobject)
		return false;

	D3DXVECTOR3 direction = this->GetPosition() - otherobject->GetPosition();
	float distanceSq = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;

	if (((this->GetRadius() + otherobject->GetRadius()) * (this->GetRadius() + otherobject->GetRadius())) < distanceSq)
		return false;
	else
		return true;
}

void CPSphere::CollisionOtherObject(CObject* otherobject)
{
	// declare variable, for performance I set them as static
	static D3DXVECTOR3 direction;
	static D3DXVECTOR3 warpVector;
	static const float fix = 1.1f;
	static float distance;
	static float overlapInterval;

	//static D3DXVECTOR3 totalVelocity;
	//static D3DXVECTOR3 normalizedDirection;
	//static D3DXVECTOR3 ballVelocity;
	//static D3DXVECTOR3 thisVelocity;
	// 2 dimension -> 3 dimension later editing...
	//if (hasIntersected(otherobject))
	//{
	//	direction = this->GetPosition() - otherobject->GetPosition();
	//	// 2 dimension -> 3 dimension later editing...
	//	distance = sqrt(direction.x * direction.x + direction.z * direction.z);
	//	overlapInterval = 2 * otherobject->GetRadius() - distance;
	//	warpVector = fix * direction * (overlapInterval / (2 * otherobject->GetRadius() - overlapInterval));
	//	// implementation of collision
	//	if (((otherobject->GetVelocity().x * otherobject->GetVelocity().x) + (otherobject->GetVelocity().z * otherobject->GetVelocity().z)) >= ((this->GetVelocity().x * this->GetVelocity().x) + (this->GetVelocity().z * this->GetVelocity().z)))
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
	//	D3DXVECTOR3 v;
	//	v.x = this->GetVelocity().x + otherobject->GetVelocity().x;
	//	v.y = 0;
	//	v.z = this->GetVelocity().z + otherobject->GetVelocity().z;
	//	totalVelocity = v;
	//	normalizedDirection = (-1) * direction / distance;
	//	ballVelocity = normalizedDirection * (normalizedDirection.x * totalVelocity.x + normalizedDirection.z * totalVelocity.z);
	//	thisVelocity = -ballVelocity + totalVelocity;
	//	v.x = thisVelocity.x;
	//	v.z = thisVelocity.z;
	//	this->SetVelocity(v);
	//	v.x = ballVelocity.x;
	//	v.z = ballVelocity.z;
	//	otherobject->SetVelocity(v);
	//}

	// mass applying
	if (hasIntersected(otherobject))
	{
		direction = this->GetPosition() - otherobject->GetPosition();
		// 2 dimension -> 3 dimension later editing...
		distance = sqrt(direction.x * direction.x + direction.z * direction.z);
		overlapInterval = 2 * otherobject->GetRadius() - distance;
		warpVector = fix * direction * (overlapInterval / (2 * otherobject->GetRadius() - overlapInterval));

		// implementation of collision
		if (((otherobject->GetVelocity().x * otherobject->GetVelocity().x) + (otherobject->GetVelocity().z * otherobject->GetVelocity().z)) >= ((this->GetVelocity().x * this->GetVelocity().x) + (this->GetVelocity().z * this->GetVelocity().z)))
		{
			otherobject->CollisionOtherObject(this);
			return;
		}
		else
		{
			// 2 dimension -> 3 dimension later editing...
			D3DXVECTOR3 p;
			p.x = this->GetPosition().x + warpVector.x;
			p.y = this->GetPosition().y;
			p.z = this->GetPosition().z + warpVector.z;
			this->SetPosition(p);
			D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		}

		// 2 dimension -> 3 dimension later editing...
		float v1, v2;
		D3DXVECTOR3 massdirection;
		massdirection = this->GetPosition() - otherobject->GetPosition();
		D3DXVec3Normalize(&massdirection, &massdirection);
		v1 = D3DXVec3Dot(&this->GetVelocity(), &massdirection);
		v2 = D3DXVec3Dot(&otherobject->GetVelocity(), &massdirection);
		/// perfect elastic collision
		//float elasticity = 1.0f;
		float elasticity = (this->GetElasticity() + otherobject->GetElasticity()) / 2;
		float finalv1, finalv2;
		finalv1 = (((this->GetMass() - (elasticity * otherobject->GetMass()))*v1) + ((1 + elasticity)*otherobject->GetMass()*v2))
			/ (this->GetMass() + otherobject->GetMass());
		finalv2 = (((otherobject->GetMass() - (elasticity * this->GetMass()))*v2) + ((1 + elasticity)*this->GetMass()*v1))
			/ (this->GetMass() + otherobject->GetMass());

		D3DXVECTOR3 collisionV1, collisionV2;
		collisionV1 = this->GetVelocity() + (finalv1 - v1) * massdirection;
		collisionV2 = otherobject->GetVelocity() + (finalv2 - v2) * massdirection;

		this->SetVelocity(collisionV1);
		otherobject->SetVelocity(collisionV2);
	}
}