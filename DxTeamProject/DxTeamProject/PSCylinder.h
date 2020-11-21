#pragma once
#include "Object.h"
class CPSCylinder :	public CObject
{
public:
	CPSCylinder();
	~CPSCylinder();
protected:
	float m_fRadius;
	float m_fHeight;
public:
	void Setup();
	void Update();
	void Render();

	void SetPickState(bool set);

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};