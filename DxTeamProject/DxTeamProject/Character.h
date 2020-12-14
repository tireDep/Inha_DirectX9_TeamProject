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
//	vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXVECTOR3				m_vDirection;
	D3DXVECTOR3				m_vPosition;
	D3DXMATRIXA16			m_matRotY;
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			matT;
	D3DXCOLOR				m_color;
	bool					m_isCollided;
	bool					m_isOBB;
	bool					m_jump;
	bool					jumpis;
	bool					jumping;
	CSkinnedMesh*			m_Character;
	bool					m_isColorChanged;

	float rotation;
	// grab
	int						m_nGrabAbleObeject;
	// Ray y check
	CRay					m_Ray;
public:
	virtual ~CCharacter(void);
	virtual void Setup();
	virtual void Update(D3DXVECTOR3 cameradirection);
//	virtual void Update(D3DXVECTOR3 cameradirection, CHeight* pMap);
	int Update(vector<PObject*> ObjectPosition, float duration);
	virtual void DoRotation(const float& radian);
	virtual void DoMove(const float& velocity);
	virtual void Render(D3DCOLOR c);

	virtual D3DXVECTOR3& GetPosition();
	virtual D3DXMATRIXA16* GetTransform();
	virtual float Getrotation();

	virtual void SetColor(D3DXCOLOR c);
	virtual D3DXCOLOR GetColor();
	COBB* m_pOBB;
	COBB* GetOBB() { return m_pOBB; }
	// tmp Collision Test
	// setup erase
	virtual bool Collider(bool isCollided);

	void ColliderOtherObject(IObject * background);
	
	// void SetBool(bool istrue);
	

	void ReceiveEvent(ST_EVENT eventMsg) override;
	virtual string GetName();

	// Ray y check
	virtual void UpdateRayYCheck(MeshTile & meshtile);
};