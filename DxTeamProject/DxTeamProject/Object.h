#pragma once
#include "IListener.h"
#include "Ray.h"

enum ObjectType;
struct ST_MapData;
struct ST_EVENT;

class CObject : public IListener
{
protected:
	static int    m_nRefCount;
	Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matWorld, matWorld);
	Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matS, matS);
	Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matT, matT);
	Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matR, matR);

	Synthesize(D3DXVECTOR3, m_vScale, Scale);
	Synthesize(D3DXVECTOR3, m_vRotation, Rotation);
	Synthesize(D3DXVECTOR3, m_vTranslation, Translation);

	D3DMATERIAL9 m_stMtl;
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

	CObject();
public:
	virtual ~CObject();
	virtual void Release();

	virtual void Setup() = 0;
	static void CreateObject(const ST_MapData& mapData);
	virtual void Update(float duration) = 0;
	virtual void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos) = 0;
	virtual void Render() = 0;

	virtual string GetName() { return m_strName; }
};