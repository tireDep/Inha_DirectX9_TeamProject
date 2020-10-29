#pragma once

class CCamera;
class CCube;
class CGrid;
class cUI;
class CLight;


class CMainGame
{
private:
	CCamera* m_pCamera;
	CGrid* m_pGrid;
	CCube* m_pCube;
	cUI *m_pUI;
	CLight*	m_pLight;

public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();
};