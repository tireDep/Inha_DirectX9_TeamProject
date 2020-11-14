#pragma once
#include "IListener.h"

class CCamera : public IListener
{
private:
	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vLookAt;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3* m_pvTarget;

	POINT m_preMousePos;
	bool m_isLBtnDown;
	float m_fCameraDistance;
	D3DXVECTOR3 m_vCamRotAngle;
public:
	CCamera();
	~CCamera();

	void Setup(D3DXVECTOR3* pvTarget);
	void Update();
	D3DXVECTOR3 GetCameraDirection();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName();
	
};