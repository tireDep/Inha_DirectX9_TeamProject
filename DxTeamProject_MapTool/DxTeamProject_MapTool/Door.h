#pragma once
#include "Gimmick.h"
class CDoor : public CGimmick
{
private:
	// todo : condition variable
	enum class OnOffCondition { eOrb, eItem, eSwitch };

	OnOffCondition	m_openCondition;

	int GetIndex();

public:
	CDoor();
	~CDoor();

	void Setup(ST_MapData setData);

	void Render();

	void SetAnotherScale(D3DXVECTOR3 set);
	void SetAnotherRotation(D3DXVECTOR3 set);
	void SetAnotherTranslation(D3DXVECTOR3 set);

	void SetOpenCondition(int index);
	void SetConditionName(string strName);

	int GetOpenConditionIndex();
	string GetOpenConditionType();
	string GetConditionName();
};

