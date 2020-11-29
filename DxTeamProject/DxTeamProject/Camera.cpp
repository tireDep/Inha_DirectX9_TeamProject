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
	if (m_vCamRotAngle.x < 0.0001f)
	{	
		float rotation_x = -m_vCamRotAngle.x;
		D3DXMatrixRotationX(&matRX, 0);
		D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
		matR = matRX * matRY * matT;

		m_vEye = D3DXVECTOR3(0, 0, -m_fCameraDistance);
		D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

		if (m_pvTarget)
		{
			m_vLookAt = *m_pvTarget + D3DXVECTOR3(0, move, 0);
			m_vEye += *m_pvTarget;
		}

		m_vLookAt += D3DXVECTOR3(0, m_fCameraDistance*sinf(rotation_x), 0);
		m_vEye += D3DXVECTOR3(0, 0, m_fCameraDistance*cosf(rotation_x));
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

		g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	}
	else 
	{
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
}

D3DXVECTOR3 CCamera::GetCameraDirection()
{
	D3DXVECTOR3 direction;
	direction = m_vLookAt - m_vEye;
	D3DXVec3Normalize(&direction, &direction);
	return direction;
}

D3DXVECTOR3 CCamera::GetCameraEye()
{
	return m_vEye;
}

void CCamera::ReceiveEvent(ST_EVENT eventMsg)
{
	if (eventMsg.eventType == EventType::eInputEvent)
	{
		switch (eventMsg.message)
		{
		case WM_LBUTTONDOWN:
			m_preMousePos.x = LOWORD(eventMsg.lParam);
			m_preMousePos.y = HIWORD(eventMsg.lParam);
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
				ptCurMouse.x = LOWORD(eventMsg.lParam);
				ptCurMouse.y = HIWORD(eventMsg.lParam);
				m_preMousePos = ptCurMouse;
				return;
			}
				POINT ptCurMouse;
				ptCurMouse.x = LOWORD(eventMsg.lParam);
				ptCurMouse.y = HIWORD(eventMsg.lParam);

				float fDeltaX = (float)ptCurMouse.x - m_preMousePos.x;
				float fDeltaY = (float)ptCurMouse.y - m_preMousePos.y;

				/// 좌우 밖으로 계속 카메라 이동 처리 중
				RECT rc;
				GetClientRect(g_hWnd, &rc);
					if (ptCurMouse.x < rc.left + 1.0f)
					{
						cout << ptCurMouse.x << ' ' << ptCurMouse.y << endl;
						fDeltaX -= 15.0f;
					}
					else if (ptCurMouse.x > rc.right - 2.0f)
					{
						cout << ptCurMouse.x << ' ' << ptCurMouse.y << endl;
						fDeltaX += 15.0f;
					}
					else if (ptCurMouse.y < rc.top + 1.0f)
					{
						cout << ptCurMouse.x << ' ' << ptCurMouse.y << endl;
						fDeltaY += 15.0f;
					}
					else if (ptCurMouse.y > rc.bottom - 2.0f)
					{
						cout << ptCurMouse.x << ' ' << ptCurMouse.y << endl;
						fDeltaY -= 15.0f;
					}
					else
					{
					}
				
				m_vCamRotAngle.y += (fDeltaX / 150.0f);
				m_vCamRotAngle.x += (fDeltaY / 150.0f);

				if (m_vCamRotAngle.x < - D3DX_PI / 3.0f - 0.0001f)
					m_vCamRotAngle.x = -D3DX_PI / 3.0f;

				if (m_vCamRotAngle.x > D3DX_PI / 2.0f - 0.0001f)
					m_vCamRotAngle.x = D3DX_PI / 2.0f - 0.0001f;

				m_preMousePos = ptCurMouse;
		}
		break;
		// DEBUG Mode
#if _DEBUG
		case WM_MOUSEWHEEL:
		{
			m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(eventMsg.wParam) / 30.0f);
			if (m_fCameraDistance < 5.0 + 0.0001f)
				m_fCameraDistance = 5.0f;
		}
		break;
#endif
		// RELEASE Mode
		} // << : switch
	} // << : if
}

string CCamera::GetName()
{
	return m_strName;
}