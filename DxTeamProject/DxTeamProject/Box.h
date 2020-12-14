#pragma once
#include "PObject.h"

class IObject;
class CGimmick;
//class CSphere;
class CCylinder;

class CBox : public PObject
{
public:
	CBox();
	~CBox();
protected:
	Synthesize(float, m_fWidth, Width);
	Synthesize(float, m_fHeight, Height);
	Synthesize(float, m_fDepth, Depth);
public:
	void Setup();
	void Setup(const ST_MapData & mapData);
	void Update(float duration);
	//bool hasIntersected(CSphere & otherSphere);
	bool hasIntersected(CBox * otherBox);
	bool hasIntersected(CCylinder * otherCylinder);
	bool hasIntersected(IObject * otherIObject);
	//bool hasIntersected(CGimmick * otherIObject);
	
	string GetName();
	// OBB TEST
	COBB* GetOBB() { return m_pOBB; }
};

/// Delete Later...
/// Collide
//const static unsigned maxContacts = 32;
//Contact contacts[maxContacts];
//CollisionBox collisionbox;
//CollisionData cData;
//ContactResolver resolver;
//void Update(float duration);
//virtual void GenerateContacts();
//void CollideUpdate(float duration);
//virtual void Update(float duration) {};
//virtual void Update3D(float duration) {}
//virtual void Update(float duration, CHeight* pMap) {};
//virtual void SetPusingForce(D3DXVECTOR3 forcedirection) {};
//virtual void AddForce(const D3DXVECTOR3 & force) {};
//virtual void ClearAccumulator() {};
//virtual void Integrate(float duration) {};
//virtual void RunPhysics(float duration) {};
//virtual bool hasIntersected(CObject * otherobject) { return true; }
//virtual void CollisionOtherObject(CObject * otherobject) {};