#pragma once
#include "Object.h"
class CPSphere : public CObject
{
public:
	CPSphere();
	~CPSphere();
protected:
	float m_fRadius;
public:
	void Setup();
	void Update();
	void Render();

	void SetPickState(bool set);

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};