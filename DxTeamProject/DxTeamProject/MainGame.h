#pragma once

class CCamera;
class CCube;
class CGrid;
class CUI;
class CLight;
class CSoundManager;
class CText;
class CGridMap;

class CMainGame
{
private:
	CCamera* m_pCamera;
	CGrid* m_pGrid;
	CCube* m_pCube;
	CUI *m_pUI;
	CLight*	m_pLight;
	CText*	m_pText;
	CGridMap* m_GridMap;

private:
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