#pragma once
class MovingCube
{
public:
	MovingCube();
	~MovingCube();

private:
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	int IndexNum; // 번호.
	bool istrue; //범위 조절 장치
	float speed; //속도
	float startpos , endpos; // 거리 ?
	D3DXVECTOR3 m_position;

	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matS, matT, matR;

public:
	void Setup(string folder, string file);
	
	void Update();

	void Render();
};

