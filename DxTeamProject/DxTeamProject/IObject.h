#pragma once
#include "Object.h"
#include "OBB.h"

class IObject : public CObject
{
protected:
	Synthesize(string, m_strConditionName, ConditionName);
	// Synthesize(int, m_conditionOrbindex, ConditionOrbIndex); // �ʿ��������?
	Synthesize(bool, m_isCondition, Condition);
	// >> On/Off ���� ����

	vector<string> m_vecColorTag;
	bool CheckIsGetColorOrb();
	D3DXVECTOR3 ResetPosition;
	D3DXVECTOR3 PresentPosition;
	COBB* m_pOBB;
	IObject();
public:
	virtual ~IObject();
	virtual void Release();

	virtual void Setup() = 0;
	virtual void Update(float duration) = 0;
	virtual void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos) { };
	virtual void Render() = 0;
	virtual string GetName() { return m_strName; }
	virtual void SetBool(bool setup) = 0; //��ȣ�ۿ� 
	virtual bool GetBool() = 0;
	virtual COBB* GetOBB() { return m_pOBB; }
	virtual void pBoxBool(bool set) = 0; //�ǿ�����Ʈ�� ��ȣ�ۿ�
	virtual void pCylinderBool(bool set) = 0;
	virtual	void pSphereBool(bool set) = 0;
	virtual void ReceiveEvent(ST_EVENT eventMsg);
	virtual ZoneType ZoneIndex() { return ZoneType(); }
	virtual D3DXVECTOR3 SendPosition() = 0;
};