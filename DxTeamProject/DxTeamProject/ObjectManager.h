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
// 	float m_vScale;
// 	CFrustum* m_frustum;
// 	thread* m_thread;
// 	CRITICAL_SECTION m_cs;
// 	bool m_isThreadRun;
// 	bool m_IsIn;
//  multimap<vector<IObject*>, bool>	m_mapObject;

	multimap<int, vector<CObject*>>	m_mapObject;	// >> 맵 위치, 맵에 존재하는 오브젝트들
	vector<bool>					m_vecIsRenderState;	// >> 맵 랜더 상태
	int								m_IObjCnt = 0;		// >> 오브젝트 카운트
	Synthesize(int, m_nowMapPos, NowMapPos);		// >> 플레이어가 현재 위치한 맵 위치
	// >> 


	bool		  ResetCube;

	//Keep (이어하기)
	vector<D3DXVECTOR3*> SaveData;

	DWORD DoFtoDw(float f);
	
public:
	//이어하기
	bool	KeepGoing;

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
	CObject& GetVecObjectIndex(int index) { return *m_vecObject[index]; }

	void Update(CRay ray);
	void Update(CRay ray, D3DXCOLOR& objectcolor);		// Color Change
	void UpdateLand(float duration);					// PObject Physics
	void Update(float duration);						// IObject(Gimmick) Physics		// Integration...
	void PreUpdate(float duration = 0.001f);			// PreUpdate(setOBB BOX)

	void Collide(float duration);						// Collision

	void CollisionSphereToSphere(CSphere* one, CSphere* two, float duration);
	void CollisionSphereToBox(CSphere* one, PObject* two, float duration);
	void CollisionBoxToBox(PObject* one, PObject* two, float duration);
	void CollisionBoxToTile(PObject* pObject, IObject* iObject, float duration);
	//void CollisionSphereToIObject(CSphere* one, IObject* two, float duration);
	//void CollisionIObject(PObject* pObject, IObject* iObject, float duration);

	void Reset();

	void Render(const D3DXVECTOR3& camEye);
	void RenderOBBBox();

	void Destroy();

	// >> mapTest
	// int GetMapVecSize(int mapIndex);
	// void UpdateNewMap(CFrustum* frustum);
	// void Thread_CalcNewMap();
	void AddMap();
	void RemoveMap();
	// IObject& GetIObject(int mapIndex, int vectorIndex);
	//
	void CalcNowPositionIndex(const D3DXVECTOR3& m_characterPos);
	void SetIsRenderState();
	int GetVecMapObjCnt();
	vector<CObject *> GetMapVecCObject();	// << 오브젝트 반환
	PObject* GetPObjectIndex(int index);
	IObject* GetIObjectIndex(int index);

	void AllUpdate();

private:
	void Update_PickCheck(const vector<bool>& vecIsPick, const vector<D3DXVECTOR3>& vecVPos);
};

/// Delete Later...
//void Update(float duration , CHeight* pMap);		// 3D Physics
//void Update3D(float duration);
//void Collide(float duration);
//void GenerateContacts();
//void HandleOverlapping(float timeIncrement, int firstobject, int secondobject, CTestObjCollision& theCollision);
//void CollisionPObject(PObject* one, PObject* two, float duration);