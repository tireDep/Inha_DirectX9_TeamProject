#pragma once
#include "IListener.h"

class CCamera : public IListener
{
private:
	enum class CamStatus { eNullPos, eLeftPos, eTopPos, eRightPos, eBottomPos };

	CamStatus m_camStatus;

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
	void Update_MouseMove();
	D3DXVECTOR3 GetCameraDirection();
	D3DXVECTOR3 GetCameraEye();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	void CheckRotRange();
	string GetName();

	void SetCameraDistance(float dist);
	float GetCameraAngle();
};