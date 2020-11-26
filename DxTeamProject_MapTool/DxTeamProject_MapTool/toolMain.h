#pragma once

class CGrid;
class CCube;
class CCamera;
class CImguiClass;
class CRay;
class CLight;

class CToolMain
{
private:
	CGrid* m_pGrid;
	CCube* m_pCube;
	CCamera* m_pCamera;
	CImguiClass* m_pImgui;
	CRay* m_pRay;
	CLight* m_pLight;

public:
	CToolMain();
	~CToolMain();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	CImguiClass* GetImgui();
};

