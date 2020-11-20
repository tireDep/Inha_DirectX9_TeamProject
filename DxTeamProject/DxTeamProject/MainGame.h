#pragma once

#include "Frustum.h"

class CCamera;
class CGrid;
class CUI;
class CText;
class CColliderObject;
class CCharacter;
class CLight;
class CGridMap;
// class CFrustum;
class CParticleWorld;
class CPhysicsSphere;
class CWall;
/// 릴리즈 버전을 위한 주석처리
//class CSoundManager;
//
class CXfile;
//

class CMainGame
{
private:
	CCamera*	m_pCamera;
	CGrid*		m_pGrid;
	CUI*		m_pUI;
	CText*		m_pText;
	CCharacter*	m_pCharacter;
	CLight*		m_pLight;
	CFrustum	m_pPrevFrustum;
	CFrustum	m_pNowFrustum;
	CGridMap*	m_GridMap;
	CParticleWorld*	m_pParticleWorld;
	CXfile*		m_Xfile;

	// tmp Physics
	CPhysicsSphere* m_pSphere1;
	CPhysicsSphere* m_pSphere2;

	CWall *m_pWall;

	/// 릴리즈 버전을 위한 주석처리
	//CSoundManager* m_pSm;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();

	/// 릴리즈 버전을 위한 주석처리
};