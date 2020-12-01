#pragma once
#include "IObject.h"


class COBB;
class CTile : public IObject
{
private:
	COBB* m_pOBB;

	D3DXMATRIXA16 matWorld;
public:
	CTile();
	~CTile();

	void Setup() { }
	void Setup(ST_MapData setData);
	void Update();
	void Render();
	
};

