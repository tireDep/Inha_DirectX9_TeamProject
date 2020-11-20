#include "stdafx.h"
#include "PhysicsObject.h"

int CPhysicsObject::m_nRefCount = 0;

CPhysicsObject::CPhysicsObject()
	: m_pMesh(NULL)
{
	CPhysicsObject::m_nRefCount += 1;
	g_pPhysicsObjectManager->AddPhysicsObject(this);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matLocal);
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
}

CPhysicsObject::~CPhysicsObject()
{
	//SafeRelease(m_pMesh);
}

void CPhysicsObject::Release()
{
	g_pPhysicsObjectManager->RemovePhysicsObject(this);
	CPhysicsObject::m_nRefCount -= 1;
}

void CPhysicsObject::ReceiveEvent(ST_EVENT eventMsg)
{

}