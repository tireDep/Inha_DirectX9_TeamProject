#pragma once

enum class Collision_Status
{
	COLLISION_NONE,
	COLLISION_TOUCHING,
	COLLISION_OVERLAPPING
};

class CTestObjCollision
{
private:
	CObject* m_pFirstObject;
	CObject* m_pSecondObject;
public:
	~CTestObjCollision();
	CTestObjCollision();
	CTestObjCollision(CObject* firstObject, CObject* secondObject);

	void setFirstObejct(CObject* firstObject);
	CObject* getFirstObject();
	void setSeconObject(CObject* secondObject);
	CObject* getSecondObject();

	Collision_Status CollisionOccurred();
	bool CalculateReactions();
};