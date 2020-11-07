#pragma once

class CCamera;
class CGrid;
class CUI;
class CText;
class CColliderObject;
class CCharacter;

/// ������ ������ ���� �ּ�ó��
//class CLight;
//class CSoundManager;
//class CGridMap;
//class CRigidBody;
//class CGravity;

class CMainGame
{
private:
	CCamera* m_pCamera;
	CGrid* m_pGrid;
	CUI *m_pUI;
	CText*	m_pText;
	CCharacter*	m_pCharacter;
	vector<CColliderObject*> m_vColliderCube;

	/// ������ ������ ���� �ּ�ó��
	//CLight*	m_pLight;
	//CGridMap* m_GridMap;
	//CRigidBody*		m_pRigidbody;
	//CRigidBody*		m_pRigidbody2;
	//CGravity*		m_pGravity;
	//CSoundManager* m_pSm;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();

	void Setup_OBB();
	void OBB_RENDER();
};