#pragma once
class cCubePC; 
class cCamera; 
class cGrid; 
class cCubeMan; 
class DirectionLight;
class SpotLight;
class PointLight;

class cGroup;

class cFrame;

class cMtlTex;

class CSkinnedMesh;

class CFrustum;

class CZealot;

class CHeigthMap;

#include "cLight.h"

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private :
	cCubePC*		m_pCubePC; 
	cCamera*		m_pCamera; 
	cGrid*			m_pGrid; 

	cCubeMan*		m_pCubeMan; 

	DirectionLight* m_directLight;
	SpotLight* m_SpotLight;
	PointLight* m_PointLight;

	vector<cLight *> m_vecLight;

	// >> : for texture 
	LPDIRECT3DTEXTURE9		m_pTexture; 
	vector<ST_PT_VERTEX>	m_vecVertex; 
	// << :

	vector<cGroup*> m_vecGroup;

	iMap *m_pMap;

	cFrame* m_pRootFrame;

	// >> mesh
	LPD3DXMESH m_pMeshTeaPot;
	LPD3DXMESH m_pMeshSphere;
	D3DMATERIAL9 m_stMtlTeaPot;
	D3DMATERIAL9 m_stMtlSphere;

	LPD3DXMESH m_pObjMesh;
	vector<cMtlTex*> m_vecObjMtlTex;
	// << mesh

	// >> piking
	vector<ST_SPHERE> m_vecSphere;
	D3DMATERIAL9 m_stMtlNone;
	D3DMATERIAL9 m_stMtlPicked;
	D3DMATERIAL9 m_stMtlPlane;	// 바닥
	vector<ST_PN_VERTEX> m_vecPlanVertex;	// 바닥
	D3DXVECTOR3 m_vPickedPosition;	// 현재 선택 위치
	// << piking

	CSkinnedMesh* m_pSkinnedMesh;

	// >>
	LPD3DXMESH		m_pSphere;
	D3DMATERIAL9	m_stCullingMtl;
	vector<ST_SPHERE*> m_vecCullingSphere;
	CFrustum* m_pFrustum;
	// <<

	// >> OBB
	CZealot* m_pHoldZealot;
	CZealot* m_pMoveZealot;
	// << OBB

	// >> font
	LPD3DXFONT m_pFont;

	ID3DXMesh* m_p3DText;
	// << font

	// >> UI
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_stImgInfo;
	LPDIRECT3DTEXTURE9 m_pTextureUI;
	// 따로 모아서 관리하는 형태로 만들어 둘 것
	// << UI

	// >> shader
	vector<ST_PC_VERTEX> m_vecVertexParticle;
	// << shader

	// >> multiTexture
	int m_nType;
	LPDIRECT3DTEXTURE9 m_pTex0;
	LPDIRECT3DTEXTURE9 m_pTex1;
	LPDIRECT3DTEXTURE9 m_pTex2;
	LPDIRECT3DTEXTURE9 m_pTex3;

	vector<ST_PT_VERTEX> m_vecVertex_Multi;
	// << multiTexture

	// >> shader2
	LPD3DXEFFECT m_pShader;
	bool LoadAssets();
	LPD3DXEFFECT LoadShader(const char * filename);
	// << shader2

	// >> Added
	CHeigthMap* m_heightMap;

public :
	void Setup(); 
	void Update(); 
	void Render(); 
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 

	void Set_Light(); 

	void Draw_Texture(); 

	void SetUp_Obj();
	void Render_Obj();

	void Load_Surface();

	// >> mesh
	void SetUp_MeshObj();
	void Render_MeshObj();
	// << mesh

	// >> piking
	void SetUp_PickingObj();
	void PickingObj_Render();
	// << piking

	// >> heightMap
	void SetUp_HeightMap();
	// << heightMap

	void Render_SkinnedMesh();

	// >> frustum
	void SetUp_Frustum();
	void Render_Frustum();
	// << frustum

	// >> OBB
	void SetUp_OBB();
	void Render_OBB();
	// << OBB

	// >> font
	void Create_Font();
	void Render_Txt();
	// << font

	// >> UI
	void SetUp_UI();
	void Render_UI();
	// << UI

	// >> shader
	void SetUp_Particle();
	void Update_Particle();
	void Render_Particle();
	// << shader

	// >> multiTexture
	void Setup_MultiTexture();
	void Update_MultiTexture();
	void Render_MultiTexture();

	void Render_MultiTexture1();
	void Render_MultiTexture2();
	void Render_MultiTexture3();
	void Render_MultiTexture4();
	void Render_MultiTexture5();
	void Render_MultiTexture6();
	void Render_MultiTexture7();
	void Render_MultiTexture8();
	void Render_MultiTexture9();
	void Render_MultiTexture0();
	void Render_MultiTexture_default();
	// << multiTexture
};

