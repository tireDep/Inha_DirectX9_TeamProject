#pragma once
#include "PhysicsObject.h"

class CPhysicsSphere : public CPhysicsObject
{
public:
	CPhysicsSphere();
	~CPhysicsSphere();
private:
	D3DXVECTOR3		m_vCenter;
	float			m_fRadius;
	D3DXVECTOR3		m_vVelocity;

	//D3DXMATRIXA16	m_matLocal;
	//D3DXMATRIXA16	m_matWorld;
	//D3DMATERIAL9	m_stMtlSphere;
	//LPD3DXMESH		m_pMeshSphere;
public:
	void Setup();
	void Update(float duration);
	void Render();

	void SphereUpdate(float duration);
	void Hitball(CPhysicsSphere& ball);
	bool hasIntersected(CPhysicsSphere& ball);

	float getVelocity_X() { return this->m_vVelocity.x; }
	float getVelocity_Z() { return this->m_vVelocity.z; }
	float getVelocity_Y() { return this->m_vVelocity.y;  }
	void setPower(double vx, double vy, double vz);
	void setCenter(float x, float y, float z);
	void setRadius(float radius) { m_fRadius = radius; }
	float getRadius() const { return m_fRadius; }
	const D3DXMATRIXA16& getLocalTransform() const { return m_matLocal; }
	void setLocalTransform(const D3DXMATRIXA16& mLocal) { m_matLocal = mLocal; }
	D3DXVECTOR3 getCenter() const;

	void ReceiveEvent(ST_EVENT eventMsg);
	string GetName() { return m_strName; }
};