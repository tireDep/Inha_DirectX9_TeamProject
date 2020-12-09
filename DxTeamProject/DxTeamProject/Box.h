#pragma once
#include "PObject.h"
#include "PSOBB.h"

class CSphere;
class CCylinder;
class IObject;
class CGimmick;

class CBox : public PObject
{
public:
	CBox();
	~CBox();
protected:
	Synthesize(float, m_fWidth, Width);
	Synthesize(float, m_fHeight, Height);
	Synthesize(float, m_fDepth, Depth);

	/// Collide
	//const static unsigned maxContacts = 32;
	//Contact contacts[maxContacts];
	//CollisionBox collisionbox;
	//CollisionData cData;
	//ContactResolver resolver;
public:
	void Setup();
	void Setup(const ST_MapData & mapData);
	string GetName();
	void Update(float duration);
	bool hasIntersected(CSphere & otherSphere);
	bool hasIntersected(CBox & otherBox);
	bool hasIntersected(CCylinder & otherCylinder);
	bool hasIntersected(IObject * otherIObject);
	bool hasIntersected(CGimmick * otherIObject);
	
	// OBB TEST
	CPSOBB* GetOBB() { return m_pOBB; }
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
};