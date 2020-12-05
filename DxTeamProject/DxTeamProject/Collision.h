#pragma once

class IntersectionTests;
class CollisionDetector;

class Collision
{
public:
	friend class IntersectionTests;
	friend class CollisionDetector;
protected:
	D3DXMATRIXA16 m_matWorld;
public:
	CObject* m_pObject; 
	Collision();
	~Collision();

	void calculateInternals();
	D3DXVECTOR3 getAxis(unsigned index) const;
	const D3DXMATRIXA16& getWorldMatrix() const;
};

class CollisionPlane : public Collision
{
public:
	D3DXVECTOR3 direction;
	float offset;
};

class CollisionSphere : public Collision
{
public:
	float radius;
};

class CollisionBox : public Collision
{
public:
	D3DXVECTOR3 halfSize;
};

class IntersectionTests
{
public:
	static bool SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane);
	static bool SphereAndSphere(const CollisionSphere &one, const CollisionSphere &two);
	static bool BoxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane);
	static bool BoxAndBox(const CollisionBox &one, const CollisionBox &two);
};

struct CollisionData
{
	Contact *contactArray;
	Contact *contacts;
	
	int contactsLeft;
	unsigned contactCount;

	float friction;
	float restitution;
	float tolerance;

	bool hasMoreContacts() { return contactsLeft > 0; }
	void reset(unsigned maxContacts)
	{
		contactsLeft = maxContacts;
		contactCount = 0;
		contacts = contactArray;
	}
	void addContacts(unsigned count)
	{
		contactsLeft -= count;
		contactCount += count;

		//contacts += count;
	}
};

class CollisionDetector
{
public:
	static unsigned SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *data);
	static unsigned SphereAndTrueSpace(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *data);
	static unsigned SphereAndSphere(const CollisionSphere &one,	const CollisionSphere &two,	CollisionData *data);

	static unsigned BoxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane, CollisionData *data);
	static unsigned BoxAndSphere(const CollisionBox &box, const CollisionSphere &sphere, CollisionData *data);
	static unsigned BoxAndBox(const CollisionBox &one, const CollisionBox &two,	CollisionData *data);
	static unsigned BoxAndPoint(const CollisionBox &box, const D3DXVECTOR3 &point, CollisionData *data);
};