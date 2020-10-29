#pragma once

template<typename T> class CSingleton
{
private:

protected:
	CSingleton() { }

public:
	virtual ~CSingleton() { }

	static T* GetInstance()
	{
		static T instance;
		return &instance;
	}

};
