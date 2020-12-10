#pragma once
class CCharacter;

class CDragon
{
private:
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	LPDIRECT3DTEXTURE9 m_pTexture;
	ST_XFile* xfile = new ST_XFile;

	// >> testRotationMove
	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3 m_vDrangonPos;

	D3DXVECTOR3 m_vDirection;
	D3DXMATRIXA16 m_matRotY;

	bool m_isTrue;
	float Drangon_y;
	// << testRotationMove

public:
	CDragon();
	~CDragon();
	void Update(D3DXVECTOR3 pos);
	void Setup();
	void Render();
	void ChangeColor(D3DXCOLOR color);
	void DoRotation(const float & radian, D3DXVECTOR3 cameradirection);
	void DirectionSet(D3DXVECTOR3 cameradirection);
};

