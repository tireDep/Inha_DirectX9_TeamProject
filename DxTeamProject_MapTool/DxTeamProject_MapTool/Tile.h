#pragma once
#include "Background.h"

class CTile : public CBackground
{
public:
	CTile();
	~CTile();

	void Setup();
	void Update();
	void Render();
};

