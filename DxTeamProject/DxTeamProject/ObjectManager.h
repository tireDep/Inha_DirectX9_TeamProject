#pragma once

// >> mapTest
#include <process.h>
#include <thread>
#include <Windows.h>
#include "Frustum.h"

class CRay;

class CObject;
class PObject;
class IObject;
class COBB;
class CGimmick;
class CSphere;
class CBox;
class CCylinder;

// Collide
//#include "Contact.h"
//#include "Collision.h"

#define		g_pObjectManager CObjectManager::GetInstance()

class CObjectManager
{
private:	
	SingleTone(CObjectManager);

	vector<CObject *>	m_vecObject;
	vector<PObject*>	m_vecPObject;
	vector<IObject *>	m_vecIObject;
	vector<COBB *>		m_vecOBBBox;
	// Integration... 
	vector<CGimmick*>	m_vecGimmick;
	vector<CSphere*>	m_vecSphere;
	vector<CBox*>		m_vecBox;
	vector<CCylinder*>  m_vecCylinder;

	// >> mapTest
	float m_vScale;
	multimap<vector<IObject*>, bool> m_mapObject;
	CFrustum* m_frustum;
	thread* m_thread;
	CRITICAL_SECTION m_cs;
	bool m_isThreadRun;
	bool m_IsIn;



	/// KT Reset
	bool		  ResetCube;

	//collide
	//const static unsigned maxContacts = 256;
	//Contact contacts[maxContacts];
	//CollisionData cData;
	//ContactResolver resolver;
public:
	void AddObject(CObject* Object)			{ m_vecObject.push_back(Object); }
	void AddObject(PObject* pObject)		{ m_vecPObject.push_back(pObject); }
	void AddObject(IObject* iObject)		{ m_vecIObject.push_back(iObject); }
	void AddOBBbox(COBB* OBBBox)			{ m_vecOBBBox.push_back(OBBBox); }
	void AddGimmick(CGimmick* Gimmick)		{ m_vecGimmick.push_back(Gimmick); }
	void AddSphere(CSphere* Sphere)			{ m_vecSphere.push_back(Sphere); }
	void AddBox(CBox* Box)					{ m_vecBox.push_back(Box); }
	void AddCylinder(CCylinder* Cylinder)	{ m_vecCylinder.push_back(Cylinder); }

	void RemoveObject(CObject* Object);
	void RemoveObject(PObject* pObject);
	void RemoveObject(IObject* iObject);
	void RemoveObject(COBB* OBBBox);
	void RemoveObject(CGimmick* Gimmick);

	vector<CObject *> GetVecObject()	{ return m_vecObject; }
	vector<PObject *> GetVecPObejct()	{ return m_vecPObject; }
	vector<IObject *> GetVecIObject()	{ return m_vecIObject; }
	vector<CGimmick*> GetVecGimmickObject() { return m_vecGimmick; }
	void Update(CRay ray, D3DXCOLOR& objectcolor);		// Color Change
	void UpdateLand(float duration);					// PObject Physics
	void Update(float duration);						// IObject(Gimmick) Physics		// Integration...

	void Collide(float duration);						// Collision
	void CollisionPObject(PObject* one, PObject* two, float duration);
	void CollisionSphereToSphere(CSphere* one, CSphere* two, float duration);
	void CollisionSphereToBox(CSphere* one, PObject* two, float duration);
	void CollisionBoxToBox(PObject* one, PObject* two, float duration);
	void CollisionSphereToIObject(CSphere* one, IObject* two, float duration);
	void CollisionIObject(PObject* pObject, IObject* iObject, float duration);
	void CollisionBoxToTile(PObject* pObject, IObject* iObject, float duration);

	/// KT Reset
	void Reset();

	void Render();
	void RenderOBBBox();

	void Destroy();

	//==========================================================

	void AddTileOBB(COBB* OBBbox);
	void SetScale(float scale);
	float GetScale();
	
	vector<COBB*> m_OBB;
	COBB* GetvecOBB();
	COBB* GetTileOBB();

	// >> mapTest
	void AddMap();
	void RemoveMap();
	int GetMapVecSize(int mapIndex);
	IObject& GetIObject(int mapIndex, int vectorIndex);
	void UpdateNewMap(CFrustum* frustum);
	void Thread_CalcNewMap();
private:
	void Update_PickCheck(const vector<bool>& vecIsPick, const vector<D3DXVECTOR3>& vecVPos);
};

/// Delete Later...
//void Update(float duration , CHeight* pMap);		// 3D Physics
//void Update3D(float duration);
//void Collide(float duration);
//void GenerateContacts();
//void HandleOverlapping(float timeIncrement, int firstobject, int secondobject, CTestObjCollision& theCollision);