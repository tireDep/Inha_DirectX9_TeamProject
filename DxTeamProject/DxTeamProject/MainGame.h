#pragma once

class CCamera;
class CGrid;
class CUI;
class CText;
class CColliderObject;
class CCharacter;
class CLight;

/// ������ ������ ���� �ּ�ó��
//class CSoundManager;
//class CGridMap;

class CMainGame
{
private:
	CCamera* m_pCamera;
	CGrid* m_pGrid;
	CUI *m_pUI;
	CText*	m_pText;
	CCharacter*	m_pCharacter;
	vector<CColliderObject*> m_vColliderCube;

	CLight*				m_pLight;
	vector<ST_SPHERE>	m_vecSphere; // ��ŷ �� ������Ʈ
	D3DMATERIAL9		m_stMtlNone; //  ��ŷ �ȵǾ�������
	D3DMATERIAL9		m_stMtlPicked; // ��ŷ�Ǿ�����
	LPD3DXMESH			m_pMeshSphere; // �޽� ��
	D3DMATERIAL9		m_stMtlSphere; // �޽� �� ���͸���

	/// ������ ������ ���� �ּ�ó��
	//CGridMap* m_GridMap;
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

	void Setup_PickingObj();
	void PickingObj_Render();
};