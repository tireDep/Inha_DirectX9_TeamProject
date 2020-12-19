#pragma once
#include "Gimmick.h"
class CSwitch : public CGimmick
{
private:
	enum class WeightType { eBlack, eWhite, eYellow };
	WeightType m_weightType;

	// Synthesize(int, m_conditionIndex, ConditionIndex);

public:
	CSwitch();
	~CSwitch();

	virtual void Setup(ST_MapData setData);
	virtual void Render();

	virtual void SetTexture(int index);
	virtual int GetTextureIndex();

	void SetWeightIndex(int index);
	int GetWeightIndex();
};

