#include "stdafx.h"
#include "Collision.h"
#include "Contact.h"

Collision::Collision()
	: m_pObject(NULL)
{
}

Collision::~Collision()
{
}

void Collision::calculateInternals()
{
	m_matWorld = m_pObject->GetmatWorld();
}

D3DXVECTOR3 Collision::getAxis(unsigned index) const
{
	D3DXVECTOR3 axis;
	if (index == 0)
		axis = D3DXVECTOR3(m_matWorld._11, m_matWorld._12, m_matWorld._13);
	else if(index == 1)
		axis = D3DXVECTOR3(m_matWorld._21, m_matWorld._22, m_matWorld._23);
	else if(index == 2)
		axis = D3DXVECTOR3(m_matWorld._31, m_matWorld._32, m_matWorld._33);
	else if(index == 3)
		axis = D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43);
	else 
		return D3DXVECTOR3(0, 0, 0);
	// return;

	return axis;
}

const D3DXMATRIXA16 & Collision::getWorldMatrix() const
{
	return m_matWorld;
}

bool IntersectionTests::SphereAndHalfSpace(const CollisionSphere & sphere, const CollisionPlane & plane)
{
	float ballDistance = D3DXVec3Dot(&plane.direction, &sphere.getAxis(3)) - sphere.radius;
	return ballDistance <= plane.offset;
}

bool IntersectionTests::SphereAndSphere(const CollisionSphere & one, const CollisionSphere & two)
{
	D3DXVECTOR3 midline = one.getAxis(3) - two.getAxis(3);
	return D3DXVec3LengthSq(&midline) < (one.radius + two.radius) * (one.radius + two.radius);
}

bool IntersectionTests::BoxAndHalfSpace(const CollisionBox & box, const CollisionPlane & plane)
{
	// Need To Modify?
	float projectedRadius =
		box.halfSize.x * fabsf(D3DXVec3Dot(&plane.direction, &box.getAxis(0))) +
		box.halfSize.y * fabsf(D3DXVec3Dot(&plane.direction, &box.getAxis(1))) +
		box.halfSize.z * fabsf(D3DXVec3Dot(&plane.direction, &box.getAxis(2)));

	float boxDistance = D3DXVec3Dot(&plane.direction, &box.getAxis(3)) - projectedRadius;
	return boxDistance <= plane.offset;
}

bool IntersectionTests::BoxAndBox(const CollisionBox & one, const CollisionBox & two)
{
	return false;
}

unsigned CollisionDetector::SphereAndHalfSpace(const CollisionSphere & sphere, const CollisionPlane & plane, CollisionData * data)
{
	if (data->contactsLeft <= 0) return 0;

	D3DXVECTOR3 position = sphere.getAxis(3);
	float ballDistance = D3DXVec3Dot(&plane.direction, &position) - sphere.radius - plane.offset;
	if (ballDistance >= 0) return 0;

	Contact* contact = data->contacts;
	contact->contactNormal = plane.direction;
	contact->penetration = -ballDistance;
	contact->contactPoint = position - plane.direction * (ballDistance + sphere.radius);
	contact->setObjectData(sphere.m_pObject, NULL, data->friction, data->restitution);

	data->addContacts(1);

	return 1;
}

unsigned CollisionDetector::SphereAndTrueSpace(const CollisionSphere & sphere, const CollisionPlane & plane, CollisionData * data)
{
	if (data->contactsLeft <= 0) return 0;

	D3DXVECTOR3 position = sphere.getAxis(3);
	float centerDistance = D3DXVec3Dot(&plane.direction, &position) - plane.offset;
	if (centerDistance * centerDistance > sphere.radius * sphere.radius)
		return 0;

	D3DXVECTOR3 normal = plane.direction;
	float penetration = -centerDistance;
	if (centerDistance < 0)
	{
		normal *= -1;
		penetration = -penetration;
	}
	penetration += sphere.radius;

	Contact* contact = data->contacts;
	contact->contactNormal = normal;
	contact->penetration = penetration;
	contact->contactPoint = position - plane.direction * centerDistance;
	contact->setObjectData(sphere.m_pObject, NULL, data->friction, data->restitution);

	data->addContacts(1);
	return 1;
}

unsigned CollisionDetector::SphereAndSphere(const CollisionSphere & one, const CollisionSphere & two, CollisionData * data)
{
	if (data->contactsLeft <= 0) return 0;

	D3DXVECTOR3 positionOne = one.getAxis(3);
	D3DXVECTOR3 positionTwo = two.getAxis(3);

	D3DXVECTOR3 midline = positionOne - positionTwo;
	float size = D3DXVec3LengthSq(&midline);

	if(size <= 0.0f || size >= one.radius + two.radius)
		return 0;

	D3DXVECTOR3 normal = midline * (((float)1.0) / size);

	Contact* contact = data->contacts;
	contact->contactNormal = normal;
	contact->contactPoint = positionOne + midline * (float)0.5;
	contact->penetration = (one.radius + two.radius - size);
	contact->setObjectData(one.m_pObject, two.m_pObject, data->friction, data->restitution);

	data->addContacts(1);
	return 1;
}

unsigned CollisionDetector::BoxAndHalfSpace(const CollisionBox & box, const CollisionPlane & plane, CollisionData * data)
{
	if (data->contactsLeft <= 0) return 0;
	if(!IntersectionTests::BoxAndHalfSpace(box, plane))
		return 0;

	static float mults[8][3] = { 
	{ 1, 1, 1 },{ -1, 1, 1 },{ 1,-1, 1 },{ -1,-1, 1 },
	{ 1, 1,-1 },{ -1, 1,-1 },{ 1,-1,-1 },{ -1,-1,-1 } };

	Contact* contact = data->contacts;
	unsigned contactUsed = 0;
	for (unsigned i = 0; i < 8; i++)
	{
		D3DXVECTOR3 vertexPos(mults[i][0], mults[i][1], mults[i][2]);
		vertexPos.x *= box.halfSize.x;
		vertexPos.y *= box.halfSize.y;
		vertexPos.z *= box.halfSize.z;

		// need to modify?
		D3DXVec3TransformCoord(&vertexPos, &vertexPos, &box.m_matWorld);

		float vertexDistance = D3DXVec3Dot(&vertexPos, &plane.direction);
		
		if (vertexDistance <= plane.offset)
		{
			contact->contactPoint = plane.direction;
			contact->contactPoint *= (vertexDistance - plane.offset);
			contact->contactPoint += vertexPos;
			contact->contactNormal = plane.direction;
			contact->penetration = plane.offset - vertexDistance;
			
			contact->setObjectData(box.m_pObject, NULL, data->friction, data->restitution);
			contact++;
			contactUsed++;
			if (contactUsed == (unsigned)data->contactsLeft) return contactUsed;
		}
	}
	data->addContacts(contactUsed);
	return contactUsed;
}

unsigned CollisionDetector::BoxAndSphere(const CollisionBox & box, const CollisionSphere & sphere, CollisionData * data)
{
	D3DXVECTOR3 center = sphere.getAxis(3);
	// need to modify?
	D3DXVECTOR3 realCenter;
	D3DXVec3TransformNormal(&realCenter, &center, &box.m_matWorld);

	if (fabsf(realCenter.x) - sphere.radius > box.halfSize.x ||
		fabsf(realCenter.y) - sphere.radius > box.halfSize.y ||
		fabsf(realCenter.z) - sphere.radius > box.halfSize.z)
		return 0;

	D3DXVECTOR3 closestPt(0, 0, 0);
	float distance;

	distance = realCenter.x;
	if (distance > box.halfSize.x) distance = box.halfSize.x;
	if (distance < -box.halfSize.x) distance = -box.halfSize.x;
	closestPt.x = distance;

	distance = realCenter.y;
	if (distance > box.halfSize.y) distance = box.halfSize.y;
	if (distance < -box.halfSize.y) distance = -box.halfSize.y;
	closestPt.y = distance;

	distance = realCenter.z;
	if (distance > box.halfSize.z) distance = box.halfSize.z;
	if (distance < -box.halfSize.z) distance = -box.halfSize.z;
	closestPt.z = distance;

	D3DXVECTOR3 tmp = closestPt - realCenter;
	distance = D3DXVec3LengthSq(&tmp);
	if (distance > sphere.radius * sphere.radius) return 0;

	D3DXVECTOR3 closestPtWorld;
	D3DXVec3TransformCoord(&closestPtWorld, &closestPt, &box.m_matWorld);

	Contact* contact = data->contacts;
	tmp = closestPtWorld - center;
	D3DXVec3Normalize(&tmp, &tmp);
	contact->contactNormal = tmp;
	contact->contactPoint = closestPtWorld;
	contact->penetration = sphere.radius - sqrtf(distance);
	contact->setObjectData(box.m_pObject, sphere.m_pObject, data->friction, data->restitution);

	data->addContacts(1);
	return 1;
}

unsigned CollisionDetector::BoxAndBox(const CollisionBox & one, const CollisionBox & two, CollisionData * data)
{
	return 0;
}

unsigned CollisionDetector::BoxAndPoint(const CollisionBox & box, const D3DXVECTOR3 & point, CollisionData * data)
{
	return 0;
}