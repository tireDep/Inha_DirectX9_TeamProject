#pragma once
#include "Object.h"

const static D3DXVECTOR3 GRAVITY(0, -9.8f, 0);

class PObject :	public CObject
{
protected:
	/// Color
	Synthesize(D3DXCOLOR, m_Color, DxColor);
	bool		  m_isPicked;
	bool		  m_isClicked;
	D3DXCOLOR	  m_outLineColor;
	LPD3DXEFFECT  m_pShader;
	Color		  m_tmpColor;
	bool LoadAssets();
	void SetShader(const D3DXMATRIXA16& setMatWorld);

public:
	PObject();
	~PObject();

	virtual void Setup() = 0;
	// Color
	virtual void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	virtual void ReceiveEvent(ST_EVENT eventMsg);
	virtual void OutlineRender();
	virtual void SetPickState(bool PickState);
	virtual void ChangeObjectColor();

	// Physics
	virtual void Update(float duration) = 0;

	// Delete
	virtual void Update3D(float duration) = 0;
	virtual void Update(float duration, CHeight* pMap) = 0;
	virtual void SetPusingForce(D3DXVECTOR3 forcedirection) = 0;
	virtual void AddForce(const D3DXVECTOR3 & force) = 0;
	virtual void ClearAccumulator() = 0;
	virtual void Integrate(float duration) = 0;
	virtual void RunPhysics(float duration) = 0;
	virtual bool hasIntersected(CObject * otherobject) = 0;
	virtual void CollisionOtherObject(CObject * otherobject) = 0;

	virtual void Render();
};