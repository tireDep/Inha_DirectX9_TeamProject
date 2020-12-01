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

#define		g_pObjectManager CObjectManager::GetInstance()

class CObjectManager
{
private:	
	SingleTone(CObjectManager);
	vector<CObject *> m_vecObject;
	vector<IObject *> m_vecIObject;
	vector<CPSOBB *> m_vecOBBBox;
	vector<COBB *> m_OBB;
	// >> mapTest
	multimap<vector<IObject*>, bool> m_mapObject;
	CFrustum* m_frustum;
	thread* m_thread;
	CRITICAL_SECTION m_cs;
	bool m_isThreadRun;
	bool m_IsIn;

public:
	void AddObject(CObject* pObject);
	void RemoveObject(CObject* pObject);

	void AddObject(IObject* pObject);
	void RemoveObject(IObject* pObject);

	void AddTileOBB(COBB* OBBbox);

	void AddOBBbox(CPSOBB* OBBBox);
	void RemoveObject(CPSOBB* OBBBox);

	void Destroy();

	void Update();										// Collision
	void Update(float duration);						// 2D Physics
	void Update(float duration , CHeight* pMap);		// 3D Physics
	void Update(CRay ray, D3DXCOLOR& objectcolor);		// Color Change
	void Render();
	void RenderOBBBox();

	vector<CObject *> GetVecObject();
	vector<IObject *> GetVecIObject();

	COBB* GetTileOBB() {return m_OBB[0];}

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