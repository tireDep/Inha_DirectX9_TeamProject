#pragma once
class CGizmo
{
private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXMATRIXA16				m_matR;

public:
	CGizmo();
	~CGizmo();

	void Setup(D3DCOLOR c, D3DXMATRIXA16& mat);
	void Render();
};

