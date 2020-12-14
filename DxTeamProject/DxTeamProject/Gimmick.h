#pragma once
#include "IObject.h"

class CGimmick : public IObject
{
protected:
	OnOffCondition	m_onOffCondition;
	CGimmick();
public:
	~CGimmick();
	virtual void Setup() { };
	
	static void Setup(const ST_MapData & mapData);
	void SetGimmickCondition(const ST_MapData & mapData);

	virtual void Update(float duration) = 0;
	virtual void Render() = 0;
	virtual string GetName() { return m_strName; }
};