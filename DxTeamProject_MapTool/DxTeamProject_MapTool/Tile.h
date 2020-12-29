#pragma once
#include "IObject.h"
#include "Ray.h"

class CTile : public IObject
{
private:
	vector<ST_PNT_VERTEX> m_vecVertex;

public:
	CTile();
	~CTile();

	void Setup() { }
	void Setup(ST_MapData setData);
	void Update();

	void Render();

	void SetDiffScale(D3DXVECTOR3 set) { };
};