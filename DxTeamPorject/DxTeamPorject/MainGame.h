#pragma once

class CCamera;
class CCube;

class CMainGame
{
private:
	CCamera* m_pCamera;
	CCube* m_pCube;

public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetUp();
	void Update();
	void Render();
};

