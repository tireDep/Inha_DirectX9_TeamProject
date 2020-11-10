#pragma once

#include "Character.h"
class COBB;

class CColliderObject
{
public:
	CColliderObject();
	~CColliderObject();
private :
	std::vector<ST_PC_VERTEX>	m_vecVertex; 
	float						m_fRotY; 
	D3DXVECTOR3					m_vDirection; 
	D3DXVECTOR3					m_vPosition;
	D3DXVECTOR3					m_vCPosition;
	D3DXMATRIXA16			    m_matWorldTM;
	D3DXCOLOR					m_color;
public:
	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;
	COBB* m_pOBB;
public :
	void Setup(D3DXVECTOR3 position);
	void Update(D3DXCOLOR C);
	void Render();
	COBB* GetOBB();
	D3DXCOLOR GetColor();
	D3DXVECTOR3& GetPosition();
};