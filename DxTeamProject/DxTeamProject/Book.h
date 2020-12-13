#pragma once
#include "IObject.h"

class CSkinnedMesh;

class CBook : public IObject
{
private:
	static int m_nCount;
	float m_fRotationSpeed;
	float m_fRotAngle;
public:
	CBook();
	~CBook();
	void Setup();
	void Setup(ST_MapData setData);
	void Update(float duration);
	bool hasIntersected(CSkinnedMesh * Character);
	void Render();

	virtual void SetBool(bool set) { }
};