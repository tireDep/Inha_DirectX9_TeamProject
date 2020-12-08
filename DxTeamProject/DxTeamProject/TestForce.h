#pragma once

class CTestForce
{
public:
	CTestForce();
	~CTestForce();
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vForceVector, ForceVector);	
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vForceLocation, ForceLocation);
};