#pragma once
#include "PObject.h"

class IObject;
class CGimmick;
class CBox;
class CCylinder;

class CSphere : public PObject
{
public:
	CSphere();
	~CSphere();
protected:
	Synthesize(float, m_fRadius, Radius);
public:
	void Setup();
	void Setup(const ST_MapData & mapData);
	void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	//void Update(float duration);

	bool hasIntersected(CSphere * otherSphere);
	bool hasIntersected(CBox * otherBox);
	bool hasIntersected(CCylinder * otherCylinder);
	bool hasIntersected(CGimmick * otherIObject);
	bool hasIntersected(IObject * otherIObject);

	string GetName();
};

/// Delete Later...
/// Collide
//const static unsigned maxContacts = 256;
//Contact contacts[maxContacts];
//CollisionSphere collisionsphere;
//CollisionData cData;
//ContactResolver resolver;
//virtual void GenerateContacts();
//void CollideUpdate(float duration);
//virtual void AddForce(const D3DXVECTOR3 & force) {};
//virtual void ClearAccumulator() {};
//virtual void Integrate(float duration) {};
//virtual void RunPhysics(float duration) {};