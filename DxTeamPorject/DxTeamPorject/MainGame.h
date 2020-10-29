#pragma once

class CCamera;
class CCube;
class CLight;

class CMainGame
{
private:
	CCamera* m_pCamera;
	CCube*	m_pCube;
	CLight*	m_pLight;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();
};