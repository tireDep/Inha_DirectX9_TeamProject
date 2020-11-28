#pragma once
#include "IListener.h"
#include "Ray.h"
#include "CHeight.h"

enum ObjectType;
struct ST_MapData;
struct ST_EVENT;

class CObject : public IListener
{
protected:
	static int    m_nRefCount;

	// LPD3DXMESH	  m_pMesh;
	//D3DXMATRIXA16 m_matWorld;

	bool		  m_isPicked;
	bool		  m_isClicked;
	// D3DXCOLOR	  m_Color;
	D3DXCOLOR	  m_outLineColor;
	// D3DMATERIAL9  m_stMtl;
	LPD3DXEFFECT  m_pShader;

	bool LoadAssets();
	void SetShader(const D3DXMATRIXA16& setMatWorld);

	// tmp physics
	Synthesize(bool, m_isForceApplied, ForceApplied);
	Synthesize(float, m_fRadius, Radius);	// collision radius
	Synthesize(float, m_finverseMass, InverseMass);	// mass
	Synthesize(float, m_fDamping, Damping);	// floating point error
	Synthesize(float, m_fDrag, Drag);	// drag
	Synthesize(float, m_fElasticity, Elasticity); // elasticity
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vPosition, Position);	// center position
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vVelocity, Velocity); // velocity
	Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matWorld, matWorld);

	// =========================================================================

	D3DMATERIAL9 m_stMtl;
	LPDIRECT3DTEXTURE9 m_pTexture;

	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9*>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	Synthesize(string, m_strObjName, ObjectName);

	Synthesize(string, m_strFolder, FolderPath);
	Synthesize(string, m_strXFile, XFilePath);
	Synthesize(string, m_strTxtFile, XTxtPath);

	Synthesize(ObjectType, m_ObjectType, ObjType);

	// Synthesize(D3DXVECTOR3, m_vScale, Scale);
	// Synthesize(D3DXVECTOR3, m_vRotate, Rotate);
	// Synthesize(D3DXVECTOR3, m_vTranslate, Translate);

	Synthesize(D3DXCOLOR, m_Color, DxColor);


	// tmp Color change
	Color		  m_tmpColor;
	CObject();
public:
	virtual ~CObject();
	virtual void Release();

	virtual void Setup() = 0;
	virtual void Update(float duration) = 0;
	virtual void Update(float duration , CHeight* pMap) = 0;
	virtual void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos) = 0;
	virtual void Render() = 0;
	virtual void SetPickState(bool set) = 0;
	virtual void OutlineRender();

	virtual string GetName() { return string(); }
	virtual void ReceiveEvent(ST_EVENT eventMsg);

	// tmp physics
	virtual void SetMass(const float mass) = 0;
	virtual float GetMass() const = 0;
	virtual bool hasFiniteMass() const = 0;
	virtual void SetPusingForce(D3DXVECTOR3 forcedirection) = 0;
	virtual void AddForce(const D3DXVECTOR3 & force) = 0;
	virtual void ClearAccumulator() = 0;
	virtual void Integrate(float duration) = 0;
	virtual void RunPhysics(float duration) = 0;
	virtual bool hasIntersected(CObject * otherobject) = 0;
	virtual void CollisionOtherObject(CObject * otherobject) = 0;

	static void CreateObject(const ST_MapData& mapData);

	// color change
	virtual void ChangeObjectColor();
};