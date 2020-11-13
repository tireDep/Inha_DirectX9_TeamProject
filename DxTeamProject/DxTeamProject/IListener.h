#pragma once

struct ST_EVENT;

class IListener
{
protected:
	string m_strName;

public:
	virtual ~IListener() { }
	virtual void ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam) { }
	virtual string GetName() { return string(); }

	virtual void ReceiveEvent(ST_EVENT eventMsg);
};
