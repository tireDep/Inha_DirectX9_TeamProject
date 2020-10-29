#pragma once
class CCamera
{
private:
	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vLookAt;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3* m_pvTarget;

	POINT m_preMousPos;
	bool m_isLBtnDown;
	float m_fCameraDistance;
	D3DXVECTOR3 m_vCamRotAngle;

public:
	CCamera();
	~CCamera();

	void Setup(D3DXVECTOR3* pvTarget);
	void Update();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

