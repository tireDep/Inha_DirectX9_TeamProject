#pragma once

class cFrame;
class cMtlTex;

class cAseLoader
{
private:
	FILE*	m_fp;
	char	m_szToken[1024];
	vector<cMtlTex*>		m_vecMtlTex;
	map<string, cFrame*>	m_mapFrame;

	// ------------------------------

	char*	GetToken();
	int		GetInteger();
	float	GetFloat();
	bool	IsWhite(IN char c);
	bool	IsEqual(IN char* str1, IN char* str2);
	void	SkipBlock();	// 필요없는 부분 건너뛰는 용도

	void	Process_MATERIAL_LIST();
	void	Process_MATERIAL(OUT cMtlTex* pMtlTex);
	void	Process_MAP_DIFFUSE(OUT cMtlTex* pMtlTex);

	cFrame*	Process_GEOMOBJECT();

	void	Process_MESH(OUT cFrame* pFrame);
	void	Process_MESH_VERTEX_LIST(OUT vector<D3DXVECTOR3>& vecV);
	void	Process_MESH_FACE_LIST(OUT vector<ST_PNT_VERTEX>& vecVertex, IN vector<D3DXVECTOR3>& vecV);
	void	Process_MESH_TVERTLIST(OUT vector<D3DXVECTOR2>& vecVT);
	void	Process_MESH_TFACELIST(OUT vector<ST_PNT_VERTEX>& vecVertex, IN vector<D3DXVECTOR2>& vecVT);
	void	Process_MESH_NORMAL(OUT vector<ST_PNT_VERTEX>& vecVertex);

	void	Process_NODE_TM(OUT cFrame* pFrame);

	// >> Animation
	void Process_TM_ANIMATION(OUT cFrame* pFrame);
	void Process_CONTROL_POS_TRACK(OUT cFrame* pFrame);
	void Process_CONTROL_ROT_TRACK(OUT cFrame* pFrame);

	void	Process_Scene();
	void	Set_SceneFrame(OUT cFrame* pRoot);

	DWORD m_dwFirstFrame;
	DWORD m_dwLastFrame;
	DWORD m_dwFrameSpeed;
	DWORD m_dwTicksPerFrame;
	// << Animation

public:
	cAseLoader();
	~cAseLoader();

	cFrame* Load(IN char* szFullPath);
};

