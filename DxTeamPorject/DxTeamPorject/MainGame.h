#pragma once

class CCamera;
class CCube;
class CGrid;

class CMainGame
{
private:
	CCamera* m_pCamera;
	CCube* m_pCube;
	CGrid* m_pGrid;

public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();
};

