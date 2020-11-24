#pragma once
#include "Background.h"

class CTile : public CBackground
{
public:
	CTile();
	~CTile();

	void Setup();
	void Setup(ST_MapData setData);
	void Update();
	void Render();
};

