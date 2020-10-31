#pragma once

class CCamera;
class CCube;
class CGrid;
class CUI;
class CLight;
class CTimer;
class CFps;
class CSoundManager;
class CText;

class CMainGame
{
private:
	CCamera* m_pCamera;
	CGrid* m_pGrid;
	CCube* m_pCube;
	CUI *m_pUI;
	CLight*	m_pLight;
	CTimer*	m_pTimer;
	CFps* m_pFps;
	CText*	m_pText;
private:
	void Frame();
	CSoundManager* m_pSm;
	bool		m_isDevMode;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();
};