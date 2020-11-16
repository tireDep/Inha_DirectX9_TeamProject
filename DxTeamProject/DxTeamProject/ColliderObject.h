#pragma once

#include "Character.h"
class COBB;

class CColliderObject
{
public:
	CColliderObject();
	~CColliderObject();
private :
	
	float						m_fRotY; 
	D3DXVECTOR3					m_vDirection; 
	D3DXVECTOR3					m_vPosition;
	D3DXVECTOR3					m_vCPosition;
	D3DXMATRIXA16			    m_matWorldTM;
	D3DXCOLOR					m_color;
	vector<ST_PC_VERTEX> m_vecVertex;
	//Synthesize_Add_Ref(CCharacter*, m_pCharacterController, CharecterController);

public:

	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;
	COBB* m_pOBB;
public :
	void Setup(D3DXVECTOR3 position);

	void Update(D3DXCOLOR C);
	void Render();
	D3DXCOLOR GetColor();
	COBB* GetOBB();
	D3DXVECTOR3& GetPosition();
	D3DXVECTOR3& GetVecPosition(int index);
	int GetVecSize();
	void GetVecPick(bool pick);
};