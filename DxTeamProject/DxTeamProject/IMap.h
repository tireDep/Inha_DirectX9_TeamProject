#pragma once

class IMap
{
public:
	virtual void Setup() = 0;
	virtual void Render() = 0;
	virtual void CalcFrustumMap(const vector<bool>& vecCheck) = 0;
};

