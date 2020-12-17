#pragma once
#include "Item.h"

class COrb : public CItem
{
public:
	COrb();
	~COrb();

	void Setup(ST_MapData setData);
	void Render();
	void SetBillBoard();

	void SetDiffScale(D3DXVECTOR3 set);
};
