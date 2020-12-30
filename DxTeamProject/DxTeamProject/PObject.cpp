#include "stdafx.h"
#include "PObject.h"

PObject::PObject()
	: m_pShader(NULL)
	, m_isClicked(false)
	, m_isPicked(false)
	, m_fBoundingSphere(0.5f)
	, m_finverseMass(10.0f)
	, m_fDamping(0.999f)
	, m_vPosition(0, 0, 0)
	, m_vVelocity(0, 0, 0)
	, m_vAcceleration(0, 0, 0)
	, m_fElasticity(1.0f)
	, m_isForceApplied(false)
	, m_fLinearDrag(0.995f)
	, m_vForceVector(0, 0, 0)
	, m_vForceLocation(0, 0, 0)
{
	g_pObjectManager->AddObject(this);
	m_Color = GRAY;
	m_outLineColor = GRAY;
	LoadAssets();
}

PObject::~PObject()
{
}

void PObject::Update(float duration)
{
	D3DXVECTOR3 linearforce;
	//D3DXVECTOR3 linearforce, angularforce;
	if (m_isForceApplied)
	{
		if (!hasFiniteMass()) return;
		linearforce = m_vForceVector * GetInverseMass();
		//D3DXVec3Cross(&angularforce, &m_vForceLocation, &m_vForceVector);
		m_isForceApplied = false;
	}
	else
	{
		linearforce = D3DXVECTOR3(0, 0, 0);
		//angularforce = D3DXVECTOR3(0, 0, 0);
	}
	
	if (m_finverseMass <= 0.0f) return;
	assert(duration > 0.0f);
	
	m_vAcceleration = (linearforce + GRAVITY) * m_finverseMass;
	//m_vAcceleration = (linearforce) * m_finverseMass;
	m_vVelocity += (m_vAcceleration * duration);
	m_vVelocity *= powf(m_fDamping, duration);
	m_vVelocity *= m_fLinearDrag;
	if (CloseToZero(m_vVelocity.x) && CloseToZero(m_vVelocity.y) && CloseToZero(m_vVelocity.z))
	{
		m_vVelocity.x = m_vVelocity.y = m_vVelocity.z = 0.0f;
	}
	else
	{
		m_vPosition += (m_vVelocity * duration);
	}
	m_vTranslation = m_vPosition;
	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = matS * matR * matT;
}

void PObject::SetPusingForce(D3DXVECTOR3 forcedirection)
{
	m_vForceVector = forcedirection * 2000;
	SetForceApplied(true);
}

void PObject::UpdateLand(float duration)
{
	float distance = GetPosition().y - GetBoundingSphere();
	if (CloseToZero(distance) || distance < 0.0f)
	{
		m_vPosition.y += -distance;
		D3DXVECTOR3 tmp = m_vVelocity;
		tmp.y = -tmp.y * m_fElasticity;
		m_vVelocity = tmp;
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
		OutlineRender();
	else
		m_pMesh->DrawSubset(0);
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
		m_pShader->SetVector("gWorldLightPos", &D3DXVECTOR4(D3DXVECTOR3(0.0f, 100.0f, 0.0f), 1.0f));
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
	if (m_isPicked != true)
		return;

	if (eventMsg.eventType == EventType::eColorChangeEvent)
	{
		ST_EVENT msg;
		msg.eventType = EventType::eChangedColorEvent;

		D3DXCOLOR color = *(D3DXCOLOR*)eventMsg.ptrMessage;
		msg.ptrMessage = &color;
		g_pEventManager->CheckEvent(msg);
	}
	else if (eventMsg.eventType == EventType::eColorEffect)
	{
		// >> To do 용 이펙트 발사 이벤트 후 색상 변경 처리
		// m_Color = *(D3DXCOLOR*)eventMsg.ptrMessage;
		m_Color = m_outLineColor;
		m_outLineColor = *(D3DXCOLOR*)eventMsg.ptrMessage;
		m_isClicked = true;
	
		this->ChangeObjectColor();
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
		SetMass(3);
		SetElasticity(1.0f);
		SetDrag(0.995f);
		break;
	case Color::White:
		SetMass(0.5f);
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

/// Delete Later...
//void PObject::CollisionOtherObject(PObject * otherobject)
//{
//	static D3DXVECTOR3 direction;
//	static D3DXVECTOR3 warpVector;
//	static const float fix = 1.1f;
//	static float distance;
//	static float overlapInterval;
//
//	if (hasIntersected(otherobject))
//	{
//		direction = this->GetPosition() - otherobject->GetPosition();
//		// 2 dimension -> 3 dimension later editing...
//		distance = sqrt(direction.x * direction.x + direction.z * direction.z);
//		overlapInterval = 2 * otherobject->GetBoundingSphere() - distance;
//		warpVector = fix * direction * (overlapInterval / (2 * otherobject->GetBoundingSphere() - overlapInterval));
//
//		// implementation of collision
//		if (((otherobject->GetLinearVelocity().x * otherobject->GetLinearVelocity().x) + (otherobject->GetLinearVelocity().z * otherobject->GetLinearVelocity().z)) >= ((this->GetLinearVelocity().x * this->GetLinearVelocity().x) + (this->GetLinearVelocity().z * this->GetLinearVelocity().z)))
//		{
//			otherobject->CollisionOtherObject(this);
//			return;
//		}
//		else
//		{
//			// 2 dimension -> 3 dimension later editing...
//			D3DXVECTOR3 p;
//			p.x = this->GetPosition().x + warpVector.x;
//			p.y = this->GetPosition().y;
//			p.z = this->GetPosition().z + warpVector.z;
//			this->SetPosition(p);
//			D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
//		}
//
//		// 2 dimension -> 3 dimension later editing...
//		float v1, v2;
//		D3DXVECTOR3 massdirection;
//		massdirection = this->GetPosition() - otherobject->GetPosition();
//		D3DXVec3Normalize(&massdirection, &massdirection);
//		v1 = D3DXVec3Dot(&this->GetLinearVelocity(), &massdirection);
//		v2 = D3DXVec3Dot(&otherobject->GetLinearVelocity(), &massdirection);
//		/// perfect elastic collision
//		//float elasticity = 1.0f;
//		float elasticity = (this->GetElasticity() + otherobject->GetElasticity()) / 2;
//		float finalv1, finalv2;
//		finalv1 = (((this->GetMass() - (elasticity * otherobject->GetMass()))*v1) + ((1 + elasticity)*otherobject->GetMass()*v2))
//			/ (this->GetMass() + otherobject->GetMass());
//		finalv2 = (((otherobject->GetMass() - (elasticity * this->GetMass()))*v2) + ((1 + elasticity)*this->GetMass()*v1))
//			/ (this->GetMass() + otherobject->GetMass());
//
//		D3DXVECTOR3 collisionV1, collisionV2;
//		collisionV1 = this->GetLinearVelocity() + (finalv1 - v1) * massdirection;
//		collisionV2 = otherobject->GetLinearVelocity() + (finalv2 - v2) * massdirection;
//
//		this->SetLinearVelocity(collisionV1);
//		otherobject->SetLinearVelocity(collisionV2);
//	}
//}
//void PObject::Collision3D(PObject * otherobject)
//{
//static D3DXVECTOR3 direction;
//static D3DXVECTOR3 warpVector;
//static const float fix = 1.1f;
//static float distance;
//static float overlapInterval;
//if (hasIntersected(otherobject))
//{
//	direction = this->GetPosition() - otherobject->GetPosition();
//	distance = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
//	overlapInterval = 2 * otherobject->GetBoundingSphere() - distance;
//	warpVector = fix * direction * (overlapInterval / (2 * otherobject->GetBoundingSphere() - overlapInterval));
//	if (D3DXVec3LengthSq(&otherobject->GetVelocity()) >= D3DXVec3LengthSq(&this->GetVelocity()))
//	{
//		otherobject->Collision3D(this);
//		return;
//	}
//	else
//	{
//		D3DXVECTOR3 p;
//		p = this->GetPosition() + warpVector;
//		this->SetPosition(p);
//		D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
//	}
//	float v1, v2;
//	D3DXVec3Normalize(&direction, &direction);
//	v1 = D3DXVec3Dot(&this->GetVelocity(), &direction);
//	v2 = D3DXVec3Dot(&otherobject->GetVelocity(), &direction);
//	float elasticity = (this->GetElasticity() + otherobject->GetElasticity()) / 2;
//	float finalv1, finalv2;
//	finalv1 = (((this->GetMass() - (elasticity * otherobject->GetMass()))*v1) + ((1 + elasticity)*otherobject->GetMass()*v2))
//		/ (this->GetMass() + otherobject->GetMass());
//	finalv2 = (((otherobject->GetMass() - (elasticity * this->GetMass()))*v2) + ((1 + elasticity)*this->GetMass()*v1))
//		/ (this->GetMass() + otherobject->GetMass());
//	D3DXVECTOR3 collisionV1, collisionV2;
//	collisionV1 = this->GetVelocity() + (finalv1 - v1) * direction;
//	collisionV2 = otherobject->GetVelocity() + (finalv2 - v2) * direction;
//	this->SetVelocity(collisionV1);
//	otherobject->SetVelocity(collisionV2);
//}
//}