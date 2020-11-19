#pragma once
class CXfile
{
private:
	ID3DXBuffer* adjBuffer;
	ID3DXBuffer* mtrlBuffer;
	DWORD numMtrls;

	ID3DXMesh* Mesh;
	vector<D3DMATERIAL9> Mtrls;
	vector<IDirect3DTexture9*> Textures;

public:
	CXfile();
	~CXfile();
	void Setup();
	void Render();
};

