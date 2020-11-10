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
public:
	virtual ~CCharacter(void);
	virtual void Setup();
	virtual void Update(D3DXVECTOR3 cameradirection);
	virtual D3DXVECTOR3 DoMove(const float& radian);
	virtual void Render();
	virtual D3DXVECTOR3& GetPosition();
	virtual D3DXMATRIXA16* GetTransform();
	
	COBB* m_pOBB;
	COBB* GetOBB(); // �ð� ��� �߰���. Setup ���ζ� ���߿� �����.

	// get UI color -> set head color. ���쾾�� ��ġ��
	virtual void SetColor(D3DCOLOR c);

	virtual void ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam);
	virtual string GetName();
};