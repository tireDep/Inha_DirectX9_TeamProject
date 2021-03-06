#pragma once

#include "Ray.h"
#include "OBB.h"

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
	// >> 현재 클릭한 오브젝트

	Synthesize(D3DXCOLOR, m_dxColor, Color);
	// >> 색상 변수

	Synthesize(string, m_strConditionName, ConditionName);
	Synthesize(int, m_conditionOrbindex, ConditionOrbIndex);
	// >> On/Off 조건 변수

	Synthesize(vector<string>, m_vecColorTag, VecColorTag);
	// >> 태그
	// >> 배경 오브젝트만 사용, 편의를 위해 상위에 선언

	LPD3DXEFFECT m_pShader;
	bool isLoad;

	COBB* m_pOBB;

	IObject();

	void SetShader(const D3DXMATRIXA16& setMatWorld);
	void SetShaderColor(const D3DXVECTOR4& outLine, const D3DXVECTOR4& inner);
	// void SetShader_ConditionColor();

public:
	virtual ~IObject();
	virtual void Release();

	virtual void Setup() = 0;
	virtual void Setup(ST_MapData setData) = 0;
	virtual void Setup_OBB_Box();

	virtual void Update() = 0;
	// ray
	virtual bool Update(CRay * ray);
	virtual void Render();
	virtual void Render_OBB_Box();

	virtual void SetDiffScale(D3DXVECTOR3 set);
	virtual D3DXMATRIXA16 GetmatWorld();

	static void SetRefCnt(int set);
	static int GetRefCnt();
	static void CreateObject(const ObjectType& objType, int index);
	static void CreateObject(ST_MapData& mapData);
};

