#pragma once
#include "IListener.h"
#include "Ray.h"

struct ST_EVENT;

class CObject : public IListener
{
protected:
	static int    m_nRefCount;

	LPD3DXMESH	  m_pMesh;
	D3DXMATRIXA16 m_matWorld;

	bool		  m_isPicked;
	bool		  m_isClicked;
	D3DXCOLOR	  m_Color;
	D3DXCOLOR	  m_outLineColor;
	D3DMATERIAL9  m_stMtl;
	LPD3DXEFFECT  m_pShader;

	bool LoadAssets();
	void SetShader(const D3DXMATRIXA16& setMatWorld);

	// tmp physics
	Synthesize(float, m_fRadius, Radius);
	Synthesize(float, m_finverseMass, InverseMass);
	Synthesize(float, m_fDamping, Damping);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vPosition, Position);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vVelocity, Velocity);
	CObject();
public:
	virtual ~CObject();
	virtual void Release();

	virtual void Setup() = 0;
	virtual void Update(float duration) = 0;
	virtual void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos) = 0;
	virtual void Render() = 0;
	virtual void SetPickState(bool set) = 0;
	virtual void OutlineRender();

	virtual string GetName() { return string(); }
	virtual void ReceiveEvent(ST_EVENT eventMsg);

	// tmp physics
	virtual bool hasIntersected(CObject * otherobject) = 0;
	virtual void CollisionOtherObject(CObject * otherobject) = 0;
};