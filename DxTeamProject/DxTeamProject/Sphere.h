#pragma once
#include "PObject.h"

class CSphere : public PObject
{
public:
	CSphere();
	~CSphere();
protected:
	Synthesize(float, m_fRadius, Radius);
	const static unsigned maxContacts = 256;
	Contact contacts[maxContacts];
	CollisionSphere collisionsphere;
	CollisionData cData;
	ContactResolver resolver;
public:
	void Setup();
	void Setup(const ST_MapData & mapData);

	void Update(float duration);
	virtual void GenerateContacts();
	void CollideUpdate(float duration);

	void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);

	virtual void AddForce(const D3DXVECTOR3 & force) {};
	virtual void ClearAccumulator() {};
	virtual void Integrate(float duration) {};
	virtual void RunPhysics(float duration) {};

	string GetName();
};