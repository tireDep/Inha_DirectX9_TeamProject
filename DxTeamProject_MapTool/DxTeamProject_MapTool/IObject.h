#pragma once

class IObject
{
protected:
	static int m_nRefCnt;

public:
	IObject();
	virtual ~IObject();
	virtual void Release();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

