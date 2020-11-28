#pragma once
#include "Object.h"

class CBox : public CObject
{
public:
	CBox();
	~CBox();

	void Setup();
	void Setup(ST_MapData setData);
	void Update();
	// ray
	void Update(CRay * ray);
	void Render();

	void SetDiffScale(D3DXVECTOR3 set) { };
};

