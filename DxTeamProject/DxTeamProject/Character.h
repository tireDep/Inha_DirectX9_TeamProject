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

	bool istrue;
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

	virtual bool Collider(bool a);
	COBB* m_pOBB;
	COBB* GetOBB(); // 시간 없어서 추가함. Setup 내부랑 나중에 지우기.

	virtual void ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam);
	virtual string GetName();
};