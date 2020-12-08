#pragma once

// >> mapTest
#include <process.h>
#include <thread>
#include <Windows.h>
#include "Frustum.h"

class IObject;
class CObject;
class CRay;
class CPSOBB;
class COBB;
class CTestObjCollision;
class PObject;

// Collide
#include "Contact.h"
#include "Collision.h"

#define		g_pObjectManager CObjectManager::GetInstance()

class CObjectManager
{
private:	
	SingleTone(CObjectManager);
	vector<CObject *> m_vecObject;
	vector<IObject *> m_vecIObject;
	vector<CPSOBB *> m_vecOBBBox;
	vector<PObject*> m_vecPObject;

	// >> mapTest
	float m_vScale;
	multimap<vector<IObject*>, bool> m_mapObject;
	CFrustum* m_frustum;
	thread* m_thread;
	CRITICAL_SECTION m_cs;
	bool m_isThreadRun;
	bool m_IsIn;

	//collide
	//const static unsigned maxContacts = 256;
	//Contact contacts[maxContacts];
	//CollisionData cData;
	//ContactResolver resolver;
public:
	void AddObject(CObject* pObject);
	void RemoveObject(CObject* pObject);

	void AddObject(IObject* pObject);
	void RemoveObject(IObject* pObject);

	void AddObject(PObject* pObject);
	void RemoveObject(PObject* pObject);

	void AddTileOBB(COBB* OBBbox);
	void SetScale(float scale);
	float GetScale();
	
	void AddOBBbox(CPSOBB* OBBBox);
	void RemoveObject(CPSOBB* OBBBox);

	void Destroy();

	void Update(CRay ray, D3DXCOLOR& objectcolor);		// Color Change
	void Update();										// Collision
	void UpdateLand(float duration);					// Land
	void Update(float duration);						// Physics
	//void Update(float duration , CHeight* pMap);		// 3D Physics
	//void Update3D(float duration);
	void Collide(float duration);
	void GenerateContacts();
	//void HandleOverlapping(float timeIncrement, int firstobject, int secondobject, CTestObjCollision& theCollision);

	void Render();
	void RenderOBBBox();

	vector<CObject *> GetVecObject();
	vector<IObject *> GetVecIObject();
	vector<PObject *> GetVecPObejct();

	COBB* GetTileOBB();
	vector<COBB*> m_OBB;
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