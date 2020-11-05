#pragma once

class cPyramid; 

class cGrid
{
public:
	cGrid();
	~cGrid();
private :
	vector<ST_PN_VERTEX>	m_vecVertex; 
	vector<cPyramid*>		m_vecPyramid; 

	vector<ST_PN_VERTEX> m_vecPrintVer;

	D3DMATERIAL9 m_mtrl;

public :
	void Setup(int nNumHalfTile = 15, float fInterval = 1.0f);
	void Render(); 
};

