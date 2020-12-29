#include "stdafx.h"
#include "IObject.h"

IObject::IObject() :
	m_grayTxt(NULL),
	m_strConditionName(""),
	m_isCondition(false),
	m_pOBB(NULL),
	m_isCameraRender(true)
{
	ResetPosition = D3DXVECTOR3(0, 0, 0);
	PresentPosition = D3DXVECTOR3(0, 0, 0);
	D3DXMatrixIdentity(&m_matWorld);
	g_pObjectManager->AddObject(this);
	m_strName = "Iobject" + to_string(m_nRefCount);
}

bool IObject::CheckIsGetColorOrb()
{
	// >> 태그와 맞는 색상 오브가 있는지 판별
	// >> 하나라도 존재 하지 않을 경우 false
	for (int i = 0; i < m_vecColorTag.size(); i++)
	{
		if (!g_pGameManager->GetIsHasOrb(m_vecColorTag[i]))
			return false;
	}
	return true;
}

IObject::~IObject()
{
	SafeDelete(m_pOBB);
}

void IObject::Release()
{
	g_pObjectManager->RemoveObject(this);
	//IObject::m_nRefCnt -= 1;
}

void IObject::Update(CRay ray)
{
	D3DXVECTOR3* pVertices;

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);

	D3DXVECTOR3 m_vMin, m_vMax;
	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	// later.. rotation add
	m_vMin.x *= m_matWorld._11;			m_vMax.x *= m_matWorld._11;
	m_vMin.y *= m_matWorld._22;			m_vMax.y *= m_matWorld._22;
	m_vMin.z *= m_matWorld._33;			m_vMax.z *= m_matWorld._33;

	m_vMin.x += m_matWorld._41;			m_vMax.x += m_matWorld._41;
	m_vMin.y += m_matWorld._42;			m_vMax.y += m_matWorld._42;
	m_vMin.z += m_matWorld._43;			m_vMax.z += m_matWorld._43;

	if (D3DXBoxBoundProbe(&m_vMin, &m_vMax, &ray.GetOrigin(), &ray.GetDirection()) == true)
	{
		if (m_ObjectType < ObjectType::eTile13)
		{
			if (m_vMax.y >= 5.0f)
				m_isCameraRender = false;
			else
				m_isCameraRender = true;
		}
	}
	else
	{
		m_isCameraRender = true;
	}
	m_pMesh->UnlockVertexBuffer();
}

void IObject::ReceiveEvent(ST_EVENT eventMsg)
{
	if (m_strConditionName == "")
		return;

	else if (eventMsg.eventType == EventType::eConditionChange)
	{
		if (m_strConditionName == eventMsg.conditionName)
			m_isCondition = !eventMsg.isCondition;
	}
}