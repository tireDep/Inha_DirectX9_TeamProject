#pragma once
#include "Background.h"
#include "Ray.h"
class CTile : public CBackground
{
public:
	CTile();
	~CTile();

	void Setup();
	void Setup(ST_MapData setData);
	void Update();
	// ray
	void Update(CRay * ray);
	void Render();
};