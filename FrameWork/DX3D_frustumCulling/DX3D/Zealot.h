#pragma once
#include "cCharacter.h"

class CSkinnedMesh;
class COBB;

class CZealot
{
private:
	CSkinnedMesh* m_pSkinnedMesh;
	COBB* m_pOBB;
	Synthesize_Add_Ref(cCharacter*, m_pCharacterController, CharacterController);

public:
	CZealot();
	virtual ~CZealot(void);

	void SetUp();
	void Update(iMap* pMap);
	void Render(D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255));

	COBB* GetOBB();

};

