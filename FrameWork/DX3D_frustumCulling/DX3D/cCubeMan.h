#pragma once
#include "cCharacter.h"
class cCubeNode; 

class cCubeMan :
	public cCharacter
{
public:
	cCubeMan();

protected :
	cCubeNode*			m_pRoot; 
	D3DMATERIAL9		m_stMtl; 

	LPDIRECT3DTEXTURE9		m_pTexture;

public : 
	virtual ~cCubeMan(); 

	virtual void Setup() override; 
	virtual void Update(iMap *pMap);
	virtual void Render() override; 
};

