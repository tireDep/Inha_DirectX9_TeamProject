#include "stdafx.h"
#include "Object.h"
#include "Ray.h"

int CObject::m_nRefCount = 0;

CObject::CObject()
	: m_pMesh(NULL)
	, m_pShader(NULL)
	, m_isClicked(false)
	, m_isPicked(false)
	, m_fRadius(0.5f)
	, m_finverseMass(1.0f)
	, m_fDamping(0.999f)
	, m_vPosition(0, 0, 0)
	, m_vVelocity(0, 0, 0)
	//, m_tmpColor(Color::NONE)
{
	CObject::m_nRefCount += 1;
	g_pObjectManager->AddObject(this);
	D3DXMatrixIdentity(&m_matWorld);
	m_Color = GRAY;
	m_outLineColor = GRAY;
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	LoadAssets();
}

CObject::~CObject()
{
	SafeRelease(m_pShader);
	SafeRelease(m_pMesh);
}

bool CObject::LoadAssets()
{
	g_pFileLoadManager->FileLoad_Shader("Resource/Shader", "outLine.fx", m_pShader);
	if (!m_pShader)
		return false;

	return true;
}

void CObject::SetShader(const D3DXMATRIXA16& setMatWorld)
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

void CObject::Release()
{
	g_pObjectManager->RemoveObject(this);
	CObject::m_nRefCount -= 1;
}

void CObject::OutlineRender()
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

void CObject::ReceiveEvent(ST_EVENT eventMsg)
{
	if (eventMsg.eventType == EventType::eColorChangeEvent)
	{
		if (m_isPicked == true)
		{
			m_Color = *(D3DXCOLOR*)eventMsg.ptrMessage;
			m_outLineColor = *(D3DXCOLOR*)eventMsg.ptrMessage;
			m_isClicked = true;

			// tmp Color change
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
					break;
				case Color::White:
					SetMass(0.001f);
					break;
				case Color::Red:
					break;
				case Color::Blue:
					break;
				case Color::Yellow:
					break;
				case Color::Green:
					break;
				default:
					break;
			}
			ST_EVENT msg;
			msg.eventType = EventType::eChangedColorEvent;
			msg.ptrMessage = &m_Color;
			g_pEventManager->CheckEvent(msg);
		}
	}
	else
		m_isClicked = false;
}

bool CObject::hasIntersected(CObject * otherobject)
{
	return true;
}

void CObject::CollisionOtherObject(CObject * otherobject)
{
}