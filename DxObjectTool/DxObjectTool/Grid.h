#pragma once

class CPyramid;

class CGrid
{
public:
	CGrid();
	~CGrid();
private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	vector<CPyramid*>		m_vecPyramid;
public:
	void Setup(int nNumHalfTile = 50, float fInterval = 1.0f);
	void Render();
};