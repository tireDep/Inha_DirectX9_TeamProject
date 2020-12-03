#pragma once
#include "Object.h"
#include "cHeight.h"

class CPSphere : public CObject
{
public:
	CPSphere();
	~CPSphere();
protected:
	Synthesize(float, m_fRadius, Radius);
public:
	void Setup();
	void Setup(D3DXVECTOR3 center);
	void Update(float duration);
	void Update3D(float duration);
	void Update(float duration, CHeight* pMap);
	void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	void Render();
	void SetPickState(bool set);

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);

	// physics
	void SetPusingForce(D3DXVECTOR3 forcedirection);
	void AddForce(const D3DXVECTOR3& force);
	void ClearAccumulator();
	void Integrate(float duration);
	void RunPhysics(float duration);
	bool hasIntersected(CObject* otherobject);
	void CollisionOtherObject(CObject* otherobject);

	// >>> pasing
	void Setup(const ST_MapData & mapData);
};