#pragma once

#include "Frustum.h"

class CCamera;
class CGrid;
class CUI;
class CText;
class CColliderObject;
class CCharacter;
class CLight;
class CParticleWorld;
class CGridMap;
// class CFrustum;

/// 릴리즈 버전을 위한 주석처리
//class CSoundManager;

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
	// vector<ST_SPHERE>	m_vecSphere; // 피킹 될 오브젝트
	// D3DMATERIAL9		m_stMtlNone; //  피킹 안되어있을떄
	// D3DMATERIAL9		m_stMtlPicked; // 피킹되었을때
	// LPD3DXMESH			m_pMeshSphere; // 메쉬 원
	// D3DMATERIAL9		m_stMtlSphere; // 메쉬 원 메터리얼

	LPD3DXMESH	 	m_sMeshCube;// 피킹 큐브
	vector<ST_CUBE>	m_vecPlaneVertex;

	CParticleWorld*		m_pParticleWorld;
	/// 릴리즈 버전을 위한 주석처리
	//CSoundManager* m_pSm;

	CFrustum m_pPrevFrustum;
	CFrustum m_pNowFrustum;
	CGridMap* m_GridMap;

public:
	CMainGame();
	~CMainGame();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup();
	void Update();
	void Render();

	void Setup_OBB();
	void OBB_RENDER();

	void Setup_PickingCube();
	void PickingCube_Render();
};