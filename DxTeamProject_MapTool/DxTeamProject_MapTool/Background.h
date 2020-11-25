#pragma once
#include "IObject.h"

class CRay;

class CBackground : public IObject
{
protected:	
	CBackground();

public:
	virtual ~CBackground();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	// ray
	virtual void Update(CRay * ray) = 0;
	virtual void Render() = 0;
};

