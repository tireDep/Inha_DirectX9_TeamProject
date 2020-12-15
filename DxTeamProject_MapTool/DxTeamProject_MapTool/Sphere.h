#pragma once
#include "Object.h"

class CSphere : public CObject
{
public:
	CSphere();
	~CSphere();

	void Setup();
	void Setup(ST_MapData setData);
	void Update();
	void Render();

	void SetDiffScale(D3DXVECTOR3 set);
};

