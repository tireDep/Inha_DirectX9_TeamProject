#pragma once
#include "Object.h"

// OBB TEST
class CPSOBB;

class CBackground : public CObject
{
public:
	CBackground();
	virtual ~CBackground();

	virtual void Setup() { };
	virtual void Update(float duration) { };
	virtual void Update(float duration, CHeight* pMap) { };
	virtual void Update3D(float duration) { };
	virtual void UpdateLand(float duration) { };
	virtual void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	virtual void SetPickState(bool set) { };
	virtual void OutlineRender() { }

	virtual string GetName() { return m_strName; }
	virtual void ReceiveEvent(ST_EVENT eventMsg) { };

	// tmp physics
	virtual void SetMass(const float mass) { };
	virtual float GetMass() const { return float(); };
	virtual bool hasFiniteMass() const { return bool();  };
	virtual void SetPusingForce(D3DXVECTOR3 forcedirection) { };
	virtual void AddForce(const D3DXVECTOR3 & force) { };
	virtual void ClearAccumulator() { };
	virtual void Integrate(float duration) { };
	virtual void RunPhysics(float duration) { };
	virtual bool hasIntersected(CObject * otherobject) { return bool(); };
	virtual void CollisionOtherObject(CObject * otherobject) { };

	virtual void Setup(ST_MapData setData);
	virtual void Render();

	// OBB TEST
	CPSOBB* m_pOBB;
};