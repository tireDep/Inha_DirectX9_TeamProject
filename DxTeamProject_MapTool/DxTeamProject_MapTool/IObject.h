#pragma once

#include "Ray.h"

class IObject
{
protected:
	static int m_nRefCnt;

	D3DMATERIAL9 m_pMtrl;
	LPDIRECT3DTEXTURE9 m_pTexture;

	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	Synthesize(string, m_strObjName, ObjectName);

	Synthesize(string, m_strFolder, FolderPath);
	Synthesize(string, m_strXFile, XFilePath);
	Synthesize(string, m_strTxtFile, XTxtPath);

	Synthesize(ObjectType, m_ObjectType, ObjType);

	Synthesize(D3DXVECTOR3, m_vScale, Scale);
	Synthesize(D3DXVECTOR3, m_vRotate, Rotate);
	Synthesize(D3DXVECTOR3, m_vTranslate, Translate);

	Synthesize(bool, m_isClick, Click);
	Synthesize(bool, m_isPick, Pick);

	Synthesize(D3DXCOLOR, m_dxColor, Color);

	static LPD3DXEFFECT m_pShader;
	static bool isLoad;

	IObject();

	void SetShader(const D3DXMATRIXA16& setMatWorld);

public:
	virtual ~IObject();
	virtual void Release();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	// ray
	virtual void Update(CRay * ray);
	virtual void Render();

	virtual void SetDiffScale(D3DXVECTOR3 set) = 0;

	static void SetRefCnt(int set);
	static void CreateObject(const ObjectType objType, int index);
	static void CreateObject(const ST_MapData& mapData);
};

