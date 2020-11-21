#pragma once

class CImguiClass;

class CToolMain
{
private:
	CImguiClass* m_pImgui;

public:
	CToolMain();
	~CToolMain();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	CImguiClass* GetImgui();
};

