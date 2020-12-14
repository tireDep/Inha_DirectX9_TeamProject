#pragma once
#include "IObject.h"

class CItem : public IObject
{
protected:
	CItem();
public:
	virtual ~CItem();

	virtual void Setup() { };
	virtual void Update() { };

	virtual void Setup(ST_MapData setData);
	virtual void Render();

	// ray
	// virtual void Update(CRay * ray) { }
	// virtual void Setup_OBB_Box() { }
	// virtual void Render_OBB_Box() { }
};

