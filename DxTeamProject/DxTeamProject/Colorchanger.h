#pragma once
class MeshTile;
class COBB;


class Color_changer
{
public:
	Color_changer();
	~Color_changer();
private:
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh); // 장치 메쉬.
					   LPD3DXMESH m_pMeshBeam; //빔 메쉬.
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	D3DXMATRIXA16 matWorld , BeamWorld; //장치월드 , 빔월드
	D3DXMATRIXA16 matS, matT , matR;
	D3DXVECTOR3 m_position , m_scale; //빔포지션 , 빔 크기 

	float angle; //장치 , 빔 앵글 조절.

	float length; // 빔 길이 조절.
	
	COBB* m_pOBB; // 빔의 충돌 처리
	D3DXCOLOR c; 
	D3DXVECTOR3 m_vMin, m_vMax;

	// KT
	float m_fHitLength;
public:
	D3DMATERIAL9 m_stMtl;

	void Setup(string folder, string file); // x파일
	void Update();
	void Render();
	COBB* GetOBB() { return m_pOBB; }
	
	D3DXVECTOR3 GetPos() { return m_position; }
	D3DXVECTOR3 GetScale() { return m_scale; }
	void SetColor(D3DXCOLOR color);

	// KT
	void SetHitLength(float HitLength); // 빔이 맞았을때 거리 구해줌.


	//인터섹트
	bool RayCheck(MeshTile& meshtile);
};

