#pragma once
class CCamera
{
public:
	CCamera();
	~CCamera();
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3*	m_pvTarget;

	POINT			m_prevMousePos;
	bool			m_isLBtDown;
	float			m_fCameraDistance;
	D3DXVECTOR3		m_vCamRotAngle;
public:
	void Setup();
	void Setup(D3DXVECTOR3* pvTarget);
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};