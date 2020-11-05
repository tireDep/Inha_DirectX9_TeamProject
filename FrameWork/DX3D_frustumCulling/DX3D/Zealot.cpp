#include "stdafx.h"
#include "Zealot.h"

#include "SkinnedMesh.h"
#include "OBB.h"

CZealot::CZealot() :
	m_pSkinnedMesh(NULL),
	m_pCharacterController(NULL),
	m_pOBB(NULL)
{
	
}

CZealot::~CZealot()
{
	SafeRelease(m_pCharacterController);
	SafeDelete(m_pSkinnedMesh);
	SafeDelete(m_pOBB);
}

void CZealot::SetUp()
{
	m_pSkinnedMesh = new CSkinnedMesh("xFile/Zealot", "zealot.x");
	m_pSkinnedMesh->SetRandomTrackPosition();

	m_pOBB = new COBB;
	m_pOBB->SetUp(m_pSkinnedMesh);
}

void CZealot::Update(iMap * pMap)
{
	if (m_pCharacterController)
		m_pCharacterController->Update(pMap);

	if (m_pOBB)
		m_pOBB->Update(m_pCharacterController ? m_pCharacterController->GetTransform() : NULL);
}

void CZealot::Render(D3DCOLOR c)
{
	if (m_pCharacterController)
		m_pSkinnedMesh->SetTransform(m_pCharacterController->GetTransform());

	m_pSkinnedMesh->UpdateAndRender();

	if (m_pOBB)
		m_pOBB->Render_OBB_BOX(c);
}

COBB * CZealot::GetOBB()
{
	return m_pOBB;
}
