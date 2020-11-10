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
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matRotY;
	D3DXMATRIXA16	m_matWorld;

	D3DCOLOR m_color;

	float			m_fRot;

public:
	virtual ~CCharacter(void);
	virtual void Setup();
	virtual void Update(D3DXVECTOR3 cameradirection);
	virtual void DoRotation(const float& radian);
	virtual void DoMove(const float& velocity);
	virtual void DoMatrix();
	virtual void Render();
	virtual D3DXVECTOR3& GetPosition();
	virtual D3DXMATRIXA16* GetTransform();
	
	D3DCOLOR GetColor();

	COBB* m_pOBB;
	COBB* GetOBB(); // 시간 없어서 추가함. Setup 내부랑 나중에 지우기.

	// get UI color -> set head color. 현우씨랑 합치기
	virtual void SetColor(D3DCOLOR c);

	virtual void ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam);
	virtual string GetName();
};