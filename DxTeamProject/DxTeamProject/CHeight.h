#pragma once
class CHeight
{
private:
	LPD3DXMESH					m_pMesh;
	std::string					m_sTexture;
	D3DMATERIAL9				m_stMtl;
	std::vector<D3DXVECTOR3>	m_vecVertex;
	int							m_nTile;
public:
	CHeight(void);
	~CHeight(void);

	void Setup(char* szFolder, char* szRawFile,int nBytesPerColor = 1);
	void Render();
	bool GetHeight(IN float x, OUT float& y, IN float z);
};
