#pragma once
#include "PObject.h"

class CBox : public PObject
{
public:
	CBox();
	~CBox();
protected:
	Synthesize(float, m_fWidth, Width);
	Synthesize(float, m_fHeight, Height);
	Synthesize(float, m_fDepth, Depth);
public:
	void Setup();
	void Setup(const ST_MapData & mapData);

	virtual void Update(float duration) {};
	virtual void Update3D(float duration) {}
	virtual void Update(float duration, CHeight* pMap) {};
	virtual void SetPusingForce(D3DXVECTOR3 forcedirection) {};
	virtual void AddForce(const D3DXVECTOR3 & force) {};
	virtual void ClearAccumulator() {};
	virtual void Integrate(float duration) {};
	virtual void RunPhysics(float duration) {};
	virtual bool hasIntersected(CObject * otherobject) { return true; }
	virtual void CollisionOtherObject(CObject * otherobject) {};

	string GetName();
};