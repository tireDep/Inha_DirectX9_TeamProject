#pragma once

class CImguiClass
{
private:
	enum class LoadType { eNull, eMap, eBackground, eObject };

	bool m_isReset;

	vector<string> m_vecItem;
	vector<ObjectType> m_vecObjType;
	string m_showItem;

	int m_FileLoadIndex;
	LoadType m_PreLoadType;
	LoadType m_NowLoadType;

	void SetVecItem();

public:
	CImguiClass();
	~CImguiClass();

	void Setup();
	void Update();

	void SetFrameEnd();
	void Render();

	void ResetDevice();
	void Destroy();
};

