#pragma once
#include "PObject.h"

class IObject;
class CBox;
class CCylinder;

class CSphere : public PObject
{
public:
	CSphere();
	~CSphere();
protected:
	bool render = true;
	Synthesize(float, m_fRadius, Radius);
public:
	void Setup();
	void Setup(const ST_MapData & mapData);
	void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	void Update(float duration);

	bool hasIntersected(CSphere * otherSphere);
	bool hasIntersected(CBox * otherBox);
	bool hasIntersected(CCylinder * otherCylinder);
	bool hasIntersected(IObject * otherIObject);
	bool GetBool() { return render; }
	string GetName();
};