#pragma once
#include "Gimmick.h"

enum class RotationAxial
{
	Rotation_X, Rotation_Y, Rotation_Z, NONE = 999
};
class CRotationBoard : public CGimmick
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
	//Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	//Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);
	//Synthesize(DWORD, m_numMtrls, NumMtrl);
	//Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	//Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);
	//D3DXMATRIXA16 m_matWorld;
private:
	D3DXMATRIXA16 m_matS, m_matR, m_matT, m_matRotGimmick;
	RotationAxial rotationAxial;
	float m_fRotationSpeed;
	float m_fRotAngle;

	/// Need Map tool
	// Size : Use m_vScale
	// Rotation_axial : enum class RotationAxial
	// Rotation_Speed : m_fRotationSpeed
	// State - Stop : RotationAxial::None
public:
	CRotationBoard();
	~CRotationBoard();
	void Setup(ST_MapData setData);
	//void Setup(string folder, string file);
	void Update(float duration);
	void Render();
};