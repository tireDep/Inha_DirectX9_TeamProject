#pragma once

class CPhysicsObject;
#define g_pPhysicsObjectManager CPhysicsObjectManager::GetInstance()

class CPhysicsObjectManager
{
private:
	SingleTone(CPhysicsObjectManager);
	vector<CPhysicsObject*> m_vecPhysicsObject;
public:
	void AddPhysicsObject(CPhysicsObject* physicsobject);
	void RemovePhysicsObject(CPhysicsObject* physicsObject);
	void Destroy();

	void Update(float duration);
	void Render();
	vector<CPhysicsObject*> getVecObject();
};