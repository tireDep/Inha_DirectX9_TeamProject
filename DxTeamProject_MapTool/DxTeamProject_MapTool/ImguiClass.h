#pragma once

class CImguiClass
{
private:
	enum class LoadType { eNull, eMap, eBackground, eObject };
	enum class ColorType { eNull, eGray, eBlack, eWhite, eRed, eBlue, eGreen, eYellow };

	bool m_isReset;

	vector<string> m_vecItem;
	vector<ObjectType> m_vecObjType;
	string m_showItem;

	int m_FileLoadIndex;
	LoadType m_PreLoadType;
	LoadType m_NowLoadType;

	vector<ColorType> m_vecColor;
	ColorType m_PrecolorType;
	ColorType m_NowcolorType;

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

