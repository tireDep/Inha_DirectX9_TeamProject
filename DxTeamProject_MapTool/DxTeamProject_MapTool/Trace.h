#pragma once
#include "Item.h"

class CTrace : public CItem
{
public:
	CTrace();
	~CTrace();

	void Setup(ST_MapData setData);
	void Render();

	void SetDiffScale(D3DXVECTOR3 set);

	void SetTranslate(D3DXVECTOR3 set);
};

