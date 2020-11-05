#pragma once


class CCharacter : public CObject
{
public:
	CCharacter();
	//~cCharacter();
protected:
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

	virtual D3DXMATRIXA16 * GetTransform()
	{
		return &m_matWorld;
	}
};

