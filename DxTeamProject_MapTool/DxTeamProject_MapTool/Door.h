#pragma once
#include "Gimmick.h"
class CDoor : public CGimmick
{
private:
	Synthesize(bool, m_isAnotherClick, IsAnotherClick);

	int GetIndex();

public:
	CDoor();
	~CDoor();

	void Setup(ST_MapData setData);

	void Update();

	void Render() override;

	void SetAnotherScale(D3DXVECTOR3 set);
	void SetAnotherRotation(D3DXVECTOR3 set);
	void SetAnotherTranslation(D3DXVECTOR3 set);

	void SetOpenCondition(int index) override;
	void SetConditionName(string strName) override;

	void SetTexture(int index) override;
};

