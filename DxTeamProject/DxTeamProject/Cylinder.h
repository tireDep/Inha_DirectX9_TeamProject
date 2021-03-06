#pragma once
#include "PObject.h"

class IObject;

class CCylinder : public PObject
{
public:
	CCylinder();
	~CCylinder();
protected:
	Synthesize(float, m_fRadius, Radius);
	Synthesize(float, m_fHeight, Height);
	bool render = true;
public:
	void Setup();
	void Setup(const ST_MapData & mapData);
	void Update(float duration);

	bool hasIntersected(CCylinder * otherCylinder);
	bool hasIntersected(IObject * otherIObject);

	string GetName();

	COBB* GetOBB() { return m_pOBB; }

	bool GetBool() { return render; }
};