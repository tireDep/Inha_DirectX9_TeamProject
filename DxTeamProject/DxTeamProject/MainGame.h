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

/// ������ ������ ���� �ּ�ó��
//class CSoundManager;
class CParticleWorld;

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
	/// ������ ������ ���� �ּ�ó��
	//CSoundManager* m_pSm;
	CParticleWorld*	m_pParticleWorld;
	//vector<CColliderObject*> m_vColliderCube;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();

	/// ������ ������ ���� �ּ�ó��
	//void Setup_OBB();
	//void OBB_RENDER();
};