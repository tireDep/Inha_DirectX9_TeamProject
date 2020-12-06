#pragma once
#include "PObject.h"

class CCylinder : public PObject
{
public:
	CCylinder();
	~CCylinder();
protected:
	Synthesize(float, m_fRadius, Radius);
	Synthesize(float, m_fHeight, Height);
public:
	void Setup();
	void Setup(const ST_MapData & mapData);

	string GetName();
};