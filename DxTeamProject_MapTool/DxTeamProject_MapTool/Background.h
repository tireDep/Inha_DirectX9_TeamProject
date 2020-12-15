#pragma once
#include "IObject.h"

class CRay;

class CBackground : public IObject
{

public:
	 CBackground();
	 virtual ~CBackground();

	virtual void Setup();
	virtual void Setup(ST_MapData setData);
	virtual void Update();
	virtual void Render();

	virtual void SetDiffScale(D3DXVECTOR3 set);
	virtual int GetTextureIndex();
	virtual void SetTexture(int index);
};

