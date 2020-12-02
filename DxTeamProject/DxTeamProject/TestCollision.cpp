#include "stdafx.h"
#include "TestCollision.h"
#include "TestRigidBody.h"

CTestCollision::CTestCollision()
	: m_pFirstObject(NULL)
	, m_pSecondObject(NULL)
{
}

CTestCollision::~CTestCollision()
{
}

CTestCollision::CTestCollision(CTestRigidBody * firstObject, CTestRigidBody * secondObject)
{
	assert(firstObject  != NULL);
	assert(secondObject != NULL);
	m_pFirstObject = firstObject;
	m_pSecondObject = secondObject;
}

void CTestCollision::setFirstObject(CTestRigidBody * firstObject)
{
	assert(firstObject != NULL);
	m_pFirstObject = firstObject;
}

CTestRigidBody * CTestCollision::getFirstObject()
{
	return m_pFirstObject;
}

void CTestCollision::setSecondObject(CTestRigidBody * secondObject)
{
	assert(secondObject != NULL);
	m_pSecondObject = secondObject;
}

CTestRigidBody * CTestCollision::getSecondObject()
{
	return m_pSecondObject;
}

collision_status CTestCollision::CollisionOccurred()
{
	float distance;
	D3DXVECTOR3 distanceVector;
	collision_status collisionStatus = COLLISION_NONE;

	distanceVector = m_pFirstObject->GetPosition() - m_pSecondObject->GetPosition();
	distance = fabs(D3DXVec3Length(&distanceVector)) - m_pFirstObject->GetBoundingSphere() - m_pSecondObject->GetBoundingSphere();
	//cout << distance << endl;
	if (-0.001f < distance  && distance < 0.001f)
	{
		collisionStatus = COLLISION_TOUCHING;
	}
	else if (distance < 0.0f)
	{
		collisionStatus = COLLISTION_OVERLAPPING;
	}
	//else if (distance < 0.0f)
	//{
	//	collisionStatus = COLLISTION_OVERLAPPING;
	//}
	return collisionStatus;
}

bool CTestCollision::CalculateReactions()
{
	float averageElasticity = (m_pFirstObject->GetElasticity() + m_pSecondObject->GetElasticity()) / 2.0f;
	D3DXVECTOR3 relativeVelocity = m_pFirstObject->GetAngularVelocity() - m_pSecondObject->GetAngularVelocity();
	D3DXVECTOR3 numerator = -1 * relativeVelocity * (averageElasticity + 1);

	D3DXVECTOR3 unitNormal = m_pFirstObject->GetPosition() - m_pSecondObject->GetPosition();
	D3DXVec3Normalize(&unitNormal, &unitNormal);

	D3DXVECTOR3 forcePosition2 = unitNormal * m_pSecondObject->GetBoundingSphere();
	
	D3DXVECTOR3 tempVector;
	D3DXVec3Cross(&tempVector, &forcePosition2, &unitNormal);

	tempVector.x = (tempVector.x / m_pSecondObject->GetRotationInertia().x);
	tempVector.y = (tempVector.y / m_pSecondObject->GetRotationInertia().y);
	tempVector.z = (tempVector.z / m_pSecondObject->GetRotationInertia().z);

	D3DXVec3Cross(&tempVector, &tempVector, &forcePosition2);

	float part1 = D3DXVec3Dot(&unitNormal, &tempVector);
	
	unitNormal *= -1;
	D3DXVECTOR3 forcePosition1 = unitNormal * m_pFirstObject->GetBoundingSphere();
	D3DXVec3Cross(&tempVector, &forcePosition1, &unitNormal);
	
	tempVector.x = (tempVector.x / m_pFirstObject->GetRotationInertia().x);
	tempVector.y = (tempVector.y / m_pFirstObject->GetRotationInertia().y);
	tempVector.z = (tempVector.z / m_pFirstObject->GetRotationInertia().z);

	D3DXVec3Cross(&tempVector, &tempVector, &forcePosition1);

	float part2 = D3DXVec3Dot(&unitNormal, &tempVector);

	float denominator = 1 / m_pFirstObject->getMass() + 1 / m_pSecondObject->getMass() + part2 + part1;

	CTestForce impulseForce;
	impulseForce.SetForceVector(numerator / denominator);
	impulseForce.SetForceLocation(forcePosition1);
	m_pFirstObject->setImpulseForce(impulseForce);

	impulseForce.SetForceVector(-1 * impulseForce.GetForceVector());
	m_pSecondObject->setImpulseForce(impulseForce);

	return true;
}