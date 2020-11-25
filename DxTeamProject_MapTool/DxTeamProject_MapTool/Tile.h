#pragma once
#include "IObject.h"
#include "Ray.h"
class CTile : public IObject
{
public:
	CTile();
	~CTile();

	void Setup() { }
	void Setup(ST_MapData setData);
	void Update();
	// ray
	void Update(CRay * ray);
	void Render();
};