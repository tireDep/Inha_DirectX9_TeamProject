#include "stdafx.h"
#include "PhysicsObjectManager.h"
#include "PhysicsObject.h"

CPhysicsObjectManager::CPhysicsObjectManager()
{
}

CPhysicsObjectManager::~CPhysicsObjectManager()
{
}

void CPhysicsObjectManager::AddPhysicsObject(CPhysicsObject * physicsobject)
{
	m_vecPhysicsObject.push_back(physicsobject);
}

void CPhysicsObjectManager::RemovePhysicsObject(CPhysicsObject * physicsObject)
{
	vector<CPhysicsObject*>::iterator it;
	for (it = m_vecPhysicsObject.begin(); it != m_vecPhysicsObject.end();)
	{
		if (*it == physicsObject)
		{
			CPhysicsObject* temp = *it;
			it = m_vecPhysicsObject.erase(it);
			delete temp;
			return;
		}
		else
			it++;
	}
}

void CPhysicsObjectManager::Destroy()
{
	for (int i = 0; i < m_vecPhysicsObject.size(); i++)
		m_vecPhysicsObject[i]->Release();
}

void CPhysicsObjectManager::Update(float duration)
{
	for (int i = 0; i < m_vecPhysicsObject.size(); i++)
		m_vecPhysicsObject[i]->Update(duration);
}

void CPhysicsObjectManager::Render()
{
	for (int i = 0; i < m_vecPhysicsObject.size(); i++)
		m_vecPhysicsObject[i]->Render();
}

vector<CPhysicsObject*> CPhysicsObjectManager::getVecObject()
{
	return m_vecPhysicsObject;
}