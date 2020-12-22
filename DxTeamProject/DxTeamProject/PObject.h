#pragma once
#include "Object.h"

const static D3DXVECTOR3 GRAVITY(0, -9.8f, 0);

class PObject :	public CObject
{
protected:
	Synthesize(D3DXCOLOR, m_Color, DxColor);
	bool		  m_isPicked;
	bool		  m_isClicked;
	
	D3DXCOLOR	  m_outLineColor;
	LPD3DXEFFECT  m_pShader;
	Color		  m_tmpColor;
	bool LoadAssets();
	void SetShader(const D3DXMATRIXA16& setMatWorld);

	D3DXVECTOR3 saveTranslation;
	D3DXVECTOR3 saveRotation;
	D3DXCOLOR ResetColor;

	D3DXVECTOR3 presentTranslation;
	D3DXVECTOR3 presentRotation;
	Synthesize(float, m_finverseMass, InverseMass);	// mass

	Synthesize(D3DXVECTOR3, m_vPosition, Position);	// center position
	Synthesize(D3DXVECTOR3, m_vVelocity, Velocity);	// velocity
	Synthesize(D3DXVECTOR3, m_vAcceleration, Acceleration); // acceleration
	Synthesize(float, m_fDamping, Damping);	// floating point error
	Synthesize(float, m_fLinearDrag, Drag);	// linear drag

	Synthesize(bool, m_isForceApplied, ForceApplied);
	Synthesize(D3DXVECTOR3, m_vForceVector, ForceVector);
	Synthesize(D3DXVECTOR3, m_vForceLocation, ForceLocation);

	Synthesize(float, m_fBoundingSphere, BoundingSphere);	// collision radius // Later Sphere
	Synthesize(float, m_fElasticity, Elasticity); // elasticity

	COBB* m_pOBB;
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
	virtual void SetPusingForce(D3DXVECTOR3 forcedirection);
	virtual void UpdateLand(float duration);
	virtual COBB* GetOBB() { return m_pOBB; }

	virtual void Render();
};