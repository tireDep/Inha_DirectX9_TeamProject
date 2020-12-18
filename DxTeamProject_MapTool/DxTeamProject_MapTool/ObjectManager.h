#pragma once
#include "Singleton.h"
#include "Ray.h"

class IObject;

#define g_pObjectManager CObjectManager::GetInstance()

class CObjectManager : public CSingleton<CObjectManager>
{
private:
	vector<IObject *>	m_vecObject;
	int					m_sameNum = 0;

	int					m_preVecObjSize = 0;
	map<string, string> m_mapConditionName;
	// >> �����̸� ���� ���� ����
	// >> �� ������ �ε�� ����

	void SetCopyObject(int index);
	void SetReConditionName();

public:
	void AddObject(IObject* pObject);
	void RemoveObject(IObject* pObject);
	void RemoveCondition(string objectName);

	void Destroy();

	void Update();
	void Update(CRay * ray);
	void Render();

	void RemoveClickedObj();
	void CheckSameName();

	vector<IObject *> GetVecObject();

	IObject& GetIObject(int index);
	int GetVecSize();

	void SetSelectAllFalse();
	int GetSelectIndex();

	void CopyObject();

	string GetPickObjName();

	void SetPreVecSize(int set);

	int GetConditionIndex();

	D3DXVECTOR3 GetHighestY(int index);
	bool GetIsAnotherPos(D3DXVECTOR3 pos);
};
