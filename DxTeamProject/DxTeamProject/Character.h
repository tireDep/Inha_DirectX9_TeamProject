#pragma once
#include "IListener.h"

class COBB;
class CRay;
class MeshTile;
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
	CRay					m_Ray;
	D3DXVECTOR3 m_vContactNormal;
	float m_fPenetration;
	bool m_isCollidedTile;
	float m_fHeightTile;


	//SaveData
	
public:
	bool Keep;
	virtual ~CCharacter(void);
	virtual void Setup();
	void SaveSetup();
	virtual void Update(D3DXVECTOR3 cameradirection);
	//virtual void Update(D3DXVECTOR3 cameradirection, CHeight* pMap);
	//int Update(vector<PObject*> ObjectPosition, float duration);
	void Update(float duration);
	virtual void DoRotation(const float& radian);
	virtual void DoMove(const float& velocity);
	virtual void Render(D3DCOLOR c);

	virtual D3DXVECTOR3& GetPosition();
	virtual D3DXMATRIXA16* GetTransform();
	virtual float Getrotation();

	virtual void SetColor(D3DXCOLOR c);
	virtual D3DXCOLOR GetColor();
	// tmp Collision Test
	// setup erase
	virtual bool Collider(bool isCollided);

	void ColliderOtherObject(IObject * background);
	// void SetBool(bool istrue);
	
	void ReceiveEvent(ST_EVENT eventMsg) override;
	virtual string GetName();

	// Ray y check
	virtual void UpdateRayYCheck(MeshTile & meshtile);

	// KT Character to Object
	void ColliderObject();

	/// KT Reset
	void Reset();

	//이어하기
	void SaveData(D3DXVECTOR3 pos);

};