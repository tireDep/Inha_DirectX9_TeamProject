#pragma once

class CGizmo;

class CGrid
{
private:
	vector<ST_PN_VERTEX> m_vecVertex;
	vector<CGizmo*> m_vecGizmo;

	vector<ST_PN_VERTEX> m_vecPrintVer;

	D3DMATERIAL9 m_mtrl;

public:
	CGrid();
	~CGrid();

	void Setup(int nNumHalfTile = 15, float fInterval = 1.0f);
	void Render();
};

