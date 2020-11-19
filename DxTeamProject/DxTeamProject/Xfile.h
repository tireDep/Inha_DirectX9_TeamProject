#pragma once
class COBB;

class CXfile
{
private:
	ID3DXBuffer* adjBuffer;
	ID3DXBuffer* mtrlBuffer;
	DWORD numMtrls;
	D3DXMATRIXA16 World;
	LPD3DXMESH Mesh;
	vector<D3DMATERIAL9> Mtrls;
	vector<IDirect3DTexture9*> Textures;
	COBB* m_pOBB;
public:
	CXfile();
	~CXfile();
	void Update();
	void Setup();
	void Render(D3DXVECTOR3 eye);
};

