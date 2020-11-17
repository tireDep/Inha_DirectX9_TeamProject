#include "stdafx.h"
#include "Object.h"
#include "Ray.h"

int CObject::m_nRefCount = 0;

bool CObject::LoadAssets()
{
	m_pShader = LoadShader("Shader/outLine.fx");
	if (!m_pShader)
		return false;

	return true;
}

LPD3DXEFFECT CObject::LoadShader(const char * fileName)
{
	LPD3DXEFFECT ret = NULL;

	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFileA(g_pD3DDevice, fileName,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		// if (ack)
		// {
		// 	char* str = new char[size];
		// 	sprintf(str, (const char*)ack, size);
		// 	OutputDebugString(str);
		// 	delete[] str;
		// }
	}

	return ret;
}

void CObject::SetShader(const D3DXMATRIXA16& setMatWorld)
{
	// g_pD3DDevice->SetTransform(D3DTS_WORLD, &setMatWorld);

	//if (m_pShader)
	//{
	//	m_pShader->
	//	D3DXMATRIXA16 matView, matProj, matViewPro, matViewInvTrans;
	//	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	//	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	//	matViewPro = matView * matProj;
	//	m_pShader->SetMatrix("matViewProjection", &matViewPro);

	//	D3DXMatrixInverse(&matViewInvTrans, NULL, &matView);
	//	D3DXMatrixTranspose(&matViewInvTrans, &matViewInvTrans);
	//	m_pShader->SetMatrix("matViewInverseTranspose", &matViewInvTrans);

	//	m_pShader->SetMatrix("matProjection", &matProj);

	//	D3DXMATRIXA16 matWorldInverse;
	//	D3DXMatrixInverse(&matWorldInverse, NULL, &setMatWorld);
	//	m_pShader->SetMatrix("matWorldInverse", &matWorldInverse);

	//	D3DXMATRIXA16 matWorldViewInverse;
	//	D3DXMATRIXA16 matWorldView;
	//	matWorldView = setMatWorld * matView;
	//	D3DXMatrixInverse(&matWorldViewInverse, NULL, &matWorldView);
	//	m_pShader->SetMatrix("matWorldViewInverse", &matWorldViewInverse);
	//}
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
	if (eventMsg.eventType == EventType::eInputEvent && eventMsg.message == WM_LBUTTONDOWN)
	{
		if (m_isPicked == true)
		{
			m_isClicked = true;
		}
	}
	else
		m_isClicked = false;
}

void CObject::SetColor(D3DXCOLOR ObjectColor)
{
	m_color = ObjectColor;
}

D3DXCOLOR CObject::GetColor()
{
	return m_color;
}

bool CObject::GetisClicked()
{
	return m_isClicked;
}
