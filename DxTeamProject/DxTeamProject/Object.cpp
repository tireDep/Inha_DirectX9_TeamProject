#include "stdafx.h"
#include "Object.h"
#include "PSBox.h"
#include "PSphere.h"
#include "PSCylinder.h"
#include "Background.h"
#include "Ray.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"

int CObject::m_nRefCount = 0;

CObject::CObject()
	: m_pMesh(NULL)
	/// Color
	//, m_pShader(NULL)
	//, m_isClicked(false)
	//, m_isPicked(false)
	//, m_tmpColor(Color::NONE)
	/// Physics
	//, m_fBoundingSphere(0.5f)
	//, m_finverseMass(10.0f)
	//, m_fDamping(0.999f)
	//, m_vPosition(0, 0, 0)
	//, m_vLinearVelocity(0, 0, 0)
	//, m_vLinearAcceleration(0, 0, 0)
	//, m_fElasticity(1.0f)
	//, m_isForceApplied(false)
	//, m_fLinearDrag(0.995f)
	//, m_vForceVector(0, 0, 0)
	//, m_vForceLocation(0, 0, 0)
	//, m_vForceAccum(0, 0, 0)
	//, m_vAngularVelocity(0, 0, 0)
	//, m_vAngularAcceleration(0, 0, 0)
	//, m_vRotationInertia(0, 0, 0)
	//, m_vTorque(0, 0, 0)
{
	CObject::m_nRefCount += 1;
	g_pObjectManager->AddObject(this);
	D3DXMatrixIdentity(&m_matWorld);
	/// Color
	//m_Color = GRAY;
	//m_outLineColor = GRAY;
	//LoadAssets();
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
}

CObject::~CObject()
{
}

/// Color
//bool CObject::LoadAssets()
//{
//	g_pFileLoadManager->FileLoad_Shader("Resource/Shader", "outLine.fx", m_pShader);
//	if (!m_pShader)
//		return false;
//
//	return true;
//}
//void CObject::SetShader(const D3DXMATRIXA16& setMatWorld)
//{
//	if (m_pShader)
//	{
//		// >> : OutLine
//		D3DXMATRIXA16 matView, matProj, matViewPro, matViewInvTrans;
//		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
//		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
//
//		matViewPro = setMatWorld * matView * matProj;
//		m_pShader->SetMatrix("matViewProjection", &matViewPro);
//		m_pShader->SetFloat("OutlineWidth", 0.1f);
//		// << : OutLine
//
//		// >> : Light Shader
//		m_pShader->SetMatrix("gWorldMatrix", &setMatWorld);
//		m_pShader->SetMatrix("gViewMatrix", &matView);
//		m_pShader->SetMatrix("gProjectionMatrix", &matProj);
//
//		// ===== 외부변수 받아오기?
//		D3DXMATRIXA16 temp;
//		D3DXMatrixIdentity(&temp);
//		m_pShader->SetMatrix("gWorldCameraPos", &temp);
//
//		m_pShader->SetVector("gLightColor", &D3DXVECTOR4(D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1.0f));
//		m_pShader->SetVector("gWorldLightPos", &D3DXVECTOR4(D3DXVECTOR3(0, 10.0f, 0), 1));
//		// ===== 외부변수 받아오기?
//		// << : Light Shader
//	}
//}
//void CObject::ReceiveEvent(ST_EVENT eventMsg)
//{
//	if (eventMsg.eventType == EventType::eColorChangeEvent)
//	{
//		if (m_isPicked == true)
//		{
//			m_Color = *(D3DXCOLOR*)eventMsg.ptrMessage;
//			m_outLineColor = *(D3DXCOLOR*)eventMsg.ptrMessage;
//			m_isClicked = true;
//
//			this->ChangeObjectColor();
//
//			ST_EVENT msg;
//			msg.eventType = EventType::eChangedColorEvent;
//			msg.ptrMessage = &m_Color;
//			g_pEventManager->CheckEvent(msg);
//		}
//	}
//	else
//		m_isClicked = false;
//}
//void CObject::OutlineRender()
//{
//	SetShader(m_matWorld);
//	m_pShader->SetVector("OutlineColor", &D3DXVECTOR4(D3DXVECTOR3(m_outLineColor), 1));
//	m_pShader->SetVector("SurfaceColor", &D3DXVECTOR4(D3DXVECTOR3(m_Color), 1));
//
//	UINT numPasses = 0;
//	m_pShader->Begin(&numPasses, NULL);
//	{
//		for (UINT i = 0; i < numPasses; ++i)
//		{
//			m_pShader->BeginPass(i); 
//			if (i == 0)
//				g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW); // 외곽선
//			else
//				g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// 내부
//			m_pMesh->DrawSubset(0);
//			m_pShader->EndPass();
//		}
//	}
//	m_pShader->End();
//}
//void CObject::ChangeObjectColor()
//{
//	if (m_Color == BLACK)
//		m_tmpColor = Color::Black;
//	else if (m_Color == WHITE)
//		m_tmpColor = Color::White;
//	else if (m_Color == RED)
//		m_tmpColor = Color::Red;
//	else if (m_Color == BLUE)
//		m_tmpColor = Color::Blue;
//	else if (m_Color == YELLOW)
//		m_tmpColor = Color::Yellow;
//	else if (m_Color == GREEN)
//		m_tmpColor = Color::Green;
//	else
//		m_tmpColor = Color::NONE;
//	switch (m_tmpColor)
//	{
//	case Color::Black:
//		SetMass(100);
//		SetElasticity(1.0f);
//		SetDrag(0.995f);
//		break;
//	case Color::White:
//		SetMass(0.1f);
//		SetElasticity(1.0f);
//		SetDrag(0.995f);
//		break;
//	case Color::Red:
//		SetMass(1.0f);
//		SetElasticity(1.0f);
//		SetDrag(0.995f);
//		break;
//	case Color::Blue:
//		SetMass(1.0f);
//		SetElasticity(1.0f);
//		SetDrag(0.995f);
//		break;
//	case Color::Yellow:
//		SetMass(1.0f);
//		SetElasticity(1.0f);
//		SetDrag(0.9999f);
//		break;
//	case Color::Green:
//		SetMass(1.0f);
//		SetElasticity(5.0f);
//		SetDrag(0.995f);
//		break;
//	default:
//		SetMass(1.0f);
//		SetElasticity(1.0f);
//		SetDrag(0.995f);
//		break;
//	}
//}

void CObject::Release()
{
	g_pObjectManager->RemoveObject(this);
	CObject::m_nRefCount -= 1;
}

void CObject::CreateObject(const ST_MapData & mapData)
{
	switch (mapData.objType)
	{
	case eBox:
	{
		//CPSBox* box = new CPSBox;
		//box->Setup(mapData);
		CBox* box = new CBox;
		box->Setup(mapData);
	}
	break;

	case eSphere:
	{
		//CPSphere* sphere = new CPSphere;
		//sphere->Setup(mapData);
		CSphere* sphere = new CSphere;
		sphere->Setup(mapData);
	}
	break;

	case eCylinder:
	{
		//CPSCylinder* cylinder = new CPSCylinder;
		//cylinder->Setup(mapData);
		CCylinder* cylinder = new CCylinder;
		cylinder->Setup(mapData);
	}
	break;

	case eATree:
	case eSTree:
	case eWTree:
	{
		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	}
}

/// Physics
//void CObject::SetMass(const float mass)
//{
//	assert(mass != 0);
//	m_finverseMass = ((float)1.0) / mass;
//}
//float CObject::GetMass() const
//{
//	if (m_finverseMass == 0) { return FLT_MAX; }
//	else { return ((float)1.0) / m_finverseMass; }
//}
//
//bool CObject::hasFiniteMass() const
//{
//	return m_finverseMass >= 0.0f;
//}
//
//void CObject::SetOrientation(CTestAngleSet Orientation)
//{
//	m_stOrientation = Orientation;
//}
//
//CTestAngleSet CObject::GetOrientation()
//{
//	return m_stOrientation;
//}

bool CObject::GetAwake() const
{
	return m_isAwake;
}

void CObject::SetAwake(const bool awake)
{
	// 0.3 = sleepEpsilon
	if (awake) 
	{
		m_isAwake = true;
		m_fMotion = 0.3 * 2.0f;
	}
	else
	{
		m_isAwake = false;
		//m_vLinearVelocity.x = m_vLinearVelocity.y = m_vLinearVelocity.z = 0.0f;
		//m_vAngularVelocity.x = m_vAngularVelocity.y = m_vAngularVelocity.z = 0.0f;
	}
}