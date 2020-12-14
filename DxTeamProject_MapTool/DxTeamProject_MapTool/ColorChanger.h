#pragma once
#include "Gimmick.h"

class CColorChanger : public CGimmick
{
public:
	CColorChanger();
	~CColorChanger();

	void Setup(ST_MapData setData);
};

