#include "stdafx.h"
#include "Object.h"
#include "IObject.h"
#include "PSOBB.h"
#include "ObjectManager.h"
#include "CHeight.h"
#include "OBB.h"
#include "TestObjCollision.h"

CObjectManager::CObjectManager() : 
	m_frustum(NULL),
	m_thread(NULL)
{
	InitializeCriticalSection(&m_cs);
}

CObjectManager::~CObjectManager()
{
	// >> mapTest
	RemoveMap();

	if (m_thread != NULL)
	{
		if (m_thread->joinable())
			m_thread->join();
	}
	SafeDelete(m_thread);
}

void CObjectManager::AddObject(CObject * pObject)
{
	m_vecObject.push_back(pObject);
}

void CObjectManager::RemoveObject(CObject * pObject)
{
	vector<CObject*>::iterator it;
	for (it = m_vecObject.begin(); it != m_vecObject.end();)
	{
		if (*it == pObject)
		{
			CObject* temp = *it;
			it = m_vecObject.erase(it);
			delete temp;
			return;
		}
		else
			it++;
	}
}

void CObjectManager::AddObject(IObject * pObject)
{
	m_vecIObject.push_back(pObject);
}

void CObjectManager::RemoveObject(IObject * pObject)
{
	vector<IObject*>::iterator it;
	for (it = m_vecIObject.begin(); it != m_vecIObject.end();)
	{
		if (*it == pObject)
		{
			IObject* temp = *it;
			it = m_vecIObject.erase(it);
			delete temp;
			return;
		}
		else
			it++;
	}
}

void CObjectManager::SetScale(float scale)
{
	m_vScale = scale;
}

float CObjectManager::GetScale()
{
   return m_vScale;
}

void CObjectManager::AddOBBbox(CPSOBB * OBBBox)
{
	m_vecOBBBox.push_back(OBBBox);
}

void CObjectManager::RemoveObject(CPSOBB * OBBBox)
{
	vector<CPSOBB*>::iterator it;
	for (it = m_vecOBBBox.begin(); it != m_vecOBBBox.end();)
	{
		if (*it == OBBBox)
		{
			CPSOBB* temp = *it;
			it = m_vecOBBBox.erase(it);
			delete temp;
			return;
		}
		else
			it++;
	}
}

void CObjectManager::AddMap()
{
	m_mapObject.insert(pair<vector<IObject*>, bool>(m_vecIObject, false));

	// m_vecIObject.clear();
	// >> �׽�Ʈ �Ϸ� �� ����
}

void CObjectManager::RemoveMap()
{
	multimap<vector<IObject*>, bool>::iterator it;
	for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
	{
		for (int i = 0; i < it->first.size(); i++)
		{
			if (&it->first != NULL)
				SafeDelete(it->first[i]);
		}
	} // >> : for

	m_mapObject.clear();
}

int CObjectManager::GetMapVecSize(int mapIndex)
{
	int num = 0;
	multimap<vector<IObject*>, bool>::iterator it;
	for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
	{
		if (mapIndex != num)
			continue;

		return it->first.size();
	}
}

IObject & CObjectManager::GetIObject(int mapIndex, int vectorIndex)
{
	int num = 0;
	multimap<vector<IObject*>, bool>::iterator it;
	for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
	{
		if (mapIndex != num)
			continue;

		return *it->first[vectorIndex];
	}
}

void CObjectManager::UpdateNewMap(CFrustum * frustum)
{
	// todo : thread
	m_frustum = frustum;
	if (m_thread == NULL)
	{
		m_thread = new thread(&CObjectManager::Thread_CalcNewMap, this);
		// cout << "thread" << endl;
	}
	else
	{
		if (m_thread->joinable()) 
			m_thread->join();

		m_thread = NULL;
		// cout << "threadEnd" << endl;
	}
}

void CObjectManager::Thread_CalcNewMap()
{
	EnterCriticalSection(&m_cs);
	bool check = false;
	multimap<vector<IObject*>, bool>::iterator it;
	for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
	{
		check = false;

		for (int i = 0; i < it->first.size(); i++)
		{
			float radius = 0;
			radius = it->first[0]->GetScale().x > it->first[0]->GetScale().y ? it->first[0]->GetScale().x : it->first[0]->GetScale().y;
			radius = radius > it->first[0]->GetScale().z ? radius : it->first[0]->GetScale().z;

			if (m_frustum->IsInFrustum(it->first[i]->GetTranslate(), radius))
			{
				it->second = true;
				check = true;
				// >> todo
				// ���� �ֺ� �ε��� true, �ƴϸ� false ó��
				// �� ����, ���� ũ�� �˾ƾ� ��
				// 3*3 ���� ����?
			}
		}

		if (!check)
			it->second = false;
	}
	LeaveCriticalSection(&m_cs);
}

void CObjectManager::Destroy()
{
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Release();
}

void CObjectManager::Update(float duration)
{
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Update(duration);
}

void CObjectManager::Update(float duration, CHeight* pMap)
{
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Update(duration , pMap);
}

void CObjectManager::Update3D(float duration)
{
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Update3D(duration);
}

void CObjectManager::UpdateLand(float duration)
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->UpdateLand(duration);
		m_vecObject[i]->Update3D(duration);
	}
}

void CObjectManager::UpdateCollide(float duration)
{
	CObjectManager::Collide(duration);
}

void CObjectManager::Update(CRay ray, D3DXCOLOR& objectcolor)
{
	vector<bool> vecIsPick;
	vector<D3DXVECTOR3> vecVPos;
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->Update(ray, objectcolor, vecIsPick, vecVPos);
	}
	Update_PickCheck(vecIsPick, vecVPos);
}

void CObjectManager::Collide(float duration)
{
	for (int hittee = 0; hittee < m_vecObject.size(); hittee++)
	{
		for (int hitter = 0; hitter < m_vecObject.size(); hitter++)
		{
			if (hittee >= hitter)
				continue;
			CTestObjCollision theCollision(m_vecObject[hittee], m_vecObject[hitter]);
			Collision_Status collisionOccurred = theCollision.CollisionOccurred();
			switch (collisionOccurred)
			{
				case Collision_Status::COLLISION_TOUCHING:
					theCollision.CalculateReactions();
					break;
				case Collision_Status::COLLISION_OVERLAPPING:
					HandleOverlapping(duration, hittee, hitter, theCollision);
					break;
				case Collision_Status::COLLISION_NONE:
					break;
				default:
					break;
			}
		}
	}
}

void CObjectManager::HandleOverlapping(float timeIncrement, int firstobject, int secondobject, CTestObjCollision & theCollision)
{
	float changeInTime = timeIncrement;

	Collision_Status collisionOccured = Collision_Status::COLLISION_OVERLAPPING;
	for (bool done = false; (!done) && (!CloseToZero(changeInTime));)
	{
		switch (collisionOccured)
		{
			case Collision_Status::COLLISION_OVERLAPPING:
				{
					CObject* firstObject;
					CObject* secondObject;
					firstObject = m_vecObject[firstobject];
					secondObject = m_vecObject[secondobject];

					D3DXVECTOR3 tempVector = firstObject->GetAngularVelocity();
					tempVector *= -1;
					firstObject->SetAngularVelocity(tempVector);
					tempVector = firstObject->GetLinearVelocity();
					tempVector *= -1;
					firstObject->SetLinearVelocity(tempVector);
					firstObject->SetForceVector(firstObject->GetForceVector() * -1);

					tempVector = secondObject->GetAngularVelocity();
					tempVector *= -1;
					secondObject->SetAngularVelocity(tempVector);
					tempVector = secondObject->GetLinearVelocity();
					tempVector *= -1;
					secondObject->SetLinearVelocity(tempVector);
					secondObject->SetForceVector(secondObject->GetForceVector() * -1);

					firstObject->Update(changeInTime);
					secondObject->Update(changeInTime);

					changeInTime /= 2;

					tempVector = firstObject->GetAngularVelocity();
					tempVector *= -1;
					firstObject->SetAngularVelocity(tempVector);
					tempVector = firstObject->GetLinearVelocity();
					tempVector *= -1;
					firstObject->SetLinearVelocity(tempVector);
					firstObject->SetForceVector(firstObject->GetForceVector() * -1);

					tempVector = secondObject->GetAngularVelocity();
					tempVector *= -1;
					secondObject->SetAngularVelocity(tempVector);
					tempVector = secondObject->GetLinearVelocity();
					tempVector *= -1;
					secondObject->SetLinearVelocity(tempVector);
					secondObject->SetForceVector(secondObject->GetForceVector() * -1);

					firstObject->Update(changeInTime);
					secondObject->Update(changeInTime);

					m_vecObject[firstobject] = firstObject;
					m_vecObject[secondobject] = secondObject;
					collisionOccured = theCollision.CollisionOccurred();
				}
				break;
			case Collision_Status::COLLISION_TOUCHING:
				theCollision.CalculateReactions();
				done = true;
				break;
			case Collision_Status::COLLISION_NONE:
				m_vecObject[firstobject]->Update(changeInTime);
				m_vecObject[secondobject]->Update(changeInTime);
				collisionOccured = theCollision.CollisionOccurred();
				break;
			default:
				break;
		}	// << : switch
	}	// << : for
	if (CloseToZero(changeInTime))
	{
		theCollision.CalculateReactions();
		m_vecObject[firstobject]->Update(changeInTime);
		m_vecObject[secondobject]->Update(changeInTime);
	}
}

void CObjectManager::Update()
{
	for (int hittee = 0; hittee < m_vecObject.size(); hittee++)
	{
		for (int hitter = 0; hitter < m_vecObject.size(); hitter++)
		{
			if (hittee >= hitter)
				continue;
			m_vecObject[hittee]->CollisionOtherObject(m_vecObject[hitter]);
		}
	}
	for (int i = 0; i < m_vecIObject.size(); i++)
	{
		m_vecIObject[i]->Update();
	}
}

vector<CObject*> CObjectManager::GetVecObject()
{
	return m_vecObject;
}

void CObjectManager::AddTileOBB(COBB* OBBbox)
{
	m_OBB.push_back(OBBbox);
}

void CObjectManager::Render()
{
	// << mapTest
	if (g_gameManager->GetGridMapMode())
	{
		multimap<vector<IObject*>, bool>::iterator it;
		for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
		{
			if (it->second == false)
			{
				// cout << "notRender" << endl;
				continue;
			}

			for (int i = 0; i < it->first.size(); i++)
				it->first[i]->Render();
		}
	}
	// >> mapTest

	for (int i = 0; i < m_vecIObject.size(); i++)
	{
		m_vecIObject[i]->Render();
    }

	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->Render();
	}

	for (int i = 0; i < m_OBB.size(); i++)
	{
		m_OBB[i]->OBBBOX_RENDER(D3DCOLOR_XRGB(255, 0, 0));
	}
}

void CObjectManager::RenderOBBBox()
{
	for (int i = 0; i < m_vecOBBBox.size(); i++)
	{
		m_vecOBBBox[i]->Render();
	}
	
}

vector<IObject*> CObjectManager::GetVecIObject()
{
	return m_vecIObject;
}

COBB* CObjectManager::GetTileOBB()
{
	for(int i =0 ; i < m_OBB.size() ; ++i)
	 return m_OBB[i];
}

void CObjectManager::Update_PickCheck(const vector<bool>& vecIsPick, const vector<D3DXVECTOR3>& vecVPos)
{
	int index = 0;
	for (int i = 1; i < m_vecObject.size(); i++)
	{
		if (vecIsPick[i] == false)
			continue;
		else
		{
			if (vecVPos[index].x >= vecVPos[i].x || vecVPos[index].y >= vecVPos[i].y || vecVPos[index].z >= vecVPos[i].z)
			{
				m_vecObject[index]->SetPickState(false);
				index = i;
			}
		} // >> : else
	} // >> : for
}