#pragma once
#include "IListener.h"

class CRay;
class CSkinnedMesh;

class CCharacter : public IListener
{
public:
	CCharacter();
protected:
	D3DXVECTOR3				m_vDirection;
	D3DXVECTOR3				m_vPosition;
	D3DXMATRIXA16			m_matRotY;
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			matT;
	D3DXCOLOR				m_color;
	bool					m_isCollided;
	bool					m_isOBB;
	bool					m_isJump;
	float					m_fMaxJumpHeight;
	float					m_fRadianJump;
	bool					m_isFallAni;
	D3DXVECTOR3 m_saveZonePosition;
	CSkinnedMesh*			m_Character;
	bool					m_isColorChanged;
	float					m_fSpeed;
	float					m_fRotation;
	float					m_preRotation;
	float					m_fGrabRotation;
	Synthesize(bool, m_isGrab, Grab);
	int						m_nGrabAbleObeject;
	D3DXVECTOR3				m_vGrabDirection;
	D3DXVECTOR3				m_vGrabCamDir;	// >> 잡기 상태일 때 dir
	CRay					m_Ray;
	D3DXVECTOR3 m_vContactNormal;
	float m_fPenetration;
	bool m_isCollidedTile;
	float m_fHeightTile;
	bool m_isReset;
	float m_preJumpPosition;
	//SaveData
	
public:
	bool Keep;
	~CCharacter(void);
	void Setup();
	void SaveSetup();
	virtual void Update(D3DXVECTOR3 cameradirection);
	void Update(float duration);
	void DoRotation(const float& radian);
	void Render();

	D3DXVECTOR3& GetPosition();
	D3DXMATRIXA16* GetTransform();
	float Getrotation();

	void SetColor(D3DXCOLOR c);
	D3DXCOLOR GetColor();
	bool Collider(bool isCollided);

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName();

	void ColliderObject();

	void Reset();

	//이어하기
	void SaveData(D3DXVECTOR3 pos);
};