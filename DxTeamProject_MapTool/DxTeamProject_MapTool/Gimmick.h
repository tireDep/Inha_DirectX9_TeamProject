#pragma once
#include "IObject.h"

class CGimmick : public IObject
{
protected:
	CGimmick();

public:
	virtual ~CGimmick();

	virtual void Setup() = 0;
	virtual void Setup(ST_MapData setData) = 0;
	virtual void Setup_OBB_Box() = 0;

	virtual void Update() = 0;

	// virtual void Update(CRay * ray) { IObject::Update(ray); };
	virtual void Render() = 0;
	virtual void Render_OBB_Box() { IObject::Render_OBB_Box(); }

	virtual void SetDiffScale(D3DXVECTOR3 set);

	virtual int GetTextureIndex() { return int(); }
	virtual void SetTexture(int index) { }

	static void CreateGimmick(const ObjectType& objType);
	static void CreateGimmick_SaveData(ST_MapData& mapData);
};

