#pragma once
class MeshTile;

class Color_changer
{
public:
	Color_changer();
	~Color_changer();
private:
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9*>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	bool istrue;
public:
	

	void Setup(string folder, string file);
	void Update();
	void Render();

	bool RayCheck(MeshTile& meshtile);
	
	

};

