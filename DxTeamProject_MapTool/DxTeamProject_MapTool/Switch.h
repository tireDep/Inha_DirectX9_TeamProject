#pragma once
#include "Gimmick.h"
class CSwitch : public CGimmick
{
private:
	Synthesize(int, m_conditionIndex, ConditionIndex);

public:
	CSwitch();
	~CSwitch();

	virtual void Setup() { }
	virtual void Setup(ST_MapData setData);
	virtual void Setup_OBB_Box() {}

	virtual void Update() { }
	virtual void Render();

	virtual void SetTexture(int index);
	virtual int GetTextureIndex();

	virtual void SetConditionType();
	virtual void SetCondition();
};

