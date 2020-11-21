#pragma once
#include "Object.h"
class CPSBox : public CObject
{
public:
	CPSBox();
	~CPSBox();
protected:
	float m_fWidth;
	float m_fHeight;
	float m_fDepth;
	D3DXVECTOR3 m_vCenter;
public:
	void Setup();
	void Setup(D3DXVECTOR3 center);
	void Update(float duration);
	void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	void Render();

	void SetPickState(bool set);

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};