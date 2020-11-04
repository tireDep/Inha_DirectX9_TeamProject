#pragma once

class CSkinnedMesh;

class COBB
{
private:
	D3DXVECTOR3 m_vOriCenterPos;
	D3DXVECTOR3 m_vOriAxidDir[3];

	D3DXVECTOR3 m_vCenterPos;

	// >> �ڽ� �׸��µ� ���(x,y,z)
	D3DXVECTOR3 m_vAxisDir[3]; 
	float m_fAxisLen[3];	// �ڽ��� ������ ���� ����
	float m_fAxisHalfLen[3];
	// << �ڽ� �׸��µ� ���(x,y,z)

	D3DXMATRIXA16 m_matWorldTM;

	vector<ST_PC_VERTEX> m_vecVertex_Basic;
	vector<ST_PC_VERTEX> m_vecVertex;

public:
	COBB();
	~COBB();

	void SetUp(CSkinnedMesh* pSkinnedMesh);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(COBB* pOBB1, COBB* pOBB2);

	void Render_OBB_BOX(D3DCOLOR c);
};

