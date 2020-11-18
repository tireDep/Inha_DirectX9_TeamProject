#pragma once
#include "IListener.h"
#include "Ray.h"

struct ST_EVENT;

class CObject : public IListener
{
protected:
	static int    m_nRefCount;
	bool		  m_isPicked;
	bool		  m_isClicked;
	D3DXCOLOR	  m_color;
	D3DXCOLOR	  m_outLineColor;
	D3DXMATRIXA16 m_matWorld;

	LPD3DXEFFECT m_pShader;
	bool LoadAssets();
	LPD3DXEFFECT LoadShader(const char *fileName);
	void SetShader(const D3DXMATRIXA16& setMatWorld);

	CObject();
public:
	virtual ~CObject(void);

	virtual void Release();

	virtual void Setup() = 0;
	virtual void Update(CRay ray, D3DXCOLOR& playerColor) = 0;
	virtual void Render() = 0;

	virtual string GetName() { return string(); }
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};