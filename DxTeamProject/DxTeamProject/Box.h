#pragma once
#include "PObject.h"

class IObject;
class CCylinder;

class CBox : public PObject
{
public:
	CBox();
	~CBox();
protected:
	Synthesize(float, m_fWidth, Width);
	Synthesize(float, m_fHeight, Height);
	Synthesize(float, m_fDepth, Depth);
	bool render = true;
public:
	void Setup();
	void Setup(const ST_MapData & mapData);
	void Update(float duration);
	bool hasIntersected(CBox * otherBox);
	bool hasIntersected(CCylinder * otherCylinder);
	bool hasIntersected(IObject * otherIObject);
	
	string GetName();

	COBB* GetOBB() { return m_pOBB; }

	bool GetBool() { return render; }
};