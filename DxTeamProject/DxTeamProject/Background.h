#pragma once
#include "IObject.h"

class CBackground : public IObject
{
private:
	bool pBox, pCylinder, pSphere;
	bool player, render;

public:
	CBackground();
	virtual ~CBackground();
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	void SetBool(bool set) { player = set; }
	bool GetBool() { return render; }
	virtual void Setup() { };
	virtual void Setup(const ST_MapData & mapData);
	virtual void Update(float duration) { m_pOBB->Update(&m_matWorld);	};
	virtual void Render();
	virtual string GetName() { return m_strName; }
	D3DXVECTOR3 SendPosition(){ return D3DXVECTOR3(); }
};

/// Delete Later..
//virtual void Update(float duration, CHeight* pMap) { };
//virtual void Update3D(float duration) { };
//virtual void UpdateLand(float duration) { };
//virtual void SetPickState(bool set) { };
//virtual void OutlineRender() { }
//virtual void ReceiveEvent(ST_EVENT eventMsg) { };
// tmp physics
//virtual void SetMass(const float mass) { };
//virtual float GetMass() const { return float(); };
//virtual bool hasFiniteMass() const { return bool();  };
//virtual void SetPusingForce(D3DXVECTOR3 forcedirection) { };
//virtual void AddForce(const D3DXVECTOR3 & force) { };
//virtual void ClearAccumulator() { };
//virtual void Integrate(float duration) { };
//virtual void RunPhysics(float duration) { };
//virtual bool hasIntersected(CObject * otherobject) { return bool(); };
//virtual void CollisionOtherObject(CObject * otherobject) { };