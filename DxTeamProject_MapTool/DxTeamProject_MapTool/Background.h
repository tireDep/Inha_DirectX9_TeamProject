#pragma once
#include "IObject.h"

class CBackground : public IObject
{
protected:	
	CBackground();

public:
	virtual ~CBackground();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

