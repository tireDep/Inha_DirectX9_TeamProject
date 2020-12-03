#pragma once
class CCamera
{
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3*	m_pvTarget;

	POINT			m_ptPrevMouse;
	bool			m_isLButtonDown;
	float			m_fCameraDistance;
	D3DXVECTOR3		m_vCamRotAngle;

	float m_fRotY;

	D3DXVECTOR3 m_vNowTarget;

public:
	CCamera();
	~CCamera();

	void Setup(D3DXVECTOR3* pvTarget);
	void Update();

	void SetCameraPos(D3DXVECTOR3 pvTarget);

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

