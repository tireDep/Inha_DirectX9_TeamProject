#pragma once
#include "Object.h"
class CPSBox :
	public CObject
{
public:
	CPSBox();
	~CPSBox();
protected:
	float m_fWidth;
	float m_fDepth;
	float m_fHeight;
public:
	void Setup();
	void Update();
	void Render();

	void SetPickState(bool set);

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};