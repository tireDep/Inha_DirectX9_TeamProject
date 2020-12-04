#pragma once

#include "Frustum.h"

class CCamera;
class CGrid;
class CUI;
class CText;
class CCharacter;
class CLight;
class COrb;
class CSkydome;
/// 이 아래는 지울 수도 있는 선언
class CHeight;
class CXfile;
class CColliderObject;
class CSkinnedMesh;
// Ray y check
class MeshTile;
// Rotation Test
class CTestRigidBody;
class CTestCollision;
/// 릴리즈 버전을 위한 주석처리

//Gimmick
class Color_changer;

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

	COrb*		m_pOrb;
	CSkinnedMesh* m_pSkinnedMesh;

	CSkydome* m_pSkydome;
	/// 이 아래는 지울 수도 있는 선언
	CHeight* m_pHeightMap;
	// Ray y check
	MeshTile* m_pMeshTile;
	// Rotation Test
	//CTestRigidBody* m_pRigidBody;
	CTestRigidBody* m_pRigidBody;
	vector<CTestRigidBody*> vecRigidBody;
	/// 릴리즈 버전을 위한 주석처리
	//CSoundManager* m_pSm;

	//Gimmick;
	Color_changer* m_pChanger;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();
	
	// Rotation Test
	/// 릴리즈 버전을 위한 주석처리
};