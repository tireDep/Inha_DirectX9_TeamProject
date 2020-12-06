#pragma once

class IObject;

class COBB
{
private:
	D3DXVECTOR3			 m_vOriCenterPos;	 // center
	D3DXVECTOR3			 m_vOriAxisDir[3];	 // axis	
	float				 m_fAxisHalfLen[3];	 // distance of center to OBB surface
	D3DXMATRIXA16		 m_matWorld;		 // matrix
	vector<ST_PC_VERTEX> m_vecOBBLineVertex; // OBB Box Line
	vector<D3DXVECTOR3> m_vecVertex;		 // OBB Box spot(36) 
	
public:
	COBB();
	~COBB();

	void Setup(IObject* object);
	void Update(D3DXMATRIXA16* pmatWorld);
	void Render();

	vector<D3DXVECTOR3> GetOBBVertex();
};

