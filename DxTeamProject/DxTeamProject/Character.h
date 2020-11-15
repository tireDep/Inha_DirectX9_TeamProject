#pragma once
#include "IListener.h"

//class CCharacter : public CObject
class COBB;

class CCharacter : public IListener
{
public:
	CCharacter();
protected:
	vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXVECTOR3				m_vDirection;
	D3DXVECTOR3				m_vPosition;
	D3DXMATRIXA16			m_matRotY;
	D3DXMATRIXA16			m_matWorld;
	D3DCOLOR				m_color;
	bool					m_isCollided;
public:
	virtual ~CCharacter(void);
	virtual void Setup();
	virtual void Update(D3DXVECTOR3 cameradirection);
	virtual void DoRotation(const float& radian);
	virtual void DoMove(const float& velocity);
	virtual void Render();

	virtual D3DXVECTOR3& GetPosition();
	virtual D3DXMATRIXA16* GetTransform();

	virtual void SetColor(D3DCOLOR c);
	virtual D3DCOLOR GetColor();

	// tmp Collision Test
	// setup erase
	virtual bool Collider(bool isCollided);
	COBB* m_pOBB;
	COBB* GetOBB(); 

	void ReceiveEvent(ST_EVENT eventMsg) override;
	virtual string GetName();
};