#pragma once
#include "iMap.h"

class CHeigthMap : public iMap
{
private:
	LPD3DXMESH m_pMesh;
	vector<D3DXVECTOR3> m_vecVertex;
	D3DMATERIAL9 m_stMtl;
	LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nTileN;

	// >> Added
	LPD3DXMESH m_pViewMesh;
	vector<ST_PNT_VERTEX> m_vecPNTVertex;
	vector<DWORD> m_vecindex;


public:
	CHeigthMap();
	virtual ~CHeigthMap();

	void SetUp(char* szFolder, char* szRaw, char*szTex, DWORD dwBytesPerPixel = 1);

	virtual void Render() override;
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;
	void Destroy();

	vector<D3DXVECTOR3> GetVecVertex();

	void SetFrustumMap(const vector<bool>& vecCheck);
};

