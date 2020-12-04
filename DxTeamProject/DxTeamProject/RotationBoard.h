#pragma once

enum class RotationAxial
{
	Rotation_X, Rotation_Y, Rotation_Z, NONE = 999
};
class RotationBoard
{
private:
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9*>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	D3DXMATRIXA16 m_matWorld;

	// size : Iobject inheritance
	RotationAxial rotationAxial;
	D3DXMATRIXA16 m_matRotGimmick;
	float m_fRotationSpeed;
	float m_fRot;
public:
	RotationBoard();
	~RotationBoard();
	void Setup(string folder, string file);
	void Update(float duration);
	void Render();
};