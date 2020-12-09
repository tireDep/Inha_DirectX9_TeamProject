#include "stdafx.h"
#include "PObject.h"
#include "PSOBB.h"

PObject::PObject()
	: m_pShader(NULL)
	, m_isClicked(false)
	, m_isPicked(false)
	, m_fBoundingSphere(0.5f)
	, m_finverseMass(10.0f)
	, m_fDamping(0.999f)
	, m_vPosition(0, 0, 0)
	, m_vLinearVelocity(0, 0, 0)
	, m_vLinearAcceleration(0, 0, 0)
	, m_fElasticity(1.0f)
	, m_isForceApplied(false)
	, m_fLinearDrag(0.995f)
	, m_vForceVector(0, 0, 0)
	, m_vForceLocation(0, 0, 0)
	, m_vForceAccum(0, 0, 0)
	, m_vAngularVelocity(0, 0, 0)
	, m_vAngularAcceleration(0, 0, 0)
	, m_vInverseRotationInertia(1, 1, 1)
	, m_vTorque(0, 0, 0)
{
	g_pObjectManager->AddObject(this);
	m_Color = GRAY;
	m_outLineColor = GRAY;
	LoadAssets();
}

PObject::~PObject()
{
}

bool PObject::LoadAssets()
{
	g_pFileLoadManager->FileLoad_Shader("Resource/Shader", "outLine.fx", m_pShader);
	if (!m_pShader)
		return false;
	return true;
}

void PObject::SetShader(const D3DXMATRIXA16 & setMatWorld)
{
	if (m_pShader)
	{
		// >> : OutLine
		D3DXMATRIXA16 matView, matProj, matViewPro, matViewInvTrans;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

		matViewPro = setMatWorld * matView * matProj;
		m_pShader->SetMatrix("matViewProjection", &matViewPro);
		m_pShader->SetFloat("OutlineWidth", 0.1f);
		// << : OutLine

		// >> : Light Shader
		m_pShader->SetMatrix("gWorldMatrix", &setMatWorld);
		m_pShader->SetMatrix("gViewMatrix", &matView);
		m_pShader->SetMatrix("gProjectionMatrix", &matProj);

		// ===== 외부변수 받아오기?
		D3DXMATRIXA16 temp;
		D3DXMatrixIdentity(&temp);
		m_pShader->SetMatrix("gWorldCameraPos", &temp);

		m_pShader->SetVector("gLightColor", &D3DXVECTOR4(D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1.0f));
		m_pShader->SetVector("gWorldLightPos", &D3DXVECTOR4(D3DXVECTOR3(0, 10.0f, 0), 1));
		// ===== 외부변수 받아오기?
		// << : Light Shader
	}
}

void PObject::Update(CRay ray, D3DXCOLOR & playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
{
	D3DXVECTOR3* pVertices;

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	D3DXVECTOR3 m_vMin, m_vMax;
	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	// later.. rotation add
	m_vMin.x += m_matWorld._41;			m_vMax.x += m_matWorld._41;
	m_vMin.y += m_matWorld._42;			m_vMax.y += m_matWorld._42;
	m_vMin.z += m_matWorld._43;			m_vMax.z += m_matWorld._43;

	if (D3DXBoxBoundProbe(&m_vMin, &m_vMax, &ray.GetOrigin(), &ray.GetDirection()) == true)
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
	m_pMesh->UnlockVertexBuffer();
}

void PObject::ReceiveEvent(ST_EVENT eventMsg)
{
	if (eventMsg.eventType == EventType::eColorChangeEvent)
	{
		if (m_isPicked == true)
		{
			m_Color = *(D3DXCOLOR*)eventMsg.ptrMessage;
			m_outLineColor = *(D3DXCOLOR*)eventMsg.ptrMessage;
			m_isClicked = true;

			this->ChangeObjectColor();

			ST_EVENT msg;
			msg.eventType = EventType::eChangedColorEvent;
			msg.ptrMessage = &m_Color;
			g_pEventManager->CheckEvent(msg);
		}
	}
	else
		m_isClicked = false;
}

void PObject::OutlineRender()
{
	SetShader(m_matWorld);
	m_pShader->SetVector("OutlineColor", &D3DXVECTOR4(D3DXVECTOR3(m_outLineColor), 1));
	m_pShader->SetVector("SurfaceColor", &D3DXVECTOR4(D3DXVECTOR3(m_Color), 1));

	UINT numPasses = 0;
	m_pShader->Begin(&numPasses, NULL);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			m_pShader->BeginPass(i);
			if (i == 0)
				g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW); // 외곽선
			else
				g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// 내부
			m_pMesh->DrawSubset(0);
			m_pShader->EndPass();
		}
	}
	m_pShader->End();
}

void PObject::SetPickState(bool PickState)
{
	m_isPicked = PickState;
}

void PObject::ChangeObjectColor()
{
	if (m_Color == BLACK)
		m_tmpColor = Color::Black;
	else if (m_Color == WHITE)
		m_tmpColor = Color::White;
	else if (m_Color == RED)
		m_tmpColor = Color::Red;
	else if (m_Color == BLUE)
		m_tmpColor = Color::Blue;
	else if (m_Color == YELLOW)
		m_tmpColor = Color::Yellow;
	else if (m_Color == GREEN)
		m_tmpColor = Color::Green;
	else
		m_tmpColor = Color::NONE;
	switch (m_tmpColor)
	{
	case Color::Black:
		SetMass(100);
		SetElasticity(1.0f);
		SetDrag(0.995f);
		break;
	case Color::White:
		SetMass(0.1f);
		SetElasticity(1.0f);
		SetDrag(0.995f);
		break;
	case Color::Red:
		SetMass(1.0f);
		SetElasticity(1.0f);
		SetDrag(0.995f);
		break;
	case Color::Blue:
		SetMass(1.0f);
		SetElasticity(1.0f);
		SetDrag(0.995f);
		break;
	case Color::Yellow:
		SetMass(1.0f);
		SetElasticity(1.0f);
		SetDrag(0.9999f);
		break;
	case Color::Green:
		SetMass(1.0f);
		SetElasticity(5.0f);
		SetDrag(0.995f);
		break;
	default:
		SetMass(1.0f);
		SetElasticity(1.0f);
		SetDrag(0.995f);
		break;
	}
}

void PObject::Update(float duration)
{
	D3DXVECTOR3 linearforce, angularforce;
	if (m_isForceApplied)
	{
		if (!hasFiniteMass()) return;
		linearforce = m_vForceVector * GetMass();
		D3DXVec3Cross(&angularforce, &m_vForceLocation, &m_vForceVector);
		m_isForceApplied = false;
	}
	else
	{
		linearforce = D3DXVECTOR3(0, 0, 0);
		angularforce = D3DXVECTOR3(0, 0, 0);
	}
	
	if (m_finverseMass <= 0.0f) return;
	assert(duration > 0.0f);
	
	m_vLinearAcceleration = (linearforce + GRAVITY) * m_finverseMass;
//	m_vLinearAcceleration = (linearforce) * m_finverseMass;
	m_vLinearVelocity += (m_vLinearAcceleration * duration);
	m_vLinearVelocity *= powf(m_fDamping, duration);
	m_vLinearVelocity *= m_fLinearDrag;
	if (CloseToZero(m_vLinearVelocity.x) && CloseToZero(m_vLinearVelocity.y) && CloseToZero(m_vLinearVelocity.z))
	{
		m_vLinearVelocity.x = m_vLinearVelocity.y = m_vLinearVelocity.z = 0.0f;
	}
	else
		m_vPosition += (m_vLinearVelocity * duration);
	
	D3DXMATRIXA16 totalTransaltion;
	D3DXMatrixTranslation(&totalTransaltion, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	
	// Need to modify
	//m_vTorque = angularforce * 10000000.0f;
	m_vTorque = angularforce;
	
	m_vAngularAcceleration.x = m_vTorque.x * m_vInverseRotationInertia.x;
	m_vAngularAcceleration.y = m_vTorque.y * m_vInverseRotationInertia.y;
	m_vAngularAcceleration.z = m_vTorque.z * m_vInverseRotationInertia.z;
	
	m_vAngularVelocity += m_vAngularAcceleration * duration;
	m_vAngularVelocity *= powf(m_fDamping, duration);
	// tmp Test... Need to AngularDrag
	m_vAngularVelocity *= 0.999f;
	if (CloseToZero(m_vAngularVelocity.x) && CloseToZero(m_vAngularVelocity.y) && CloseToZero(m_vAngularVelocity.z))
	{
		m_vAngularVelocity.x = m_vAngularVelocity.y = m_vAngularVelocity.z = 0.0f;
	}
	else
		m_vAngularVelocity += (m_vAngularVelocity * duration);
	
	m_stOrientation.setXAngle(m_stOrientation.getXAngle() + m_vAngularVelocity.x * duration);
	m_stOrientation.setYAngle(m_stOrientation.getYAngle() + m_vAngularVelocity.y * duration);
	m_stOrientation.setZAngle(m_stOrientation.getZAngle() + m_vAngularVelocity.z * duration);
	
	D3DXMATRIXA16 rotationX, rotationY, rotationZ, totalRotation;
	D3DXMatrixRotationX(&rotationX, m_stOrientation.getXAngle());
	D3DXMatrixRotationY(&rotationY, m_stOrientation.getYAngle());
	D3DXMatrixRotationZ(&rotationZ, m_stOrientation.getZAngle());
	D3DXMatrixMultiply(&totalRotation, &rotationX, &rotationY);
	D3DXMatrixMultiply(&totalRotation, &totalRotation, &rotationZ);
	
	D3DXMatrixMultiply(&m_matWorld, &totalRotation, &totalTransaltion);
}

void PObject::SetMass(const float mass)
{
	assert(mass != 0);
	m_finverseMass = ((float)1.0) / mass;
}

float PObject::GetMass() const
{
	if (m_finverseMass == 0) { return FLT_MAX; }
	else { return ((float)1.0) / m_finverseMass; }
}

bool PObject::hasFiniteMass() const
{
	return m_finverseMass >= 0.0f;
}

void PObject::SetOrientation(CTestAngleSet Orientation)
{
	m_stOrientation = Orientation;
}

CTestAngleSet PObject::GetOrientation()
{
	return m_stOrientation;
}

void PObject::SetPusingForce(D3DXVECTOR3 forcedirection)
{
	D3DXVECTOR3 forcePosition = forcedirection * m_fBoundingSphere;
	m_vForceLocation = forcePosition;
	m_vForceVector = forcedirection * 100.0f;
	SetForceApplied(true);
}

bool PObject::hasIntersected(PObject * otherobject)
{
	if (this == otherobject)
		return false;

	D3DXVECTOR3 direction = this->GetPosition() - otherobject->GetPosition();
	float distanceSq = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;

	if (((this->GetBoundingSphere() + otherobject->GetBoundingSphere()) * (this->GetBoundingSphere() + otherobject->GetBoundingSphere())) < distanceSq)
		return false;
	else
		return true;
}

void PObject::CollisionOtherObject(PObject * otherobject)
{
	static D3DXVECTOR3 direction;
	static D3DXVECTOR3 warpVector;
	static const float fix = 1.1f;
	static float distance;
	static float overlapInterval;

	if (hasIntersected(otherobject))
	{
		direction = this->GetPosition() - otherobject->GetPosition();
		// 2 dimension -> 3 dimension later editing...
		distance = sqrt(direction.x * direction.x + direction.z * direction.z);
		overlapInterval = 2 * otherobject->GetBoundingSphere() - distance;
		warpVector = fix * direction * (overlapInterval / (2 * otherobject->GetBoundingSphere() - overlapInterval));

		// implementation of collision
		if (((otherobject->GetLinearVelocity().x * otherobject->GetLinearVelocity().x) + (otherobject->GetLinearVelocity().z * otherobject->GetLinearVelocity().z)) >= ((this->GetLinearVelocity().x * this->GetLinearVelocity().x) + (this->GetLinearVelocity().z * this->GetLinearVelocity().z)))
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
		v1 = D3DXVec3Dot(&this->GetLinearVelocity(), &massdirection);
		v2 = D3DXVec3Dot(&otherobject->GetLinearVelocity(), &massdirection);
		/// perfect elastic collision
		//float elasticity = 1.0f;
		float elasticity = (this->GetElasticity() + otherobject->GetElasticity()) / 2;
		float finalv1, finalv2;
		finalv1 = (((this->GetMass() - (elasticity * otherobject->GetMass()))*v1) + ((1 + elasticity)*otherobject->GetMass()*v2))
			/ (this->GetMass() + otherobject->GetMass());
		finalv2 = (((otherobject->GetMass() - (elasticity * this->GetMass()))*v2) + ((1 + elasticity)*this->GetMass()*v1))
			/ (this->GetMass() + otherobject->GetMass());

		D3DXVECTOR3 collisionV1, collisionV2;
		collisionV1 = this->GetLinearVelocity() + (finalv1 - v1) * massdirection;
		collisionV2 = otherobject->GetLinearVelocity() + (finalv2 - v2) * massdirection;

		this->SetLinearVelocity(collisionV1);
		otherobject->SetLinearVelocity(collisionV2);
	}
}

void PObject::Collision3D(PObject * otherobject)
{
	static D3DXVECTOR3 direction;
	static D3DXVECTOR3 warpVector;
	static const float fix = 1.1f;
	static float distance;
	static float overlapInterval;

	if (hasIntersected(otherobject))
	{
		direction = this->GetPosition() - otherobject->GetPosition();
		distance = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
		overlapInterval = 2 * otherobject->GetBoundingSphere() - distance;
		warpVector = fix * direction * (overlapInterval / (2 * otherobject->GetBoundingSphere() - overlapInterval));

		if (D3DXVec3LengthSq(&otherobject->GetLinearVelocity()) >= D3DXVec3LengthSq(&this->GetLinearVelocity()))
		{
			otherobject->Collision3D(this);
			return;
		}
		else
		{
			D3DXVECTOR3 p;
			p = this->GetPosition() + warpVector;
			this->SetPosition(p);
			D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		}

		float v1, v2;
		D3DXVec3Normalize(&direction, &direction);
		v1 = D3DXVec3Dot(&this->GetLinearVelocity(), &direction);
		v2 = D3DXVec3Dot(&otherobject->GetLinearVelocity(), &direction);

		float elasticity = (this->GetElasticity() + otherobject->GetElasticity()) / 2;

		float finalv1, finalv2;
		finalv1 = (((this->GetMass() - (elasticity * otherobject->GetMass()))*v1) + ((1 + elasticity)*otherobject->GetMass()*v2))
			/ (this->GetMass() + otherobject->GetMass());
		finalv2 = (((otherobject->GetMass() - (elasticity * this->GetMass()))*v2) + ((1 + elasticity)*this->GetMass()*v1))
			/ (this->GetMass() + otherobject->GetMass());

		D3DXVECTOR3 collisionV1, collisionV2;
		collisionV1 = this->GetLinearVelocity() + (finalv1 - v1) * direction;
		collisionV2 = otherobject->GetLinearVelocity() + (finalv2 - v2) * direction;

		this->SetLinearVelocity(collisionV1);
		otherobject->SetLinearVelocity(collisionV2);
	}
}

void PObject::UpdateLand(float duration)
{
	float distance = GetPosition().y - GetBoundingSphere();
	if (CloseToZero(distance) || distance < 0.0f)
	{
		D3DXVECTOR3 tmp = m_vLinearVelocity;
		tmp.y = -tmp.y * m_fElasticity;
		m_vLinearVelocity = tmp;
	}
}

void PObject::Render()
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
