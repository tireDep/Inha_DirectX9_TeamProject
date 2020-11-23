#include "stdafx.h"
#include "PSphere.h"

CPSphere::CPSphere()
	: m_fRadius(0.5f)
	, m_finverseMass(10.0f)
	, m_fDamping(0.999f)
	, m_vPosition(0, 0, 0)
	, m_vVelocity(0, 0, 0)
	, m_vAcceleration(0, 0, 0)
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
	ClearAccumulator();
	RunPhysics(duration);
	Integrate(duration);
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CPSphere::Update(CRay ray, D3DXCOLOR & playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
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
	m_stMtl.Ambient  = m_Color;
	m_stMtl.Diffuse  = m_Color;
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
}

void CPSphere::AddForce(const D3DXVECTOR3 & force)
{
	m_vForceAccum += force;
}

void CPSphere::ClearAccumulator()
{
	m_vForceAccum.x = m_vForceAccum.y = m_vForceAccum.z = 0.0f;
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

void CPSphere::RunPhysics(float duration)
{
	if (!hasFiniteMass()) return;
	AddForce(m_vForceDirection * GetMass());
	Integrate(duration);
}

bool CPSphere::hasIntersected(CPSphere & othersphere)
{
	if (this == &othersphere)
		return false;

	D3DXVECTOR3 direction = this->GetPosition() - othersphere.GetPosition();
	float distance = D3DXVec3LengthSq(&direction);

	if (((this->GetRadius() + othersphere.GetRadius())*(this->GetRadius() + othersphere.GetRadius())) < distance)
		return false;
	else
		return true;
}

void CPSphere::Collisionsphere(CPSphere & othersphere)
{
	static D3DXVECTOR3 direction;
	static D3DXVECTOR3 warpVector;
	static D3DXVECTOR3 totalVelocity;
	static D3DXVECTOR3 normalizedDirection;
	static D3DXVECTOR3 ballVelocity;
	static D3DXVECTOR3 thisVelocity;
	static const float fix = 1.1f;
	static float distance;
	static float overlapInterval;

	if (hasIntersected(othersphere))
	{
		direction = this->GetPosition() - othersphere.GetPosition();
		distance = sqrt(direction.x * direction.x + direction.z * direction.z);
		overlapInterval = 2 * othersphere.GetRadius() - distance;
		warpVector = fix * direction *(overlapInterval / (2 * othersphere.GetRadius() - overlapInterval));

		if (((othersphere.m_vVelocity.x * othersphere.m_vVelocity.x) + (othersphere.m_vVelocity.z * othersphere.m_vVelocity.z)) >= ((this->m_vVelocity.x * this->m_vVelocity.x) + (this->m_vVelocity.z * this->m_vVelocity.z)))
		{
			othersphere.Collisionsphere(*this);
			return;
		}
		else
		{
			D3DXVECTOR3 p;
			p.x = m_vPosition.x + warpVector.x;
			p.y = m_vPosition.y;
			p.z = m_vPosition.z + warpVector.z;
			this->SetPosition(p);
			D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		}

		D3DXVECTOR3 v;
		v.x = this->GetVelocity().x + othersphere.GetVelocity().x;
		v.y = 0;
		v.z = this->GetVelocity().z + othersphere.GetVelocity().z;
		totalVelocity = v;
		normalizedDirection = (-1) * direction / distance;

		ballVelocity = normalizedDirection * (normalizedDirection.x * totalVelocity.x + normalizedDirection.z * totalVelocity.z);
		thisVelocity = -ballVelocity + totalVelocity;

		v.x = thisVelocity.x;
		v.z = thisVelocity.z;
		this->SetVelocity(v);
		v.x = ballVelocity.x;
		v.z = ballVelocity.z;
		othersphere.SetVelocity(v);

		//if (hasIntersected(othersphere))
		//	this->setCenter(this->GetPosition().x + 3 * warpVector.x, this->GetPosition().y, this->GetPosition().z + 3 * warpVector.z);
	}
}