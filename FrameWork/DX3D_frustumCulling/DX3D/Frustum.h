#pragma once
class CFrustum
{
private:
	vector<D3DXVECTOR3> m_vecProjVertex;
	vector<D3DXVECTOR3> m_vecWorldVertex;
	vector<D3DXPLANE>	m_vecPlane;

public:
	CFrustum();
	~CFrustum();

	void SetUp();
	void Update();
	bool IsIn(ST_SPHERE* pSphere);

	bool IsInFrustum(D3DXVECTOR3 pos);

};

