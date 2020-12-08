#pragma once

class COBB
{
public:
	COBB();
	~COBB();
private:
	D3DXVECTOR3 m_OriCenterPos;
	D3DXVECTOR3 m_vOriAxisDir[3];		//축
	D3DXVECTOR3 m_vCenterPos;
	vector<ST_PC_VERTEX> m_vecVertex;
	D3DXVECTOR3 m_vAxisDir[3];			//방향
	float m_fAxisLen[3];				//축의 길이
	float m_fAxisHalfLen[3];
public:
	D3DXMATRIXA16 m_matWorldTM;
	void SetupCube(ST_PC_VERTEX v1, ST_PC_VERTEX v2,float CubeSize);
	void SetUpXFile(D3DXVECTOR3 &vMin, D3DXVECTOR3 &vMax);
	void Update(D3DXMATRIXA16 *pmatWorld);
	void SetupTile(D3DXVECTOR3& vMin, D3DXVECTOR3& vMax, D3DXVECTOR3 xfileY ,float x, float z);
	void SetupMesh(D3DXVECTOR3 &vMin, D3DXVECTOR3 &vMax ,float cubesize);
	static bool IsCollision(COBB * pOBB1, COBB* pOBB);
	void OBBBOX_RENDER(D3DXCOLOR c);
};