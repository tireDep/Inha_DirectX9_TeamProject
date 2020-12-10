#pragma once
#include "Object.h"
#include "OBB.h"

class IObject : public CObject
{
protected:
	//static int m_nRefCnt;
	//D3DXMATRIXA16 m_matWorld;
	//D3DMATERIAL9 m_pMtrl;
	//LPDIRECT3DTEXTURE9 m_pTexture;
	//Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	//Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);
	//Synthesize(DWORD, m_numMtrls, NumMtrl);
	//Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	//Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);
	//Synthesize(string, m_strObjName, ObjectName);
	//Synthesize(string, m_strFolder, FolderPath);
	//Synthesize(string, m_strXFile, XFilePath);
	//Synthesize(string, m_strTxtFile, XTxtPath);
	//Synthesize(ObjectType, m_ObjectType, ObjType);
	//Synthesize(D3DXVECTOR3, m_vScale, Scale);
	//Synthesize(D3DXVECTOR3, m_vRotate, Rotate);
	//Synthesize(D3DXVECTOR3, m_vTranslate, Translate);
	
	//COBB* m_pOBB;
	IObject();

	// OBB TEST
	COBB* m_pOBB;
public:
	virtual ~IObject();
	virtual void Release();

	virtual void Setup() = 0;
	virtual void Update(float duration) = 0;
	virtual void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos) { };
	virtual void Render() = 0;
	virtual string GetName() { return string(); }

	virtual COBB* GetOBB() { return m_pOBB; }
	//static void CreateObject(const ST_MapData& mapData);
};