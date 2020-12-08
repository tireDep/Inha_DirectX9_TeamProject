#pragma once
#include "IObject.h"
#include "PSOBB.h"

class CGimmick : public IObject
{
protected:
	CPSOBB* m_pOBB;
	CGimmick();
public:
	~CGimmick();
	virtual void Setup() { };
	static void Setup(ST_MapData setData);
	virtual void Update(float duration) = 0;
	virtual void Render() = 0;
	virtual string GetName() { return m_strName; }

	// OBB TEST
	virtual CPSOBB* GetOBB() { return m_pOBB; }
};