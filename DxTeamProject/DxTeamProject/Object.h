#pragma once
class CObject
{
public:
	CObject();
	//~cObject();
protected:
	ULONG m_ulRefCount;
public:
	virtual ~CObject(void);

	virtual	void AddRef();
	virtual void Release();
};

