#include "stdafx.h"
#include "TestObjCollision.h"

CTestObjCollision::CTestObjCollision()
	: m_pFirstObject(NULL)
	, m_pSecondObject(NULL)
{
}

CTestObjCollision::~CTestObjCollision()
{
}

CTestObjCollision::CTestObjCollision(CObject * firstObject, CObject * secondObject)
{
	assert(firstObject  != NULL);
	assert(secondObject != NULL);
	m_pFirstObject = firstObject;
	m_pSecondObject = secondObject;
}

void CTestObjCollision::setFirstObejct(CObject * firstObject)
{
	assert(firstObject != NULL);
	m_pFirstObject = firstObject;
}

CObject * CTestObjCollision::getFirstObject()
{
	return m_pFirstObject;
}

void CTestObjCollision::setSeconObject(CObject * secondObject)
{
	assert(secondObject != NULL);
	m_pSecondObject = secondObject;
}

CObject * CTestObjCollision::getSecondObject()
{
	return m_pSecondObject;
}

Collision_Status CTestObjCollision::CollisionOccurred()
{
	float distance;
	D3DXVECTOR3 distanceVector;
	Collision_Status collisionStatus = Collision_Status::COLLISION_NONE;

	distanceVector = m_pFirstObject->GetPosition() - m_pSecondObject->GetPosition();
	distance = fabs(D3DXVec3Length(&distanceVector) - m_pFirstObject->GetBoundingSphere() - m_pSecondObject->GetBoundingSphere());

	// need to modify?
	if (CloseToZero(distance))
	{
		collisionStatus = Collision_Status::COLLISION_TOUCHING;
	}
	else if (distance < 0.0f)
	{
		collisionStatus = Collision_Status::COLLISION_OVERLAPPING;
	}
	return collisionStatus;
}

bool CTestObjCollision::CalculateReactions()
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

	float denominator = m_pFirstObject->GetInverseMass() + m_pSecondObject->GetInverseMass() + part2 + part1;

	m_pFirstObject->SetForceVector(numerator / denominator);
	m_pFirstObject->SetForceLocation(forcePosition1);

	m_pSecondObject->SetForceVector(-1 * numerator / denominator);
	// need to modify?
	m_pSecondObject->SetForceLocation(forcePosition1);

	return true;
}