#pragma once
#include "Object.h"

const static D3DXVECTOR3 GRAVITY(0, -9.8f, 0);

class PObject :	public CObject
{
protected:
	/// Color
	Synthesize(D3DXCOLOR, m_Color, DxColor);
	bool		  m_isPicked;
	bool		  m_isClicked;
	D3DXCOLOR	  m_outLineColor;
	LPD3DXEFFECT  m_pShader;
	Color		  m_tmpColor;
	bool LoadAssets();
	void SetShader(const D3DXMATRIXA16& setMatWorld);

	/// Physics
	Synthesize(float, m_finverseMass, InverseMass);	// mass
	Synthesize(D3DXVECTOR3, m_vInverseRotationInertia, inverseRotationInertia);	// Rotation Inertia;

	Synthesize(D3DXVECTOR3, m_vPosition, Position);	// center position
	Synthesize(D3DXVECTOR3, m_vLinearVelocity, LinearVelocity); // velocity
	Synthesize(D3DXVECTOR3, m_vLinearAcceleration, LinearAcceleration); // acceleration
	Synthesize(float, m_fDamping, Damping);	// floating point error
	Synthesize(float, m_fLinearDrag, Drag);	// linear drag
	Synthesize(D3DXVECTOR3, m_vLastFrameAcceleration, LastFrameAcceleration); // lastFrameAcceleration

	CTestAngleSet m_stOrientation; // Orientation
	Synthesize(D3DXVECTOR3, m_vAngularVelocity, AngularVelocity); // Angular Velocity
	Synthesize(D3DXVECTOR3, m_vAngularAcceleration, AngularAcceleration);	// Angular Accerleration
	Synthesize(D3DXVECTOR3, m_vTorque, Torque);	// Torque;

	Synthesize(bool, m_isForceApplied, ForceApplied);
	Synthesize(D3DXVECTOR3, m_vForceAccum, ForceAccum);
	Synthesize(D3DXVECTOR3, m_vForceVector, ForceVector);
	Synthesize(D3DXVECTOR3, m_vForceLocation, ForceLocation);

	Synthesize(float, m_fBoundingSphere, BoundingSphere);	// collision radius
	Synthesize(float, m_fElasticity, Elasticity); // elasticity
public:
	PObject();
	~PObject();

	virtual void Setup() = 0;
	virtual void Update(float duration);

	// Color
	virtual void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	virtual void ReceiveEvent(ST_EVENT eventMsg);
	virtual void OutlineRender();
	virtual void SetPickState(bool PickState);
	virtual void ChangeObjectColor();

	// Physics
	virtual void SetMass(const float mass);
	virtual float GetMass() const;
	virtual bool hasFiniteMass() const;
	virtual void SetOrientation(CTestAngleSet Orientation);
	virtual CTestAngleSet GetOrientation();
	virtual void SetPusingForce(D3DXVECTOR3 forcedirection);
	virtual bool hasIntersected(PObject * otherobject);
	virtual void CollisionOtherObject(PObject * otherobject);
	virtual void Collision3D(PObject * otherobject);
	virtual void UpdateLand(float duration);

	// Delete
	//virtual void Update3D(float duration) = 0;
	//virtual void Update(float duration, CHeight* pMap) = 0;
	virtual void AddForce(const D3DXVECTOR3 & force) = 0;
	virtual void ClearAccumulator() = 0;
	virtual void Integrate(float duration) = 0;
	virtual void RunPhysics(float duration) = 0;

	virtual void Render();

	// collide
	virtual void GenerateContacts() { };
};