#pragma once
#include "IObject.h"

class CItem : public IObject
{
protected:
	D3DXIMAGE_INFO m_stImageInfo;
	vector<ST_PT_VERTEX> m_vecVertex;

	float m_UvX;
	float m_UvY;

	CItem();
public:
	virtual ~CItem();

	virtual void Setup() { };
	virtual void Update() { };

	virtual void Setup(ST_MapData setData);
	virtual void Render();
	virtual void Render_Sprite();

	virtual int GetSpriteIndex();
	virtual void SetSpriteIndex(int index);

	// ray
	// virtual void Update(CRay * ray) { }
	// virtual void Setup_OBB_Box() { }
	// virtual void Render_OBB_Box() { }
};

