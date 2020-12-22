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
class MovingCube;
//Gimmick
class Color_changer;
class CDoor;
class CBreakableWall;
class RotationBoard;
class CSwitch;
class CBook;
class CDragon;
class CSoundManager;
class CBox;
class CSphere;
//
class CScene;
//


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

	CSkydome* m_pSkydome;
	CHeight* m_pHeightMap;
	// Ray y check
	vector<MeshTile*> m_pMeshTile;
	//Gimmick;
	Color_changer* m_pChanger;
	//CDoor* m_pGimmick_Door[2];
	//RotationBoard* m_pGimmick_RotationBoard;
	CSwitch* m_pGimmick_Switch;
	CBreakableWall* m_pGimmick_BreakableWall[2];

	// tmp
	//CBox* m_pBox;
	//CSphere* m_pSphere;
	CBook* m_pBook;
	CDragon* m_pDragon;
	MovingCube* m_pMovingCube;
	//
	CScene* m_pScene;
	//
	/// 릴리즈 버전을 위한 주석처리
	//
public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();
};