#include "stdafx.h"
#include "Object.h"
#include "Ray.h"

int CObject::m_nRefCount = 0;

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
		// >> 외곽선
		D3DXMATRIXA16 matView, matProj, matViewPro, matViewInvTrans;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

		matViewPro = setMatWorld * matView * matProj;
		m_pShader->SetMatrix("matViewProjection", &matViewPro);
		m_pShader->SetFloat("OutlineWidth", 0.1f);
		// << 외곽선

		// >> 라이트 쉐이더
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
		// << 라이트 쉐이더
	}
}

CObject::CObject()
{
	CObject::m_nRefCount += 1;
	g_pObjectManager->AddObject(this);
	m_color = GRAY;
	m_pShader = NULL;
	LoadAssets();
	D3DXMatrixIdentity(&m_matWorld);
}

CObject::~CObject()
{
	SafeRelease(m_pShader);
}

void CObject::Release()
{
	g_pObjectManager->RemoveObject(this);
	CObject::m_nRefCount -= 1;
}

void CObject::ReceiveEvent(ST_EVENT eventMsg)
{
	if (eventMsg.eventType == EventType::eColorChangeEvent)
	{
		if (m_isPicked == true)
		{
			m_color = *(D3DXCOLOR*)eventMsg.ptrMessage;
			m_outLineColor = *(D3DXCOLOR*)eventMsg.ptrMessage;
			m_isClicked = true;

			ST_EVENT msg;
			msg.eventType = EventType::eChangedColorEvent;
			msg.ptrMessage = &m_color;
			g_pEventManager->CheckEvent(msg);
		}
	}
	else
		m_isClicked = false;
}
