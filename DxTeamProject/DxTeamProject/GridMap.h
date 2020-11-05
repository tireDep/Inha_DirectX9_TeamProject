#pragma once
#include <process.h>
#include <thread>
#include <Windows.h>
#include "Frustum.h"
#include "IMap.h"

#define ThreadCnt 10

class CGridMap : public IMap
{
private:
	LPD3DXMESH m_origMesh;
	LPD3DXMESH m_nowMesh;

	D3DMATERIAL9 m_mtrl;
	LPDIRECT3DTEXTURE9 m_Texture;

	vector<ST_PNT_VERTEX> m_vecVertex;
	vector<DWORD> m_vecDIndex;

	HANDLE m_arrThread[ThreadCnt];
	thread m_thread;
 	CFrustum* m_frustum;

public:
	CGridMap();
	~CGridMap();

	virtual void Setup();
	virtual void Render();
	virtual void CalcFrustumMap(const vector<bool>& vecCheck);

	void CalcNewMap(CFrustum frustum);

	void ThreadFunc();
};

