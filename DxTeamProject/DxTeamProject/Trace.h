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

	virtual void SetBool(bool setup) { }; //��ȣ�ۿ� 
	virtual void pBoxBool(bool set) { }; //�ǿ�����Ʈ�� ��ȣ�ۿ�
	virtual void pCylinderBool(bool set) { };
	virtual	void pSphereBool(bool set) { };
	bool GetBool() { return render; }
};

