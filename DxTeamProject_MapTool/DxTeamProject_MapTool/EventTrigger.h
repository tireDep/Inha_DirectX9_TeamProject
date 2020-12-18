#pragma once
#include "IObject.h"

class CEventTrigger : public IObject
{
private:
	enum class TriggerType { eSave, eZone };
	TriggerType m_triggerType;

	void SetMaterialColor(float r, float g, float b, float a);

public:
	CEventTrigger();
	~CEventTrigger();

	void Setup() { }
	void Update() { }

	void Setup(ST_MapData setData);
	void Render();

	void SetTriggerIndex(int index);
	int GetTriggerIndex();
	string GetTriggerType();
};

