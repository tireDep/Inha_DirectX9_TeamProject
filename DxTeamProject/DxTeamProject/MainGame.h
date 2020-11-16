#pragma once

#include "Frustum.h"

class CCamera;
class CGrid;
class CUI;
class CText;
class CColliderObject;
class CCharacter;
class CLight;
class CParticleWorld;
class CGridMap;
// class CFrustum;

/// 릴리즈 버전을 위한 주석처리
//class CSoundManager;

class CMainGame
{
private:
	CCamera* m_pCamera;
	CGrid* m_pGrid;
	CUI *m_pUI;
	CText*	m_pText;
	CCharacter*	m_pCharacter;
	vector<CColliderObject*> m_vColliderCube;
	CLight*				m_pLight;
	CParticleWorld*		m_pParticleWorld;
	/// 릴리즈 버전을 위한 주석처리
	//CSoundManager* m_pSm;

	CFrustum m_pPrevFrustum;
	CFrustum m_pNowFrustum;
	CGridMap* m_GridMap;

public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();

	void Setup_OBB();
	void OBB_RENDER();
};