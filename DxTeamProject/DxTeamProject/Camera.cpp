#include "stdafx.h"
#include "Camera.h"

CCamera::CCamera() :
	m_vEye(0,0,-13),
	m_vLookAt(0,0,0),
	m_vUp(0,1,0),
	m_pvTarget(NULL),
	m_fCameraDistance(13.0f),
	m_isLBtnDown(false),
	m_vCamRotAngle(0,0,0)
{
	m_preMousePos = { 0,0 };
	m_strName = "Camera";
}

CCamera::~CCamera()
{
}

void CCamera::Setup(D3DXVECTOR3* pvTarget)
{
	m_pvTarget = pvTarget;
}

void CCamera::Update()
{
	float move = 2.0f;

	D3DXMATRIXA16	matT;
	D3DXMatrixTranslation(&matT, 0, move, 0);

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);

	matR = matRX * matRY * matT;

	m_vEye = D3DXVECTOR3(0, 0, -m_fCameraDistance);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	if (m_pvTarget)
	{
		m_vLookAt = *m_pvTarget + D3DXVECTOR3(0, move, 0);
		m_vEye += *m_pvTarget;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

D3DXVECTOR3 CCamera::GetCameraDirection()
{
	D3DXVECTOR3 direction;
	direction = m_vLookAt - m_vEye;
	D3DXVec3Normalize(&direction, &direction);
	return direction;
}

void CCamera::ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_preMousePos.x = LOWORD(lParam);
		m_preMousePos.y = HIWORD(lParam);
		m_isLBtnDown = true;
	break;

	case WM_LBUTTONUP:
		m_isLBtnDown = false;
		break;

	case WM_MOUSEMOVE:
	{
		if (g_gameManager->GetUImode())
		{
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);
			m_preMousePos = ptCurMouse;
			return;
		}
		//if (m_isLBtnDown)
		//{
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);

			float fDeltaX = (float)ptCurMouse.x - m_preMousePos.x;
			float fDeltaY = (float)ptCurMouse.y - m_preMousePos.y;

			m_vCamRotAngle.y += (fDeltaX / 150.0f);
			m_vCamRotAngle.x += (fDeltaY / 150.0f);

			if (m_vCamRotAngle.x < D3DX_PI / 12.0f + 0.0001f)
				m_vCamRotAngle.x = D3DX_PI / 12.0f;

			if (m_vCamRotAngle.x > D3DX_PI / 2.0f - 0.0001f)
				m_vCamRotAngle.x = D3DX_PI / 2.0f - 0.0001f;

			m_preMousePos = ptCurMouse;
		//}	// : if
	}
		break;

	case WM_MOUSEWHEEL:
	{
		//m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);

		//if (m_fCameraDistance < 5.0 + 0.0001f)
		//	m_fCameraDistance = 5.0f;
	}
		break;
	default:
		break;
	}
}

string CCamera::GetName()
{
	return m_strName;
}