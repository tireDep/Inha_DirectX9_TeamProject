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
	// ray
	void Update(CRay * ray);
	void Render();
};

