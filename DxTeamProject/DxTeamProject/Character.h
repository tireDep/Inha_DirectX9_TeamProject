#pragma once

//class CCharacter : public CObject
class COBB;

class CCharacter
{
public:
	CCharacter();
	//~cCharacter();
protected:
	vector<ST_PC_VERTEX>	m_vecVertex;
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;
public:
	virtual ~CCharacter(void);
	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual D3DXVECTOR3& GetPosition();
	virtual D3DXMATRIXA16 * GetTransform();

	COBB* m_pOBB;
	COBB* GetOBB(); // 시간 없어서 추가함. Setup 내부랑 나중에 지우기.
};