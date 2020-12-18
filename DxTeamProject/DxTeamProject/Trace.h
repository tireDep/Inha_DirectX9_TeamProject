#pragma once
#include "Item.h"

class CTrace : public CItem
{
private:
	bool render;
public:
	CTrace();
	~CTrace();

	virtual void Update(float duration) { };
	virtual void Render();

	virtual void Setup(ST_MapData setData);

	virtual void SetBool(bool setup) { }; //상호작용 
	virtual void pBoxBool(bool set) { }; //피오브젝트와 상호작용
	virtual void pCylinderBool(bool set) { };
	virtual	void pSphereBool(bool set) { };
	bool GetBool() { return render; }
};

