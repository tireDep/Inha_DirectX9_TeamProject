#include "stdafx.h"

#include "ObjectManager.h"
#include "Object.h"
#include "IObject.h"
#include "PObject.h"
#include "OBB.h"
#include "Gimmick.h"
#include "Sphere.h"
#include "Box.h"
#include "Cylinder.h"

CObjectManager::CObjectManager() :
	// m_frustum(NULL),
	// m_thread(NULL),
	ResetCube(false),
	KeepGoing(false),
	m_nowMapPos(0)
{
	// InitializeCriticalSection(&m_cs);
}

CObjectManager::~CObjectManager()
{
	RemoveMap();

	//if (m_thread != NULL)
	//{
	//	if (m_thread->joinable())
	//		m_thread->join();
	//}
	//SafeDelete(m_thread);
}

DWORD CObjectManager::DoFtoDw(float f)
{
	// float to dword
	return *((DWORD*)&f);
}

void CObjectManager::RemoveObject(CObject * Object)
{
	vector<CObject*>::iterator it;
	for (it = m_vecObject.begin(); it != m_vecObject.end();)
	{
		if (*it == Object)
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
void CObjectManager::RemoveObject(PObject * pObject)
{
	vector<PObject*>::iterator it;
	for (it = m_vecPObject.begin(); it != m_vecPObject.end();)
	{
		if (*it == pObject)
		{
			PObject* temp = *it;
			it = m_vecPObject.erase(it);
			delete temp;
			return;
		}
		else
			it++;
	}
}
void CObjectManager::RemoveObject(IObject * iObject)
{
	vector<IObject*>::iterator it;
	for (it = m_vecIObject.begin(); it != m_vecIObject.end();)
	{
		if (*it == iObject)
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
void CObjectManager::RemoveObject(COBB * OBBBox)
{
	vector<COBB*>::iterator it;
	for (it = m_vecOBBBox.begin(); it != m_vecOBBBox.end();)
	{
		if (*it == OBBBox)
		{
			// COBB* temp = *it;
			// it = m_vecOBBBox.erase(it);
			// delete temp;
			*it = NULL;
			return;
		}
		else
			it++;
	}
}
void CObjectManager::RemoveObject(CGimmick* Gimmick)
{
	vector<CGimmick*>::iterator it;
	for (it = m_vecGimmick.begin(); it != m_vecGimmick.end();)
	{
		if (*it == Gimmick)
		{
			IObject* temp = *it;
			it = m_vecGimmick.erase(it);
			delete temp;
			return;
		}
		else
			it++;
	}
}

void CObjectManager::Update_PickCheck(const vector<bool>& vecIsPick, const vector<D3DXVECTOR3>& vecVPos)
{
	int index = 0;
	for (int i = 1; i < m_vecPObject.size(); i++)
	{
		if (vecIsPick.size() == 1)
			return;

		if (vecIsPick[i] == false)
			continue;
		else
		{
			if (vecVPos[index].x >= vecVPos[i].x || vecVPos[index].y >= vecVPos[i].y || vecVPos[index].z >= vecVPos[i].z)
			{
				m_vecPObject[index]->SetPickState(false);
				index = i;
			}
		} // >> : else
	} // >> : for
}

void CObjectManager::Update(CRay ray)
{
	IObject* iObj = NULL;
	int loopSize = GetVecMapObjCnt();
	for (int i = 0; i < loopSize; i++)
	{
		iObj = GetIObjectIndex(i);

		if (iObj == NULL)
			continue;

		iObj->Update(ray);

		// m_vecIObject[i]->Update(ray);
	}
}

void CObjectManager::Update(CRay ray, D3DXCOLOR& objectcolor)
{
	vector<bool> vecIsPick;
	vector<D3DXVECTOR3> vecVPos;

	vector<CObject *> vecCheck = GetMapVecCObject();
	int loopSize = GetVecMapObjCnt();
	for (int i = 0; i <loopSize; i++)
	{
		PObject* pObjCheck = dynamic_cast<PObject*>(vecCheck[i]);

		if (pObjCheck == NULL)
			continue;

		pObjCheck->Update(ray, objectcolor, vecIsPick, vecVPos);

		// m_vecPObject[i]->Update(ray, objectcolor, vecIsPick, vecVPos);
	}

	if (vecIsPick.size() != 0)
		Update_PickCheck(vecIsPick, vecVPos);
}

// Integrate P + I Obejct...
void CObjectManager::Update(float duration)
{
	vector<CObject *> vecCheck = GetMapVecCObject();
	int loopSize = GetVecMapObjCnt();
	for (int i = 0; i <loopSize; i++)
	{
		IObject* iObjCheck = dynamic_cast<IObject*>(vecCheck[i]);

		if (iObjCheck == NULL)
			continue;

		iObjCheck->Update(duration);
	}

	// for (int i = 0; i < m_vecIObject.size(); i++)
	// 	m_vecIObject[i]->Update(duration);

	//
	//ofstream fout;
	//fout.open("PObjectData.txt");

	//for (int i = 0; i < m_vecPObject.size(); ++i) //끌때 판단
	//{

	//	fout << m_vecPObject[i]->GetPosition().x
	//		<< m_vecPObject[i]->GetPosition().y
	//		<< m_vecPObject[i]->GetPosition().z;
	//}
	//fout.close();


	//for (int i = 0; i < m_vecGimmick.size(); i++)
	//   m_vecGimmick[i]->Update(duration);
	//for (int i = 0; i < m_vecObject.size(); i++)
	//   m_vecObject[i]->Update(duration);
}

void CObjectManager::PreUpdate(float duration)
{
	for (int i = 0; i < m_vecIObject.size(); i++)
		m_vecIObject[i]->Update(duration);
}

void CObjectManager::UpdateLand(float duration)
{
	vector<CObject *> vecCheck = GetMapVecCObject();
	int loopSize = GetVecMapObjCnt();
	for (int i = 0; i <loopSize; i++)
	{
		PObject* pObjCheck = dynamic_cast<PObject*>(vecCheck[i]);

		if (pObjCheck == NULL)
			continue;

		pObjCheck->UpdateLand(duration);
		pObjCheck->Update(duration);
	}

	// for (int i = 0; i < m_vecPObject.size(); i++)
	// {
	// 	m_vecPObject[i]->UpdateLand(duration);
	// 	m_vecPObject[i]->Update(duration);
	// }
}

void CObjectManager::Collide(float duration)
{
	// vector<CObject *> vecCheck = GetMapVecCObject();
	// int loopSize = GetVecMapObjCnt();
	// for (int i = 0; i <loopSize; i++)
	// {
	// 	PObject* pObjCheck = dynamic_cast<PObject*>(vecCheck[i]);
	// 
	// 	if (pObjCheck == NULL)
	// 		continue;
	// }

	PObject* pObjCheck = NULL;
	IObject* iObjCheck = NULL;
	int loopSize = g_pObjectManager->GetVecMapObjCnt();
	///Sphere
	for (int SphereIndex = 0; SphereIndex < m_vecSphere.size(); SphereIndex++)
	{
		// Sphere to Other PObject
		for (int PObjectIndex = 0; PObjectIndex < loopSize; PObjectIndex++)
		{
			pObjCheck = g_pObjectManager->GetPObjectIndex(PObjectIndex);

			if (pObjCheck == NULL)
				continue;

			switch (pObjCheck->GetObjType())
			{
			case eSphere:
				if (m_vecSphere[SphereIndex]->hasIntersected(dynamic_cast<CSphere*>(pObjCheck)))
				{
					CollisionSphereToSphere(m_vecSphere[SphereIndex], static_cast<CSphere*>(pObjCheck), duration);
				}
				break;
			case eBox:
				if (m_vecSphere[SphereIndex]->hasIntersected(dynamic_cast<CBox*>(pObjCheck)))
				{
					CollisionSphereToBox(m_vecSphere[SphereIndex], pObjCheck, duration);
				}
				break;
			case eCylinder:
				if (m_vecSphere[SphereIndex]->hasIntersected(dynamic_cast<CCylinder*>(pObjCheck)))
				{
					CollisionSphereToBox(m_vecSphere[SphereIndex], pObjCheck, duration);
				}
				break;
			default:
				break;
			}
		} 
		// >> : for_pObj

		// Sphere To IObject
		for (int IObjectIndex = 0; IObjectIndex < loopSize; IObjectIndex++)
		{
			iObjCheck = g_pObjectManager->GetIObjectIndex(IObjectIndex);

			if (iObjCheck == NULL)
				continue;

			if (m_vecSphere[SphereIndex]->hasIntersected(iObjCheck))
			{
				switch (iObjCheck->GetObjType())
				{
				case eG_RotationBoard:  case eG_MovingCube:
				{
					D3DXVECTOR3 v;
					v = m_vecSphere[SphereIndex]->GetPosition() - iObjCheck->GetOBB()->GetCenter();
					D3DXVec3Normalize(&v, &v);
					m_vecSphere[SphereIndex]->SetPusingForce(v);
				}
				break;
				case eG_Door:
					break;
				case  eG_Switch:
				{
					iObjCheck->pBoxBool(true);
				}
				break;
				default:
					//CollisionSphereToIObject(m_vecSphere[SphereIndex], m_vecIObject[IObjectIndex], duration);
					CollisionBoxToTile(m_vecSphere[SphereIndex], iObjCheck, duration);
					iObjCheck->pBoxBool(false);
					break;
				}
			}
		}
		// >> : for_iObj
	}

	///Box
	for (int BoxIndex = 0; BoxIndex < m_vecBox.size(); BoxIndex++)
	{
		// Box to Other PObject
		for (int PObjectIndex = 0; PObjectIndex < loopSize; PObjectIndex++)
		{
			pObjCheck = g_pObjectManager->GetPObjectIndex(PObjectIndex);

			if (pObjCheck == NULL)
				continue;

			switch (pObjCheck->GetObjType())
			{
			case eSphere:
				break;
			case eBox:
				if (m_vecBox[BoxIndex]->hasIntersected(dynamic_cast<CBox*>(pObjCheck)))
				{
					CollisionBoxToBox(m_vecBox[BoxIndex], pObjCheck, duration);
				}
				break;
			case eCylinder:
				if (m_vecBox[BoxIndex]->hasIntersected(dynamic_cast<CCylinder*>(pObjCheck)))
				{
					CollisionBoxToBox(m_vecBox[BoxIndex], pObjCheck, duration);
				}
				break;
			default:
				break;
			}
		}

		// Box To IObject
		for (int IObjectIndex = 0; IObjectIndex < loopSize; IObjectIndex++)
		{
			iObjCheck = g_pObjectManager->GetIObjectIndex(IObjectIndex);

			if (iObjCheck == NULL)
				continue;

			if (m_vecBox[BoxIndex]->hasIntersected(iObjCheck))
			{
				switch (iObjCheck->GetObjType())
				{
				case eG_RotationBoard: case eG_MovingCube:
				{
					D3DXVECTOR3 v;
					v = m_vecBox[BoxIndex]->GetPosition() - iObjCheck->GetOBB()->GetCenter();
					D3DXVec3Normalize(&v, &v);
					m_vecBox[BoxIndex]->SetPusingForce(v);
				}
				break;
				case eG_Door:
					break;
				case  eG_Switch:
				{
					iObjCheck->pBoxBool(true);
				}
				break;
				default:
					CollisionBoxToTile(m_vecBox[BoxIndex], iObjCheck, duration);
					iObjCheck->pBoxBool(false);
					break;
				}
			}
		}

		//// Box to Other PObject
		//for (int PObectIndex = 0; PObectIndex < m_vecPObject.size(); PObectIndex++)
		//{
		//	switch (m_vecPObject[PObectIndex]->GetObjType())
		//	{
		//	case eSphere:
		//		break;
		//	case eBox:
		//		if (m_vecBox[BoxIndex]->hasIntersected(dynamic_cast<CBox*>(m_vecPObject[PObectIndex])))
		//		{
		//			CollisionBoxToBox(m_vecBox[BoxIndex], m_vecPObject[PObectIndex], duration);
		//		}
		//		break;
		//	case eCylinder:
		//		if (m_vecBox[BoxIndex]->hasIntersected(dynamic_cast<CCylinder*>(m_vecPObject[PObectIndex])))
		//		{
		//			CollisionBoxToBox(m_vecBox[BoxIndex], m_vecPObject[PObectIndex], duration);
		//		}
		//		break;
		//	default:
		//		break;
		//	}

		//	// Box To IObject
		//	for (int IObjectIndex = 0; IObjectIndex < m_vecIObject.size(); IObjectIndex++)
		//	{
		//		if (m_vecBox[BoxIndex]->hasIntersected(m_vecIObject[IObjectIndex]))
		//		{
		//			switch (m_vecIObject[IObjectIndex]->GetObjType())
		//			{
		//			case eG_RotationBoard: case eG_MovingCube:
		//			{
		//				D3DXVECTOR3 v;
		//				v = m_vecBox[BoxIndex]->GetPosition() - m_vecIObject[IObjectIndex]->GetOBB()->GetCenter();
		//				D3DXVec3Normalize(&v, &v);
		//				m_vecBox[BoxIndex]->SetPusingForce(v);
		//			}
		//			break;
		//			case eG_Door:
		//				break;
		//			case  eG_Switch:
		//			{
		//				m_vecIObject[IObjectIndex]->pBoxBool(true);
		//			}
		//			break;
		//			default:
		//				CollisionBoxToTile(m_vecBox[BoxIndex], m_vecIObject[IObjectIndex], duration);
		//				m_vecIObject[IObjectIndex]->pBoxBool(false);
		//				break;
		//			}
		//		}
		//	}
		// }
	}
	/// Cylinder
	for (int CylinderIndex = 0; CylinderIndex < m_vecCylinder.size(); CylinderIndex++)
	{
		// Cylinder to Other PObject
		for (int PObjectIndex = 0; PObjectIndex < loopSize; PObjectIndex++)
		{
			pObjCheck = g_pObjectManager->GetPObjectIndex(PObjectIndex);

			if (pObjCheck == NULL)
				continue;

			switch (pObjCheck->GetObjType())
			{
			case eSphere:
				break;
			case eBox:
				break;
			case eCylinder:
				if (m_vecCylinder[CylinderIndex]->hasIntersected(dynamic_cast<CCylinder*>(pObjCheck)))
				{
					CollisionBoxToBox(m_vecCylinder[CylinderIndex], pObjCheck, duration);
				}
				break;
			default:
				break;
			}
		}
		// << : for_pObj

		// Cylinder To IObject
		for (int IObjectIndex = 0; IObjectIndex < loopSize; IObjectIndex++)
		{
			iObjCheck = g_pObjectManager->GetIObjectIndex(IObjectIndex);

			if (iObjCheck == NULL)
				continue;

			if (m_vecCylinder[CylinderIndex]->hasIntersected(iObjCheck))
			{
				switch (iObjCheck->GetObjType())
				{
				case eG_RotationBoard:    case eG_MovingCube:	// Complete
				{
					D3DXVECTOR3 v;
					v = m_vecCylinder[CylinderIndex]->GetPosition() - iObjCheck->GetOBB()->GetCenter();
					D3DXVec3Normalize(&v, &v);
					m_vecCylinder[CylinderIndex]->SetPusingForce(v);
				}
				break;
				case eG_Door:
					break;
				case eG_Switch:
					iObjCheck->pBoxBool(true);
					break;
				default:
					CollisionBoxToTile(m_vecCylinder[CylinderIndex], iObjCheck, duration);
					iObjCheck->pBoxBool(false);
					break;
				}
			}
		}
		// << : for_iObj
	}
}

void CObjectManager::CollisionSphereToSphere(CSphere* one, CSphere* two, float duration)
{
	D3DXVECTOR3 contactNormal = one->GetPosition() - two->GetPosition();
	float penetration = D3DXVec3Length(&contactNormal) - one->GetRadius() - two->GetRadius();
	float elasticity = 1.0f;

	D3DXVECTOR3 relativeVelocity = one->GetVelocity() - two->GetVelocity();
	float separatinVelocity = D3DXVec3Dot(&relativeVelocity, &contactNormal);
	if (separatinVelocity > 0) return;         // Need Modify? 1 = Elasticity
	float newSepVelocity = -separatinVelocity * elasticity;

	D3DXVECTOR3 accCausedVelocity = one->GetAcceleration() - two->GetAcceleration();
	float accCausedSepVelocity = D3DXVec3Dot(&accCausedVelocity, &contactNormal) * duration;
	if (accCausedSepVelocity < 0)
	{                 // Need Modify? 1 = Elasticity
		newSepVelocity += (elasticity * accCausedSepVelocity);
		if (newSepVelocity < 0) newSepVelocity = 0.0f;
	}

	float deltaVelocity = newSepVelocity - separatinVelocity;
	float totalInverseMass = one->GetInverseMass() + two->GetInverseMass();
	if (totalInverseMass <= 0) return;

	float impulse = deltaVelocity / totalInverseMass;
	D3DXVECTOR3 impulsePerIMass = contactNormal * impulse;

	one->SetVelocity(one->GetVelocity() + impulsePerIMass * one->GetInverseMass());
	two->SetVelocity(two->GetVelocity() + impulsePerIMass * -two->GetInverseMass());

	if (penetration <= 0) return;
	D3DXVECTOR3 movePerIMass = contactNormal * (penetration / totalInverseMass);
	one->SetPosition(one->GetPosition() + movePerIMass * one->GetInverseMass());
	two->SetPosition(two->GetPosition() + movePerIMass * -two->GetInverseMass());
}

void CObjectManager::CollisionSphereToBox(CSphere* one, PObject* two, float duration)
{
	D3DXMATRIXA16 inverseBoxMatrix;
	D3DXMatrixInverse(&inverseBoxMatrix, NULL, &two->GetmatWorld());

	D3DXVECTOR3 SphereToBoxCenter;
	D3DXVec3TransformCoord(&SphereToBoxCenter, &one->GetPosition(), &inverseBoxMatrix);

	D3DXVECTOR3 closestPt(0, 0, 0);
	float dist;

	dist = SphereToBoxCenter.x;
	if (dist > two->GetOBB()->GetOBBWidth()) dist = two->GetOBB()->GetOBBWidth();
	if (dist < -two->GetOBB()->GetOBBWidth()) dist = -two->GetOBB()->GetOBBWidth();
	closestPt.x = dist;

	dist = SphereToBoxCenter.y;
	if (dist >  two->GetOBB()->GetOBBHeight()) dist = two->GetOBB()->GetOBBHeight();
	if (dist < -two->GetOBB()->GetOBBHeight()) dist = -two->GetOBB()->GetOBBHeight();
	closestPt.y = dist;

	dist = SphereToBoxCenter.z;
	if (dist >  two->GetOBB()->GetOBBDepth()) dist = two->GetOBB()->GetOBBDepth();
	if (dist < -two->GetOBB()->GetOBBDepth()) dist = -two->GetOBB()->GetOBBDepth();
	closestPt.z = dist;

	//dist = SphereToBoxCenter.x;
	//if (dist > two->GetOBB()->GetOBBWidth() / 2.0f) dist = two->GetOBB()->GetOBBWidth() / 2.0f;
	//if (dist < -two->GetOBB()->GetOBBWidth() / 2.0f) dist = -two->GetOBB()->GetOBBWidth() / 2.0f;
	//closestPt.x = dist;
	//dist = SphereToBoxCenter.y;
	//if (dist >  two->GetOBB()->GetOBBHeight() / 2.0f) dist =  two->GetOBB()->GetOBBHeight() / 2.0f;
	//if (dist < -two->GetOBB()->GetOBBHeight() / 2.0f) dist = -two->GetOBB()->GetOBBHeight() / 2.0f;
	//closestPt.y = dist;
	//dist = SphereToBoxCenter.z;
	//if (dist >  two->GetOBB()->GetOBBDepth() / 2.0f) dist =  two->GetOBB()->GetOBBDepth() / 2.0f;
	//if (dist < -two->GetOBB()->GetOBBDepth() / 2.0f) dist = -two->GetOBB()->GetOBBDepth() / 2.0f;
	//closestPt.z = dist;

	SphereToBoxCenter.x *= two->GetmatWorld()._11;
	SphereToBoxCenter.y *= two->GetmatWorld()._22;
	SphereToBoxCenter.z *= two->GetmatWorld()._33;

	D3DXVECTOR3 tmp = closestPt - SphereToBoxCenter;
	dist = D3DXVec3Length(&tmp);

	D3DXVECTOR3 closestPtWorld;
	D3DXVec3TransformCoord(&closestPtWorld, &closestPt, &two->GetmatWorld());

	D3DXVECTOR3 contactNormal = closestPtWorld - SphereToBoxCenter;
	D3DXVec3Normalize(&contactNormal, &contactNormal);
	// TEST
	contactNormal.y = 0;
	float penetration = one->GetRadius() - sqrtf(dist);
	float elasticity = 1.0f;

	D3DXVECTOR3 relativeVelocity = one->GetVelocity() - two->GetVelocity();
	float separatinVelocity = D3DXVec3Dot(&relativeVelocity, &contactNormal);
	//if (separatinVelocity > 0) return;         // Need Modify? 1 = Elasticity
	float newSepVelocity = -separatinVelocity * elasticity;

	D3DXVECTOR3 accCausedVelocity = one->GetAcceleration() - two->GetAcceleration();
	float accCausedSepVelocity = D3DXVec3Dot(&accCausedVelocity, &contactNormal) * duration;
	//if (accCausedSepVelocity < 0)
	//{                 // Need Modify? 1 = Elasticity
		newSepVelocity += (elasticity * accCausedSepVelocity);
		//if (newSepVelocity < 0) newSepVelocity = 0.0f;
	//}

	float deltaVelocity = newSepVelocity - separatinVelocity;
	float totalInverseMass = one->GetInverseMass() + two->GetInverseMass();
	if (totalInverseMass <= 0) return;

	float impulse = deltaVelocity / totalInverseMass;
	D3DXVECTOR3 impulsePerIMass = contactNormal * impulse;

	one->SetVelocity(one->GetVelocity() + impulsePerIMass * one->GetInverseMass());
	two->SetVelocity(two->GetVelocity() + impulsePerIMass * -two->GetInverseMass());

	//if (penetration <= 0) return;
	D3DXVECTOR3 movePerIMass = contactNormal * (penetration / totalInverseMass);
	one->SetPosition(one->GetPosition() + movePerIMass * one->GetInverseMass());
	two->SetPosition(two->GetPosition() + movePerIMass * -two->GetInverseMass());
}

void CObjectManager::CollisionBoxToBox(PObject* one, PObject* two, float duration)
{
	D3DXVECTOR3 contactNormal;
	float penetration;
	one->GetOBB()->IsCollision(two->GetOBB(), &contactNormal, &penetration);
	contactNormal = one->GetPosition() - two->GetPosition();   // Need To Modify...
	D3DXVec3Normalize(&contactNormal, &contactNormal);
	float elasticity = 1.0f;

	D3DXVECTOR3 relativeVelocity = one->GetVelocity() - two->GetVelocity();
	float separatinVelocity = D3DXVec3Dot(&relativeVelocity, &contactNormal);
	if (separatinVelocity > 0) return;         // Need Modify? 1 = Elasticity
	float newSepVelocity = -separatinVelocity * elasticity;

	D3DXVECTOR3 accCausedVelocity = one->GetAcceleration() - two->GetAcceleration();
	float accCausedSepVelocity = D3DXVec3Dot(&accCausedVelocity, &contactNormal) * duration;
	if (accCausedSepVelocity < 0)
	{                 // Need Modify? 1 = Elasticity
		newSepVelocity += (elasticity * accCausedSepVelocity);
		if (newSepVelocity < 0) newSepVelocity = 0.0f;
	}

	float deltaVelocity = newSepVelocity - separatinVelocity;
	float totalInverseMass = one->GetInverseMass() + two->GetInverseMass();
	if (totalInverseMass <= 0) return;

	float impulse = deltaVelocity / totalInverseMass;
	D3DXVECTOR3 impulsePerIMass = contactNormal * impulse;

	one->SetVelocity(one->GetVelocity() + impulsePerIMass * one->GetInverseMass());
	two->SetVelocity(two->GetVelocity() + impulsePerIMass * -two->GetInverseMass());

	if (penetration <= 0) return;
	D3DXVECTOR3 movePerIMass = contactNormal * (penetration / totalInverseMass);
	one->SetPosition(one->GetPosition() + movePerIMass * one->GetInverseMass());
	two->SetPosition(two->GetPosition() + movePerIMass * -two->GetInverseMass());
}

void CObjectManager::CollisionBoxToTile(PObject * pObject, IObject * iObject, float duration)
{
	D3DXVECTOR3 contactNormal;
	float penetration;
	pObject->GetOBB()->IsCollision(iObject->GetOBB(), &contactNormal, &penetration);

	float elasticity = 0.1f; // TEST
	D3DXVECTOR3 relativeVelocity = pObject->GetVelocity();
	float separatinVelocity = D3DXVec3Dot(&relativeVelocity, &contactNormal);
	if (separatinVelocity > 0) return;         // Need Modify? 1 = Elasticity
	float newSepVelocity = -separatinVelocity * elasticity;

	D3DXVECTOR3 accCausedVelocity = pObject->GetAcceleration();
	float accCausedSepVelocity = D3DXVec3Dot(&accCausedVelocity, &contactNormal) * duration;
	//if (accCausedSepVelocity < 0)
	//{                 // Need Modify? 1 = Elasticity
		newSepVelocity += (elasticity * accCausedSepVelocity);
		//if (newSepVelocity < 0) newSepVelocity = 0.0f;
	//}

	float deltaVelocity = newSepVelocity - separatinVelocity;
	if (pObject->GetInverseMass() <= 0) return;

	float impulse = deltaVelocity / pObject->GetInverseMass();
	D3DXVECTOR3 impulsePerIMass = contactNormal * impulse;

	pObject->SetVelocity(pObject->GetVelocity() + impulsePerIMass * pObject->GetInverseMass());

	if (penetration <= 0) return;
	D3DXVECTOR3 movePerIMass = contactNormal * (penetration / pObject->GetInverseMass());
	pObject->SetPosition(pObject->GetPosition() + movePerIMass * pObject->GetInverseMass());
}

void CObjectManager::Reset()
{
	for (int i = 0; i < m_vecPObject.size(); i++)
	{
		m_vecPObject[i]->SetDxColor(m_vecPObject[i]->ResetColor);
		m_vecPObject[i]->SetPosition(m_vecPObject[i]->saveTranslation);
		m_vecPObject[i]->SetForceApplied(false);
		m_vecPObject[i]->SetAcceleration(D3DXVECTOR3(0, 0, 0));
		m_vecPObject[i]->SetVelocity(D3DXVECTOR3(0, 0, 0));
		m_vecPObject[i]->SetForceVector(D3DXVECTOR3(0, 0, 0));
	}

	for (int i = 0; i < m_vecIObject.size(); ++i)
	{
		m_vecIObject[i]->PresentPosition = m_vecIObject[i]->ResetPosition;
	}

	g_pObjectManager->AllUpdate();
}

void CObjectManager::Render(const D3DXVECTOR3& camEye)
{
	PObject* pObj = NULL;
	multimap<int, vector<CObject*>>::iterator it;
	for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
	{
		//// >> fog
		g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, true);

		g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.67f, 0.85f, 0.89f, 0.1f));
		// g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.4f));

		g_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
		g_pD3DDevice->SetRenderState(D3DRS_FOGSTART, DoFtoDw(25.0f));
		g_pD3DDevice->SetRenderState(D3DRS_FOGEND, DoFtoDw(45.0f));
		// >> 한 구역 크기 : 30
		g_pD3DDevice->SetRenderState(D3DRS_RANGEFOGENABLE, true);

		D3DXVECTOR3 vRender;
		float length = 0;
		float camDist = 60.0f;
		float camCloseDist = 37.0f;
		for (int i = 0; i < it->second.size(); i++)
		{
			// >> 안개 범위 안에 들어가는 것만 랜더
			vRender = it->second[i]->GetTranslation() - camEye;
			length = D3DXVec3Length(&vRender);
			if (length >= -camDist && length <= camDist)
			{
				// >> 색 변화, 바다 등 셰이더 적용을 위해 일정 범위 내 안개 off
				if (length >= -camCloseDist && length <= camCloseDist)
					g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, false);

				it->second[i]->Render();

				g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, true);
			}
		}

		g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, false);
		
		//// KT fog off... Need to level design.. 
		////for (int i = 0; i < it->second.size(); i++)
		////	it->second[i]->Render();

		//for (int i = 0; i < it->second.size(); i++)
		//{
		//	iObj = dynamic_cast<IObject*> (it->second[i]);
		//	if (iObj == NULL)
		//		continue;

		//	if (!iObj->m_isCameraRender && iObj->GetObjType() < ObjectType::eTile13 && renderObj == NULL)
		//		renderObj = dynamic_cast<IObject*> (it->second[i]);
		//	else
		//		iObj->Render();
		//}

		//// for (int i = 0; i < it->second.size(); i++)
		//// {
		//// 	if(it->second[i]->m_isCameraRender)
		//// 		it->second[i]->Render();
		//// }

		//// >> pObject Render
		//int loopSize = m_vecPObject.size();
		//for (int i = 0; i < loopSize; i++)
		//{
		//	m_vecPObject[i]->Render();
		//}

		// >> 기존 방식 : 3X3 영역만 랜더, 나머지 안개 OR 랜더 X
		// >> 너무 바뀌는게 잘 보임
		// if (m_vecIsRenderState[index] == true)
		// {
		// 	for (int i = 0; i < it->second.size(); i++)
		// 		it->second[i]->Render();
		// }
		//else
		//{
		//	// >> fog
		//	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, true);
		//
		//	g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(255, 255, 255, 255));
		//	// g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(156, 211, 226, 125));
		//	// todo : fog color
		//	// todo : 너무 눈에 띄에 바뀜
		//
		//	g_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
		//	g_pD3DDevice->SetRenderState(D3DRS_FOGSTART, DoFtoDw(10.0f));
		//	g_pD3DDevice->SetRenderState(D3DRS_FOGEND, DoFtoDw(200.0f));
		//	g_pD3DDevice->SetRenderState(D3DRS_RANGEFOGENABLE, true);
		//
		//	// for (int i = 0; i < it->second.size(); i++)
		//	// 	it->second[i]->Render();
		//
		//	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, false);
		//}
	} // << : for

	// if (renderObj != NULL)
	// 	renderObj->Render();
}

void CObjectManager::RenderOBBBox()
{
	for (int i = 0; i < m_vecOBBBox.size(); i++)
		m_vecOBBBox[i]->Render();
}

void CObjectManager::Destroy()
{
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Release();

	// Integration Object?
	for (int i = 0; i < m_vecIObject.size(); i++)
		m_vecIObject[i]->Release();

	m_vecObject.clear();
	m_vecIObject.clear();
}

// YS CODE... MAP TEST
void CObjectManager::AddMap()
{
	vector<CObject*> temp;

	for (int i = m_IObjCnt; i < m_vecObject.size(); i++)
		temp.push_back(m_vecObject[i]);

	m_mapObject.insert(pair<int, vector<CObject*>>(g_pFileLoadManager->GetFileLoadCnt(), temp));

	m_IObjCnt = m_vecObject.size();


	// m_vecIObject.clear();
	// >> 테스트 완료 후 적용
}

void CObjectManager::RemoveMap()
{
	if (m_vecIObject.size() == 0)
		return;
	// >> 이중 삭제 관련 임시 적용

	int size;
	multimap<int, vector<CObject*>>::iterator it;
	for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
	{
		size = it->second.size();
		for (int i = 0; i < size; i++)
		{
			if (&it->second != NULL)
				SafeDelete(it->second[i]);
		}
	} // >> : for

	m_mapObject.clear();
}

//int CObjectManager::GetMapVecSize(int mapIndex)
//{
//	int num = 0;
//	multimap<vector<IObject*>, bool>::iterator it;
//	for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
//	{
//		if (mapIndex != num)
//			continue;
//
//		return it->first.size();
//	}
//}

//IObject & CObjectManager::GetIObject(int mapIndex, int vectorIndex)
//{
//	int num = 0;
//	multimap<int, vector<IObject*>>::iterator it;
//	for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
//	{
//		num++;
//		if (mapIndex != num)
//			continue;
//
//		return *it->second[vectorIndex];
//	}
//}

void CObjectManager::CalcNowPositionIndex(const D3DXVECTOR3 & m_characterPos)
{
	float mapSize = 30;
	D3DXVECTOR3 playerPos = m_characterPos;

	POINT result;
	result.x = ((float)mapSize / 2.0f) + playerPos.x;
	result.y = ((float)mapSize / 2.0f) - playerPos.z;

	result.x = floorf(result.x) - 15;
	result.y = floorf(result.y) - 15;

	int gridNum = -15;
	int gridAddNum = 30;
	int maxSize = g_pFileLoadManager->GetFileLoadCnt();

	for (int i = 0; i < maxSize; i++)
	{
		if (gridNum + (gridAddNum * i) <= result.x && gridNum + (gridAddNum * (i + 1)) >= result.x)
			result.x = i;

		if (gridNum + (gridAddNum * i) <= result.y && gridNum + (gridAddNum * (i + 1)) >= result.y)
			result.y = i;
	}

	int mapCnt = g_pFileLoadManager->GetMapXCnt();
	m_nowMapPos = result.x + (result.y * mapCnt);
	// >> 현재 플레이어가 위치한 맵 번호

	// SetIsRenderState();
	// >> 랜더 방식 변경으로 필요하지 않음
}

void CObjectManager::SetIsRenderState()
{
	// >> 랜더 상태 결정
	// >> 플레이어 기준 3x3 랜더, 그 외의 범위는 포그처리

	m_vecIsRenderState.clear();
	int maxSize = g_pFileLoadManager->GetFileLoadCnt();

	for (int i = 0; i < maxSize; i++)
		m_vecIsRenderState.push_back(false);

	int mapCnt = g_pFileLoadManager->GetMapXCnt();
	int indexY = m_nowMapPos / mapCnt;
	int indexX = m_nowMapPos % mapCnt;

	int checkIndex = m_nowMapPos;
	while (true)
	{
		// >> 가장 오른쪽 끝 라인인지 판별 인덱스 계산
		if (checkIndex < mapCnt)
			break;
		else
			checkIndex %= mapCnt;
	}

	// todo? : 꼭지점 부분, 모서리 부분에 대한 재처리 필요?

	// >> 플레이어 기준 상하좌우대각선 true 처리(3 x 3)
	if (checkIndex + 1 == mapCnt)
	{
		// >> 가장 오른쪽 끝일 경우
		for (int i = indexY - 1; i < indexY + 2; i++)
		{
			for (int j = indexX - 1; j < indexX + 1; j++)
			{
				if (i < 0 || j < 0 || i >= maxSize || j >= maxSize || (i * mapCnt) + j < 0 || (i * mapCnt) + j >= maxSize)
					continue;

				m_vecIsRenderState[(i * mapCnt) + j] = true;
			}
		}
	}
	else
	{
		for (int i = indexY - 1; i < indexY + 2; i++)
		{
			for (int j = indexX - 1; j < indexX + 2; j++)
			{
				if (i < 0 || j < 0 || i >= maxSize || j >= maxSize || (i * mapCnt) + j < 0 || (i * mapCnt) + j >= maxSize)
					continue;

				m_vecIsRenderState[(i * mapCnt) + j] = true;

			} // << : for_j

		} // << : for_i

	} // << : else
}

int CObjectManager::GetVecMapObjCnt()
{
	int result = -1;
	int index = 0;

	map<int, vector<CObject*>>::iterator it;
	for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
	{
		if (index == m_nowMapPos)
			return it->second.size();
		else
			index++;
	}

	return result;
}

vector<CObject *> CObjectManager::GetMapVecCObject()
{
	int index = 0;
	map<int, vector<CObject*>>::iterator it;
	for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
	{
		if (index == m_nowMapPos)
			return it->second;
		else
			index++;
	}
}

PObject * CObjectManager::GetPObjectIndex(int index)
{
	return dynamic_cast<PObject*> (GetMapVecCObject()[index]);
}

IObject * CObjectManager::GetIObjectIndex(int index)
{
	return dynamic_cast<IObject*> (GetMapVecCObject()[index]);
}

void CObjectManager::AllUpdate()
{
	float fTime = 0.0001f;

	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->Update(fTime);
	}
}

//void CObjectManager::UpdateNewMap(CFrustum * frustum)
//{
//	//// todo : thread
//	//m_frustum = frustum;
//	//if (m_thread == NULL)
//	//{
//	//	m_thread = new thread(&CObjectManager::Thread_CalcNewMap, this);
//	//	// cout << "thread" << endl;
//	//}
//	//else
//	//{
//	//	if (m_thread->joinable())
//	//		m_thread->join();
//
//	//	m_thread = NULL;
//	//	// cout << "threadEnd" << endl;
//	//}
//}
//
//void CObjectManager::Thread_CalcNewMap()
//{
//	//EnterCriticalSection(&m_cs);
//	//bool check = false;
//	//multimap<vector<IObject*>, bool>::iterator it;
//	//for (it = m_mapObject.begin(); it != m_mapObject.end(); it++)
//	//{
//	//   check = false;
//
//	//   for (int i = 0; i < it->first.size(); i++)
//	//   {
//	//      float radius = 0;
//	//      radius = it->first[0]->GetScale().x > it->first[0]->GetScale().y ? it->first[0]->GetScale().x : it->first[0]->GetScale().y;
//	//      radius = radius > it->first[0]->GetScale().z ? radius : it->first[0]->GetScale().z;
//
//	//      if (m_frustum->IsInFrustum(it->first[i]->GetTranslate(), radius))
//	//      {
//	//         it->second = true;
//	//         check = true;
//	//         // >> todo
//	//         // 판정 주변 인덱스 true, 아니면 false 처리
//	//         // 맵 세로, 가로 크기 알아야 함
//	//         // 3*3 정도 판정?
//	//      }
//	//   }
//
//	//   if (!check)
//	//      it->second = false;
//	//}
//	//LeaveCriticalSection(&m_cs);
//}

/// Delete Later...
//void CObjectManager::GenerateContacts()
//{
//   CollisionPlane plane;
//   plane.direction = D3DXVECTOR3(0, 1, 0);
//   plane.offset = 0;
//   cData.reset(maxContacts);
//   cData.friction = 0.9f;
//   cData.restitution = 0.6f;
//   cData.tolerance = 0.1f;
//
//}
// Collide
//void CObjectManager::GenerateContacts()
//{
//   for (int i = 0; i < m_vecPObject.size(); i++)
//   {
//      m_vecPObject[i]->GenerateContacts();
//   }
//}
//void CObjectManager::Collide(float duration)
//{
//   for (int hittee = 0; hittee < m_vecObject.size(); hittee++)
//   {
//      for (int hitter = 0; hitter < m_vecObject.size(); hitter++)
//      {
//         if (hittee >= hitter)
//            continue;
//         CTestObjCollision theCollision(m_vecObject[hittee], m_vecObject[hitter]);
//         Collision_Status collisionOccurred = theCollision.CollisionOccurred();
//         switch (collisionOccurred)
//         {
//            case Collision_Status::COLLISION_TOUCHING:
//               theCollision.CalculateReactions();
//               break;
//            case Collision_Status::COLLISION_OVERLAPPING:
////               HandleOverlapping(duration, hittee, hitter, theCollision);
//               break;
//            case Collision_Status::COLLISION_NONE:
//               break;
//            default:
//               break;
//         }
//      }
//   }
//}
//void CObjectManager::HandleOverlapping(float timeIncrement, int firstobject, int secondobject, CTestObjCollision & theCollision)
//{
//   float changeInTime = timeIncrement;
//
//   Collision_Status collisionOccured = Collision_Status::COLLISION_OVERLAPPING;
//   for (bool done = false; (!done) && (!CloseToZero(changeInTime));)
//   {
//      switch (collisionOccured)
//      {
//         case Collision_Status::COLLISION_OVERLAPPING:
//            {
//               CObject* firstObject;
//               CObject* secondObject;
//               firstObject = m_vecObject[firstobject];
//               secondObject = m_vecObject[secondobject];
//
//               D3DXVECTOR3 tempVector = firstObject->GetAngularVelocity();
//               tempVector *= -1;
//               firstObject->SetAngularVelocity(tempVector);
//               tempVector = firstObject->GetLinearVelocity();
//               tempVector *= -1;
//               firstObject->SetLinearVelocity(tempVector);
//               firstObject->SetForceVector(firstObject->GetForceVector() * -1);
//
//               tempVector = secondObject->GetAngularVelocity();
//               tempVector *= -1;
//               secondObject->SetAngularVelocity(tempVector);
//               tempVector = secondObject->GetLinearVelocity();
//               tempVector *= -1;
//               secondObject->SetLinearVelocity(tempVector);
//               secondObject->SetForceVector(secondObject->GetForceVector() * -1);
//
//               firstObject->Update(changeInTime);
//               secondObject->Update(changeInTime);
//
//               changeInTime /= 2;
//
//               tempVector = firstObject->GetAngularVelocity();
//               tempVector *= -1;
//               firstObject->SetAngularVelocity(tempVector);
//               tempVector = firstObject->GetLinearVelocity();
//               tempVector *= -1;
//               firstObject->SetLinearVelocity(tempVector);
//               firstObject->SetForceVector(firstObject->GetForceVector() * -1);
//
//               tempVector = secondObject->GetAngularVelocity();
//               tempVector *= -1;
//               secondObject->SetAngularVelocity(tempVector);
//               tempVector = secondObject->GetLinearVelocity();
//               tempVector *= -1;
//               secondObject->SetLinearVelocity(tempVector);
//               secondObject->SetForceVector(secondObject->GetForceVector() * -1);
//
//               firstObject->Update(changeInTime);
//               secondObject->Update(changeInTime);
//
//               m_vecObject[firstobject] = firstObject;
//               m_vecObject[secondobject] = secondObject;
//               collisionOccured = theCollision.CollisionOccurred();
//            }
//            break;
//         case Collision_Status::COLLISION_TOUCHING:
//            theCollision.CalculateReactions();
//            done = true;
//            break;
//         case Collision_Status::COLLISION_NONE:
//            m_vecObject[firstobject]->Update(changeInTime);
//            m_vecObject[secondobject]->Update(changeInTime);
//            collisionOccured = theCollision.CollisionOccurred();
//            break;
//         default:
//            break;
//      }   // << : switch
//   }   // << : for
//   if (CloseToZero(changeInTime))
//   {
//      theCollision.CalculateReactions();
//      m_vecObject[firstobject]->Update(changeInTime);
//      m_vecObject[secondobject]->Update(changeInTime);
//   }
//}
//void CObjectManager::Update(float duration, CHeight* pMap)
//{
//   for (int i = 0; i < m_vecObject.size(); i++)
//      m_vecObject[i]->Update(duration , pMap);
//}
//void CObjectManager::Update3D(float duration)
//{
//   for (int i = 0; i < m_vecObject.size(); i++)
//      m_vecObject[i]->Update3D(duration);
//}
//for (int BoxIndex = 0; BoxIndex < m_vecBox.size(); BoxIndex++)
//{
//   // Box to Other PObject... Subtract Sphere      m_vecBox.size() + m_vecCylinder.size()?
//   for (int PObectIndex = 0; PObectIndex < m_vecPObject.size(); PObectIndex++)
//   {
//   }
//   // Box to Gimmick
//   for (int GimmickIndex = 0; GimmickIndex < m_vecGimmick.size(); GimmickIndex++)
//   {
//   }
//   // Box to IObject... Subtract Gimmick
//   for (int IObjectIndex = 0; IObjectIndex < m_vecIObject.size(); IObjectIndex++)
//   {
//   }
//}
/////Cylinder
//for (int CylinderIndex = 0; CylinderIndex < m_vecCylinder.size(); CylinderIndex++)
//{
//   // Cylinder to Other PObject... Subtract Sphere, Box   m_vecCylinder.size()?
//   for (int PObectIndex = 0; PObectIndex < m_vecPObject.size(); PObectIndex++)
//   {
//   }
//   // Cylinder to Gimmick
//   for (int GimmickIndex = 0; GimmickIndex < m_vecGimmick.size(); GimmickIndex++)
//   {
//   }
//   // Cylinder to IObject... Subtract Gimmick
//   for (int IObjectIndex = 0; IObjectIndex < m_vecIObject.size(); IObjectIndex++)
//   {
//   }
//}
//void CObjectManager::CollisionPObject(PObject * one, PObject * two, float duration)
//{
//   D3DXVECTOR3 unitNormal = one->GetPosition() - two->GetPosition();
//
//   float v1 = D3DXVec3Dot(&one->GetVelocity(), &unitNormal);
//   float v2 = D3DXVec3Dot(&two->GetVelocity(), &unitNormal);
//
//   float averageE = (one->GetElasticity() + two->GetElasticity()) / 2.0f;
//
//   float finalv1 =   ((one->GetMass() - averageE * two->GetMass()) * v1 + (1 + averageE) * two->GetMass() * v2) / (one->GetMass() + two->GetMass());
//   float finalv2 = ((two->GetMass() - averageE * one->GetMass()) * v2 + (1 + averageE) * one->GetMass() * v1) / (one->GetMass() + two->GetMass());
//   
//   one->SetVelocity((((finalv1 - v1) * unitNormal) + one->GetVelocity()));
//   two->SetVelocity((((finalv2 - v2) * unitNormal) + two->GetVelocity()));
//
//   D3DXVECTOR3 acceleration1 = one->GetVelocity() / duration;
//   D3DXVECTOR3 acceleration2 = two->GetVelocity() / duration;
//
//   one->SetForceVector(acceleration1 * one->GetMass());
//   two->SetForceVector(acceleration2 * two->GetMass());
//}
// Need To modify...
//for (int hittee = 0; hittee < m_vecPObject.size(); hittee++)
//{
//   for (int hitter = 0; hitter < m_vecPObject.size(); hitter++)
//   {
//      if (hittee >= hitter)
//         continue;
//      //m_vecPObject[hittee]->CollisionOtherObject(m_vecPObject[hitter]);
//      m_vecPObject[hittee]->Collision3D(m_vecPObject[hitter]);
//   }
//}
// Need To Modify...
// OBB TEST
//for (int i = 0; i < m_vecBox.size(); i++)
//   for (int j = 0; j < m_vecIObject.size(); j++)
//   {
//      m_vecBox[i]->hasIntersected(m_vecIObject[j]);
//   }
//for (int i = 0; i < m_vecIObject.size(); i++)
//{
//   m_vecIObject[i]->Update();
//}
// Delete Later... Box to Box
//void CObjectManager::CollisionPObject(PObject* one, PObject* two, float duration)
//{
//	D3DXVECTOR3 contactNormal = one->GetPosition() - two->GetPosition();
//	float penetration = D3DXVec3Length(&contactNormal) - one->GetBoundingSphere() - two->GetBoundingSphere();
//	float elasticity = 1.0f;
//
//	D3DXVECTOR3 relativeVelocity = one->GetVelocity() - two->GetVelocity();
//	float separatinVelocity = D3DXVec3Dot(&relativeVelocity, &contactNormal);
//	if (separatinVelocity > 0) return;         // Need Modify? 1 = Elasticity
//	float newSepVelocity = -separatinVelocity * elasticity;
//
//	D3DXVECTOR3 accCausedVelocity = one->GetAcceleration() - two->GetAcceleration();
//	float accCausedSepVelocity = D3DXVec3Dot(&accCausedVelocity, &contactNormal) * duration;
//	if (accCausedSepVelocity < 0)
//	{                 // Need Modify? 1 = Elasticity
//		newSepVelocity += (elasticity * accCausedSepVelocity);
//		if (newSepVelocity < 0) newSepVelocity = 0.0f;
//	}
//
//	float deltaVelocity = newSepVelocity - separatinVelocity;
//	float totalInverseMass = one->GetInverseMass() + two->GetInverseMass();
//	if (totalInverseMass <= 0) return;
//
//	float impulse = deltaVelocity / totalInverseMass;
//	D3DXVECTOR3 impulsePerIMass = contactNormal * impulse;
//
//	one->SetVelocity(one->GetVelocity() + impulsePerIMass * one->GetInverseMass());
//	two->SetVelocity(two->GetVelocity() + impulsePerIMass * -two->GetInverseMass());
//
//	if (penetration <= 0) return;
//	D3DXVECTOR3 movePerIMass = contactNormal * (penetration / totalInverseMass);
//	one->SetPosition(one->GetPosition() + movePerIMass * one->GetInverseMass());
//	two->SetPosition(two->GetPosition() + movePerIMass * -two->GetInverseMass());
//}
// Delete Later... Box to Box
//void CObjectManager::CollisionIObject(PObject* pObject, IObject* iObject, float duration)
//{
//	D3DXVECTOR3 contactNormal = pObject->GetPosition() - D3DXVECTOR3(iObject->GetmatWorld()._41, iObject->GetmatWorld()._42, iObject->GetmatWorld()._43);
//	// TEST
//	contactNormal.y = 0;
//	float penetration = fabs(D3DXVec3Length(&contactNormal)) - pObject->GetBoundingSphere();
//	float elasticity = 0.1f; // TEST
//	D3DXVECTOR3 relativeVelocity = pObject->GetVelocity();
//	float separatinVelocity = D3DXVec3Dot(&relativeVelocity, &contactNormal);
//	if (separatinVelocity > 0) return;         // Need Modify? 1 = Elasticity
//	float newSepVelocity = -separatinVelocity * elasticity;
//
//	D3DXVECTOR3 accCausedVelocity = pObject->GetAcceleration();
//	float accCausedSepVelocity = D3DXVec3Dot(&accCausedVelocity, &contactNormal) * duration;
//	if (accCausedSepVelocity < 0)
//	{                 // Need Modify? 1 = Elasticity
//		newSepVelocity += (elasticity * accCausedSepVelocity);
//		if (newSepVelocity < 0) newSepVelocity = 0.0f;
//	}
//
//	float deltaVelocity = newSepVelocity - separatinVelocity;
//	if (pObject->GetInverseMass() <= 0) return;
//
//	float impulse = deltaVelocity / pObject->GetInverseMass();
//	D3DXVECTOR3 impulsePerIMass = contactNormal * impulse;
//
//	pObject->SetVelocity(pObject->GetVelocity() + impulsePerIMass * pObject->GetInverseMass());
//
//	if (penetration <= 0) return;
//	D3DXVECTOR3 movePerIMass = contactNormal * (penetration / pObject->GetInverseMass());
//	pObject->SetPosition(pObject->GetPosition() + movePerIMass * pObject->GetInverseMass());
//}
//void CObjectManager::AddObject(CObject * cObject)
//{
//   m_vecObject.push_back(cObject);
//}
//void CObjectManager::AddObject(PObject * pObject)
//{
//   m_vecPObject.push_back(pObject);
//}
//void CObjectManager::AddObject(IObject * iObject)
//{
//   m_vecIObject.push_back(iObject);
//}
//void CObjectManager::AddOBBbox(COBB * OBBBox)
//{
//   m_vecOBBBox.push_back(OBBBox);
//}
//void CObjectManager::AddGimmick(CGimmick * Gimmick)
//{
//   m_vecGimmick.push_back(Gimmick);
//}
//void CObjectManager::AddBox(CBox * Box)
//{
//   m_vecBox.push_back(Box);
//}
//vector<CObject*> CObjectManager::GetVecObject()
//{
//   return m_vecObject;
//}
//vector<IObject*> CObjectManager::GetVecIObject()
//{
//   return m_vecIObject;
//}
//
//vector<PObject*> CObjectManager::GetVecPObejct()
//{
//   return m_vecPObject;
//}
// Integrate CollisionSphereToBox(Rotation Error)
//void CObjectManager::CollisionSphereToIObject(CSphere * one, IObject * two, float duration)
//{
//	D3DXMATRIXA16 inverseBoxMatrix;
//	//D3DXMatrixInverse(&inverseBoxMatrix, NULL, &two->GetmatWorld());
//
//	D3DXMatrixIdentity(&inverseBoxMatrix);
//	inverseBoxMatrix._41 = -two->GetmatWorld()._41;
//	inverseBoxMatrix._42 = -two->GetmatWorld()._42;
//	inverseBoxMatrix._43 = -two->GetmatWorld()._43;
//
//	D3DXVECTOR3 SphereToBoxCenter;
//	D3DXVec3TransformCoord(&SphereToBoxCenter, &one->GetPosition(), &inverseBoxMatrix);
//
//	D3DXVECTOR3 closestPt(0, 0, 0);
//	float dist;
//
//	dist = SphereToBoxCenter.x;
//	if (dist > two->GetOBB()->GetOBBWidth()) dist = two->GetOBB()->GetOBBWidth();
//	if (dist < -two->GetOBB()->GetOBBWidth()) dist = -two->GetOBB()->GetOBBWidth();
//	closestPt.x = dist;
//
//	dist = SphereToBoxCenter.y;
//	if (dist >  two->GetOBB()->GetOBBHeight()) dist = two->GetOBB()->GetOBBHeight();
//	if (dist < -two->GetOBB()->GetOBBHeight()) dist = -two->GetOBB()->GetOBBHeight();
//	closestPt.y = dist;
//
//	dist = SphereToBoxCenter.z;
//	if (dist >  two->GetOBB()->GetOBBDepth()) dist = two->GetOBB()->GetOBBDepth();
//	if (dist < -two->GetOBB()->GetOBBDepth()) dist = -two->GetOBB()->GetOBBDepth();
//	closestPt.z = dist;
//
//	//dist = SphereToBoxCenter.x;
//	//if (dist > two->GetOBB()->GetOBBWidth() / 2.0f) dist = two->GetOBB()->GetOBBWidth() / 2.0f;
//	//if (dist < -two->GetOBB()->GetOBBWidth() / 2.0f) dist = -two->GetOBB()->GetOBBWidth() / 2.0f;
//	//closestPt.x = dist;
//	//dist = SphereToBoxCenter.y;
//	//if (dist >  two->GetOBB()->GetOBBHeight() / 2.0f) dist = two->GetOBB()->GetOBBHeight() / 2.0f;
//	//if (dist < -two->GetOBB()->GetOBBHeight() / 2.0f) dist = -two->GetOBB()->GetOBBHeight() / 2.0f;
//	//closestPt.y = dist;
//	//dist = SphereToBoxCenter.z;
//	//if (dist >  two->GetOBB()->GetOBBDepth() / 2.0f) dist = two->GetOBB()->GetOBBDepth() / 2.0f;
//	//if (dist < -two->GetOBB()->GetOBBDepth() / 2.0f) dist = -two->GetOBB()->GetOBBDepth() / 2.0f;
//	//closestPt.z = dist;
//
//	//SphereToBoxCenter.x *= two->GetmatWorld()._11;
//	//SphereToBoxCenter.y *= two->GetmatWorld()._22;
//	//SphereToBoxCenter.z *= two->GetmatWorld()._33;
//
//	D3DXVECTOR3 tmp = closestPt - SphereToBoxCenter;
//	dist = D3DXVec3Length(&tmp);
//
//	D3DXVECTOR3 closestPtWorld;
//	D3DXVec3TransformCoord(&closestPtWorld, &closestPt, &two->GetmatWorld());
//
//	D3DXVECTOR3 contactNormal = closestPtWorld - SphereToBoxCenter;                     // Need To Modify.. 1214 01:46
//																						// TEST
//	contactNormal.y = 0;
//	//D3DXVECTOR3 contactNormal = SphereToBoxCenter - closestPtWorld;
//	D3DXVec3Normalize(&contactNormal, &contactNormal);
//	float penetration = one->GetRadius() - sqrtf(dist);
//	float elasticity = 0.1f; // TEST
//
//	D3DXVECTOR3 relativeVelocity = one->GetVelocity();
//	float separatinVelocity = D3DXVec3Dot(&relativeVelocity, &contactNormal);
//	//if (separatinVelocity > 0) return;         // Need Modify? 1 = Elasticity          // Need To Modify.. 1214 01:46
//	float newSepVelocity = -separatinVelocity * elasticity;
//
//	D3DXVECTOR3 accCausedVelocity = one->GetAcceleration();                           // Need To Modify.. 1214 01:46
//	float accCausedSepVelocity = D3DXVec3Dot(&accCausedVelocity, &contactNormal) * duration;
//	// Need Modify? 1 = Elasticity
//	newSepVelocity += (elasticity * accCausedSepVelocity);
//
//	//D3DXVECTOR3 accCausedVelocity = one->GetAcceleration();                           // Need To Modify.. 1214 01:46
//	//float accCausedSepVelocity = D3DXVec3Dot(&accCausedVelocity, &contactNormal) * duration; 
//	//if (accCausedSepVelocity < 0)
//	//{                 // Need Modify? 1 = Elasticity
//	//   newSepVelocity += (elasticity * accCausedSepVelocity);
//	//   if (newSepVelocity < 0) newSepVelocity = 0.0f;
//	//}
//
//	float deltaVelocity = newSepVelocity - separatinVelocity;
//	if (one->GetInverseMass() <= 0) return;
//
//	float impulse = deltaVelocity / one->GetInverseMass();
//	D3DXVECTOR3 impulsePerIMass = contactNormal * impulse;
//
//	one->SetVelocity(one->GetVelocity() + impulsePerIMass * one->GetInverseMass());
//
//	//if (penetration <= 0) return;
//	D3DXVECTOR3 movePerIMass = contactNormal * (penetration / one->GetInverseMass());
//	one->SetPosition(one->GetPosition() + movePerIMass * one->GetInverseMass());
//}