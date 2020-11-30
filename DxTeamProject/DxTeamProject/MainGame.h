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
/// 이 아래는 지울 수도 있는 선언
class CHeight;
class CXfile;
class CColliderObject;
class CSkinnedMesh;
// Ray y check
class MeshTile;
// Rotation Test
class CTestRigidBody;
/// 릴리즈 버전을 위한 주석처리
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
	/// 이 아래는 지울 수도 있는 선언
	CXfile*		m_Xfile;
	CHeight* m_pHeightMap;
	// Ray y check
	MeshTile* m_pMeshTile;
	// Rotation Test
	CTestRigidBody* m_pRigidBody;
	/// 릴리즈 버전을 위한 주석처리
	//CSoundManager* m_pSm;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();
	/// 릴리즈 버전을 위한 주석처리
};