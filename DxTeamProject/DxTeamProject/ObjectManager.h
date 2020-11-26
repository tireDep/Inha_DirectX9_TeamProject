#pragma once

class IObject;
class CObject;
class CRay;
#define		g_pObjectManager CObjectManager::GetInstance()

class CObjectManager
{
private:	
	SingleTone(CObjectManager);
	vector<CObject *> m_vecObject;
	vector<IObject *> m_vecIObject;

public:
	void AddObject(CObject* pObject);
	void RemoveObject(CObject* pObject);

	void AddObject(IObject* pObject);
	void RemoveObject(IObject* pObject);

	void Destroy();

	void Update(float duration , CHeight* pMap);
	void Update(CRay ray, D3DXCOLOR& objectcolor);
	void Render();

	void Update();
	vector<CObject *> GetVecObject();
	vector<IObject *> GetVecIObject();

private:
	void Update_PickCheck(const vector<bool>& vecIsPick, const vector<D3DXVECTOR3>& vecVPos);
};