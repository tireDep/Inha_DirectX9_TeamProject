#pragma once

#include "IObject.h"

class CObject : public IObject
{
public:
	CObject();
	virtual ~CObject();

	virtual void Setup();
	virtual void Setup(ST_MapData setData);
	virtual void Render();
};

