#pragma once
#include "AllocateHierarchy.h"

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

public:
	CSkinnedMesh();
	~CSkinnedMesh();

	void SetUp(char* szFolder, char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void SetUpBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);

	void SetNowPlayMaxTime(LPD3DXANIMATIONSET aniInfo);

	// >> hitBox_OBB
	CSkinnedMesh(char* szFolder, char* szFileName);
	void Load(char* szFolder, char* szFileName);
	void Destroy();
	void UpdateAndRender();
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void SetRandomTrackPosition();

	D3DXMATRIXA16 m_matworldTM;
	void SetTransform(D3DXMATRIXA16* pmat);
	// << hitBox_OBB
};

