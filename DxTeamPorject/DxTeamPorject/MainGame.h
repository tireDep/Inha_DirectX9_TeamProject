#pragma once

class CCamera;
class CCube;
class cUI;
class CMainGame
{
private:
	CCamera* m_pCamera;
	CCube* m_pCube;
	cUI *m_pUI;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();
};

