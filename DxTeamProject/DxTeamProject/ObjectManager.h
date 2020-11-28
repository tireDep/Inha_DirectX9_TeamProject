#pragma once

class IObject;
class CObject;
class CRay;
class CPSOBB;
#define		g_pObjectManager CObjectManager::GetInstance()

class CObjectManager
{
private:	
	SingleTone(CObjectManager);
	vector<CObject *> m_vecObject;
	vector<IObject *> m_vecIObject;
	vector<CPSOBB *> m_vecOBBBox;
public:
	void AddObject(CObject* pObject);
	void RemoveObject(CObject* pObject);

	void AddObject(IObject* pObject);
	void RemoveObject(IObject* pObject);

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

private:
	void Update_PickCheck(const vector<bool>& vecIsPick, const vector<D3DXVECTOR3>& vecVPos);
};