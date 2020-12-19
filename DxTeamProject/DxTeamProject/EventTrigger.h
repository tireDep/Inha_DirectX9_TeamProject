#pragma once
#include "IObject.h"

class CEventTrigger : public IObject
{
private:
	enum class TriggerType { eSave, eZone };
	TriggerType m_triggerType;
	bool player;
	D3DXVECTOR3 triggerpos;
public:
	CEventTrigger();
	~CEventTrigger();

	virtual void Setup() { };
	virtual void Setup(ST_MapData setData);
	virtual void Update(float duration);
	virtual void Render();

	virtual bool GetBool() { return true; };
	virtual void SetBool(bool setup) { player = setup; } //��ȣ�ۿ� 
	virtual void pBoxBool(bool set) { }; //�ǿ�����Ʈ�� ��ȣ�ۿ�
	virtual void pCylinderBool(bool set) { };
	virtual	void pSphereBool(bool set) { };

	void TriggerPosition(D3DXVECTOR3 pos) { pos = triggerpos ; }
	D3DXVECTOR3 SendPosition() { return triggerpos; }
	
	string GetTriggerTypeString();
};

