#pragma once
#include "stdafx.h"

class iMap
{
private:

public:
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) = 0;
	virtual void Render() = 0;

	virtual vector<D3DXVECTOR3> GetVecVertex() = 0;
	virtual void SetFrustumMap(const vector<bool>& vecCheck) = 0;
};