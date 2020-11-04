#pragma once
class cObject
{
private:

	
protected:
	ULONG m_ulRefCount;

public:
	cObject();

	virtual ~cObject(void);

	virtual void AddRef();
	virtual void Release();

};