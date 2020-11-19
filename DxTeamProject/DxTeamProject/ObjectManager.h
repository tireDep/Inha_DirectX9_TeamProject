#pragma once

class CObject;
class CRay;
#define		g_pObjectManager CObjectManager::GetInstance()

class CObjectManager
{
private:	
	SingleTone(CObjectManager);
	vector<CObject *> m_vecObject;

public:
	void AddObject(CObject* pObject);
	void RemoveObject(CObject* pObject);
	void Destroy();

	void Update(CRay ray, D3DXCOLOR& objectcolor);
	void Render();

	vector<CObject *> GetVecObject();

private:
	void Update_PickCheck(const vector<bool>& vecIsPick, const vector<D3DXVECTOR3>& vecVPos);
};