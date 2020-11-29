#pragma once

class CFrustum
{
private:
	vector<D3DXVECTOR3> m_vecProjVertex;
	vector<D3DXVECTOR3> m_vecWorldVertex;
	vector<D3DXPLANE> m_vecPlane;

	D3DXVECTOR3 m_vLeftUpPos;
	D3DXVECTOR3 m_vRightDownPos;

public:
	CFrustum();
	~CFrustum();

	void Setup();
	void Update();

	bool IsInFrustum(D3DXVECTOR3 pos);

	bool IsUpdateCheck(CFrustum const &prevFrustum);

	// >> mapTest
	bool IsInFrustum(D3DXVECTOR3 pos, float radius);
};

