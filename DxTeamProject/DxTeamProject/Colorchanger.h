#pragma once
class MeshTile;
class COBB;


class Color_changer
{
public:
	Color_changer();
	~Color_changer();
private:
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh); // ��ġ �޽�.
					   LPD3DXMESH m_pMeshBeam; //�� �޽�.
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	D3DXMATRIXA16 matWorld , BeamWorld; //��ġ���� , ������
	D3DXMATRIXA16 matS, matT , matR;
	D3DXVECTOR3 m_position , m_scale; //�������� , �� ũ�� 

	float angle; //��ġ , �� �ޱ� ����.

	float length; // �� ���� ����.
	
	COBB* m_pOBB; // ���� �浹 ó��
	D3DXCOLOR c; 
	D3DXVECTOR3 m_vMin, m_vMax;

	// KT
	float m_fHitLength;
public:
	D3DMATERIAL9 m_stMtl;

	void Setup(string folder, string file); // x����
	void Update();
	void Render();
	COBB* GetOBB() { return m_pOBB; }
	
	D3DXVECTOR3 GetPos() { return m_position; }
	D3DXVECTOR3 GetScale() { return m_scale; }
	void SetColor(D3DXCOLOR color);

	// KT
	void SetHitLength(float HitLength); // ���� �¾����� �Ÿ� ������.


	//���ͼ�Ʈ
	bool RayCheck(MeshTile& meshtile);
};

