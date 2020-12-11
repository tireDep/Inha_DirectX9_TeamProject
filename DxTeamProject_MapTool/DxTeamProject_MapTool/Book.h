#pragma once
#include "IObject.h"
class CBook : public IObject
{
public:
	CBook();
	~CBook();

	void Setup() { }
	void Setup(ST_MapData setData);
	void Update() { }
	void Render();
	void SetDiffScale(D3DXVECTOR3 set);
};

