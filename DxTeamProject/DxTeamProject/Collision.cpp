#include "stdafx.h"
#include "Collision.h"

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
	return D3DXVECTOR3(0, 0, 0);
	//D3DXVECTOR3 axis;
	//if (index == 0)
	//	axis = D3DXVECTOR3(m_matWorld._11, m_matWorld._12, m_matWorld._13);
	//else if(index == 1)
	//	axis = D3DXVECTOR3(m_matWorld._21, m_matWorld._22, m_matWorld._23);
	//else if(index == 2)
	//	axis = D3DXVECTOR3(m_matWorld._31, m_matWorld._32, m_matWorld._33);
	//else if(index == 3)
	//	axis = D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43);
	//else return;

	//return axis;
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
