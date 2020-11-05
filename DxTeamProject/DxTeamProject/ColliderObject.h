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
	
	D3DXMATRIXA16 m_matWorldTM;
	Synthesize_Add_Ref(CCharacter*, m_pCharacterController, CharecterController);
	
public:
	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;
	COBB* m_pOBB;
public :
	void Setup(); 
	void Update();
	void Render(D3DXCOLOR c);
	COBB* GetOBB();
	D3DXVECTOR3& GetPosition();
};

