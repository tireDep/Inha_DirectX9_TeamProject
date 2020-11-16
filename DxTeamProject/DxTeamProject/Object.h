#pragma once
#include "IListener.h"
#include "Ray.h"

struct ST_EVENT;

class CObject : public IListener
{
protected:
	static int  m_nRefCount;
	bool		m_isPicked;
	bool		m_isClicked;
	D3DXCOLOR	m_color;
	CObject();
public:
	virtual ~CObject(void);

	virtual void Release();

	virtual void Setup() = 0;
	virtual void Update(CRay ray) = 0;
	virtual void Render() = 0;

	virtual string GetName() { return string(); }
	virtual void ReceiveEvent(ST_EVENT eventMsg);

	virtual void SetColor(D3DXCOLOR ObjectColor);
	virtual D3DXCOLOR GetColor();
	virtual bool GetisClicked();
};