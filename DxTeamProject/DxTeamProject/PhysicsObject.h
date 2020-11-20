#pragma once
#include "IListener.h"

struct ST_EVENT;

class CPhysicsObject : public IListener
{
protected:
	static int	m_nRefCount;
	
	D3DXMATRIXA16	m_matLocal;
	D3DXMATRIXA16	m_matWorld;
	D3DMATERIAL9	m_stMtl;
	LPD3DXMESH		m_pMesh;

	CPhysicsObject();
public:
	virtual ~CPhysicsObject(void);
	virtual void Release();
	virtual void Setup() = 0;
	virtual void Update(float duration) = 0;
	virtual void Render() = 0;

	virtual string GetName() { return string(); }
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};