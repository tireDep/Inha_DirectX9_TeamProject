#pragma once
#include "Object.h"
#include "cHeight.h"

class CPSBox : public CObject
{
public:
	CPSBox();
	~CPSBox();
protected:
	Synthesize(float, m_fWidth, Width);
	Synthesize(float, m_fHeight, Height);
	Synthesize(float, m_fDepth, Depth);
	//Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vPosition, Position);
	//Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vVelocity, Velocity);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vAcceleration, Acceleration);
	D3DXVECTOR3 m_vForceDirection;
	D3DXVECTOR3 m_vForceAccum;

public:
	void Setup();
	void Setup(D3DXVECTOR3 center);
	void Update(float duration);
	void Update(float duration, CHeight* pMap);
	void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	void Render();
	void SetPickState(bool set);

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);

	// physics
	void SetMass(const float mass);
	float GetMass() const;
	bool hasFiniteMass() const;
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