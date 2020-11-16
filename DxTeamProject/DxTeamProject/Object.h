#pragma once
#include "IListener.h"
#include "Ray.h"

struct ST_EVENT;

class CObject : public IListener
{
protected:
	static int m_nRefCount;

	CObject();

public:
	virtual ~CObject(void);

	virtual void Release();

	virtual void Setup() = 0;
	virtual void Update(CRay ray) = 0;
	virtual void Render() = 0;

	virtual string GetName() { return string(); }
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};

