#pragma once
#include "IObject.h"

class CItem : public IObject
{
protected:
	D3DXIMAGE_INFO m_stImageInfo;
	vector<ST_PT_VERTEX> m_vecVertex;

	CItem();

public:
	~CItem();

	virtual void Setup() {};
	virtual void Update(float duration) = 0;
	virtual void Render() = 0;

	virtual void Setup(ST_MapData setData);

	virtual void SetBool(bool setup) = 0; //��ȣ�ۿ� 
	virtual COBB* GetOBB() { return m_pOBB; }
	virtual void pBoxBool(bool set) = 0; //�ǿ�����Ʈ�� ��ȣ�ۿ�
	virtual void pCylinderBool(bool set) = 0;
	virtual	void pSphereBool(bool set) = 0;
};

