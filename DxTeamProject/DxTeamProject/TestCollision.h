#pragma once

class CTestRigidBody;

enum collision_status
{
	COLLISION_NONE,
	COLLISION_TOUCHING,
	COLLISTION_OVERLAPPING
};

class CTestCollision
{
private:
	CTestRigidBody* m_pFirstObject;
	CTestRigidBody* m_pSecondObject;
public:
	~CTestCollision();
	CTestCollision();
	CTestCollision(CTestRigidBody* firstObject, CTestRigidBody* secondObject);

	void setFirstObject(CTestRigidBody* firstObject);
	CTestRigidBody* getFirstObject();
	void setSecondObject(CTestRigidBody* secondObject);
	CTestRigidBody* getSecondObject();

	collision_status CollisionOccurred();
	bool CalculateReactions();
};

