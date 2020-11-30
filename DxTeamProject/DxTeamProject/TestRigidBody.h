#pragma once
#include "TestForce.h"
#include "TestAngleSet.h"

class CTestRigidBody
{
public:
	CTestRigidBody();
	~CTestRigidBody();
private:
	ID3DXMesh*	m_pMesh;
	D3DMATERIAL9 m_stMtl;

	// linear
	float m_fMass;	// mass
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vPosition, Position);	// center of mass position
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vLinearVelocity, LinearVelocity);	// linear velocity
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vLinearAccerleration, LinearAccerleration);	// linear accerleration
	CTestForce sumForces;

	// rotation
	CTestAngleSet currentOrientation;
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vAngularVelocity, AngularVelocity); // angular velocity
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vAngularAccerleration, AngularAccerleration);	// angular accerleration
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vRotationInertia, RotationInertia);	// Rotation Inertia;
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vTorque, Torque);	// Torque;

	Synthesize(bool, m_isForceApplied, ForceApplied);
	D3DXMATRIXA16 m_matWorld;
public:
	void setMass(float massValue);
	float getMass();

	void setForce(CTestForce sumExternalForces);
	CTestForce getForce();

	void setCurrentOrientation(CTestAngleSet newOrientation);
	CTestAngleSet getCurrentOrientation();

	void Setup();
	void Update(float duration);
	void Render();
};