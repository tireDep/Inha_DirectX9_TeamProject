#include "stdafx.h"
#include "Object.h"
#include "Ray.h"

int CObject::m_nRefCount = 0;

CObject::CObject()
{
	CObject::m_nRefCount += 1;
	g_pObjectManager->AddObject(this);
	m_color = GRAY;
}

CObject::~CObject()
{
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
			// todo : 색상값 받아와야 함
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
