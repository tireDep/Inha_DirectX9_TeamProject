#include "stdafx.h"
#include "PObject.h"

PObject::PObject()
	: m_pShader(NULL)
	, m_isClicked(false)
	, m_isPicked(false)
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

void PObject::Render()
{
	m_stMtl.Ambient = m_Color;
	m_stMtl.Diffuse = m_Color;
	m_stMtl.Specular = m_Color;

	D3DXMatrixTranslation(&m_matWorld, 5, 0, 5);
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
