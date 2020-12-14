#pragma once
#include "IObject.h"

class CGimmick : public IObject
{
protected:
	OnOffCondition	m_openCondition;

	CGimmick();

public:
	virtual ~CGimmick();

	virtual void Setup() { }
	virtual void Setup(ST_MapData setData);
	virtual void Setup_OBB_Box() { };

	virtual void Update() { };

	virtual void Render();

	virtual void SetDiffScale(D3DXVECTOR3 set);

	virtual int GetTextureIndex() { return int(); }
	virtual void SetTexture(int index) { }

	static void CreateGimmick(const ObjectType& objType);
	static void CreateGimmick_SaveData(ST_MapData& mapData);
};

