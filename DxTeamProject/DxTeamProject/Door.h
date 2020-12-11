#pragma once
#include "Gimmick.h"

class CDoor : public CGimmick
{
	/// Iobject inheritance
	//static int m_nRefCnt;
	//D3DXMATRIXA16 m_matWorld;
	//D3DMATERIAL9 m_pMtrl;
	//LPDIRECT3DTEXTURE9 m_pTexture;
	//Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	//Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);
	//Synthesize(DWORD, m_numMtrls, NumMtrl);
	//Synthesize(vector<D3DMATERIAL9*>, m_vecMtrls, VecMtrls);
	//Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);
	//Synthesize(string, m_strObjName, ObjectName);
	//Synthesize(string, m_strFolder, FolderPath);
	//Synthesize(string, m_strXFile, XFilePath);
	//Synthesize(string, m_strTxtFile, XTxtPath);
	//Synthesize(ObjectType, m_ObjectType, ObjType);
	//Synthesize(D3DXVECTOR3, m_vScale, Scale);
	//Synthesize(D3DXVECTOR3, m_vRotate, Rotate);
	//Synthesize(D3DXVECTOR3, m_vTranslate, Translate);
private:
	// Need Map tool(Two Class? Need to Modify)
	// Size : Use m_vScale;
	// Opening_angle : m_fOpeningAngle;
	// Required_object : IsOpen(true, false)
		// Update(float, bool)
		// bool : switch ON/OFF
	D3DXMATRIXA16 m_matS, m_matR, m_matT, m_matRotGimmick;
	float m_fOpeningAngle;
	bool IsOpen;

	float m_fRotationSpeed;
	float m_fRotAngle;
	//Synthesize(ObjectType, m_ObjectType, ObjType);
	//D3DXMATRIXA16 m_matRotGimmick;
public:
	CDoor();
	~CDoor();
	void Setup(string folder, string file);
	void Setup(ST_MapData setData);
	void Update(float duration);
	void Update(float duration, bool isSwitchOn);

	void Render();
};