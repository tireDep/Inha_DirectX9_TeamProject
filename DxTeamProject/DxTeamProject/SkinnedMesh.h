#pragma once
#include "AllocateHierarchy.h"

class COBB;

class CSkinnedMesh
{
protected:
	LPD3DXFRAME					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAniController;

	// >> animation blend
	float m_fBlendTime;
	float m_fPassedBlendTime;
	bool  m_isAniBlend;
	// << animation blend

	float m_passedTime;
	float m_maxPlayTime;
	string m_sNowPlayAni;

	// >> hitBox_OBB
	Synthesize(D3DXVECTOR3, m_vMin, Min);
	Synthesize(D3DXVECTOR3, m_vMax, Max);
	// << hitBox_OBB

	COBB* m_pOBB;
	D3DXMATRIXA16 m_matworldTM;
public:
	CSkinnedMesh();
	~CSkinnedMesh();

	void SetUp(char* szFolder, char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pMatParent);
	void Render(LPD3DXFRAME pFrame);
	void SetUpBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int nIndex); // 애니메이션
	void SetAnimationIndexBlend(int nIndex); //  애니메이션 블렌드

	void SetNowPlayMaxTime(LPD3DXANIMATIONSET aniInfo);

	void SetTransform(D3DXMATRIXA16 * pmat); // << 월드 매트릭스 설정

	COBB* GetOBB() { return m_pOBB; }
	//CPSOBB* GetOBB() { return m_pOBB; }

	bool CheckAnimationEnd();
};


