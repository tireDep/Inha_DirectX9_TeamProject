#pragma once

class CImguiClass
{
private:
	enum class LoadType 
	{ 
		eNull, eMap, 
		eBackground, eAutumnTree, eSummerTree, eWinterTree, 
#ifdef _DEBUG
		eInvisibleWall,
		// >> ��������
#endif // DEBUG
		eObject, 
		eGimmick, eBreakWall, eDoor, eRotateBoard, eColorChanger
	};
	enum class ColorType { eNull, eGray, eBlack, eWhite, eRed, eBlue, eGreen, eYellow };

	bool m_isReset;

	vector<string> m_vecItem;
	vector<ObjectType> m_vecObjType;
	string m_showItem;

	int m_FileLoadIndex;
	LoadType m_PreLoadType;
	LoadType m_NowLoadType;
	LoadType m_SubType;

	vector<ColorType> m_vecColor;
	ColorType m_PrecolorType;
	ColorType m_NowcolorType;

	void SetVecItem();
	void SetObjectColor();

public:
	static int m_nowSelectindex;
	static int m_prevSelectIndex;

	CImguiClass();
	~CImguiClass();

	void Setup();

	void Update();
	void Update_MenuTitleBar();
	void Update_Hiearachy();
	void Update_FileLoader();
	void Update_Inspector();

	void SetFrameEnd();
	void Render();

	void ResetDevice();
	void Destroy();
};

