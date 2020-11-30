#pragma once

#include "Frustum.h"

class CCamera;
class CGrid;
class CUI;
class CText;
class CCharacter;
class CLight;
class CGridMap;
// class CFrustum;
/// �� �Ʒ��� ���� ���� �ִ� ����
class CHeight;
class CXfile;
class CColliderObject;
class CSkinnedMesh;
// Ray y check
class MeshTile;
// Rotation Test
class CTestRigidBody;
/// ������ ������ ���� �ּ�ó��
//class CSoundManager;
class CMainGame
{
private:
	CCamera*	m_pCamera;
	CGrid*		m_pGrid;
	CUI*		m_pUI;
	CText*		m_pText;
	CCharacter*	m_pCharacter;
	CLight*		m_pLight;
	CFrustum	m_pPrevFrustum;
	CFrustum	m_pNowFrustum;
	// CGridMap*	m_GridMap;
	CSkinnedMesh* m_pSkinnedMesh;
	/// �� �Ʒ��� ���� ���� �ִ� ����
	CXfile*		m_Xfile;
	CHeight* m_pHeightMap;
	// Ray y check
	MeshTile* m_pMeshTile;
	// Rotation Test
	CTestRigidBody* m_pRigidBody;
	/// ������ ������ ���� �ּ�ó��
	//CSoundManager* m_pSm;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();
	/// ������ ������ ���� �ּ�ó��
};