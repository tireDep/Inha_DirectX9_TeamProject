#pragma once

template<typename T> class CSingleton
{
protected:
	CSingleton() {}

public:
	static T* GetInstance()
	{
		static T instance;
		return &instance;
	}

	virtual ~CSingleton() {}
};

