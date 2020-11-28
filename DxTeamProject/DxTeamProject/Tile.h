#pragma once
#include "IObject.h"

class CTile : public IObject
{
public:
	CTile();
	~CTile();

	void Setup() { }
	void Setup(ST_MapData setData);
	void Update();
	void Render();
};

