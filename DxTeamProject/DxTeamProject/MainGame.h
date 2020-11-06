#pragma once

class CCamera;
class CGrid;
class CUI;
class CLight;
class CSoundManager;
class CText;
class CGridMap;
class CColliderObject;
class CRigidBody;
class CGravity;

class CMainGame
{
private:
	CCamera* m_pCamera;
	CGrid* m_pGrid;
	CUI *m_pUI;
	CLight*	m_pLight;
	CText*	m_pText;
	CGridMap* m_GridMap;



	//충돌큐브
	vector<CColliderObject*> m_vColliderCube;

	CRigidBody*		m_pRigidbody;
	CRigidBody*		m_pRigidbody2;
	CGravity*		m_pGravity;
private:
	CSoundManager* m_pSm;
	bool		m_isDevMode;
	bool		m_Uimode;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();


	// 충돌
	void Setup_OBB();
	void OBB_RENDER();
};