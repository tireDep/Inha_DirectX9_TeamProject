#pragma once
#include "Object.h"

class CCylinder : public CObject
{
public:
	CCylinder();
	~CCylinder();

	void Setup();
	void Setup(ST_MapData setData);
	void Update();
	void Render();
};

