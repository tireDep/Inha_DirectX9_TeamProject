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
/// 릴리즈 버전을 위한 주석처리

//Gimmick
class Color_changer;
class CDoor;
class CBreakableWall;
class RotationBoard;

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
	vector<MeshTile*> m_pMeshTile;
	//Gimmick;
	Color_changer* m_pChanger;
	CDoor* m_pGimmick_Door[2];
	RotationBoard* m_pGimmick_RotationBoard;
	/// 릴리즈 버전을 위한 주석처리
	//CSoundManager* m_pSm;
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();
};