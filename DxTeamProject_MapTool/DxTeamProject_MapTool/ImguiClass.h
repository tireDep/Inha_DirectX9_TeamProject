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
		// >> 버전차이
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

	// >> testLoad
	D3DMATERIAL9 m_pMtrl;
	LPDIRECT3DTEXTURE9 m_pTexture;

	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);
	// << testLoad

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

