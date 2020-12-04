#pragma once
#include "IListener.h"
#include "Ray.h"
#include "CHeight.h"
#include "TestAngleSet.h"

enum ObjectType;
struct ST_MapData;
struct ST_EVENT;

const static D3DXVECTOR3 GRAVITY(0, -9.8f, 0);

class CObject : public IListener
{
protected:
	static int    m_nRefCount;

	bool		  m_isPicked;
	bool		  m_isClicked;
	D3DXCOLOR	  m_outLineColor;
	LPD3DXEFFECT  m_pShader;

	bool LoadAssets();
	void SetShader(const D3DXMATRIXA16& setMatWorld);

	// physics
	Synthesize(bool, m_isForceApplied, ForceApplied);
	Synthesize(float, m_finverseMass, InverseMass);	// mass
	Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matWorld, matWorld);

	// force
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vForceAccum, ForceAccum);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vForceVector, ForceVector);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vForceLocation, ForceLocation);

	// linear
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vPosition, Position);	// center position
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vLinearVelocity, LinearVelocity); // velocity
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vLinearAcceleration, LinearAcceleration); // acceleration
	Synthesize(float, m_fDamping, Damping);	// floating point error
	Synthesize(float, m_fLinearDrag, Drag);	// linear drag

	// rotation
	CTestAngleSet m_stOrientation; // Orientation
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vAngularVelocity, AngularVelocity); // Angular Velocity
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vAngularAcceleration, AngularAcceleration);	// Angular Accerleration
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vRotationInertia, RotationInertia);	// Rotation Inertia;
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vTorque, Torque);	// Torque;

	// collision
	Synthesize(float, m_fBoundingSphere, BoundingSphere);	// collision radius
	Synthesize(float, m_fElasticity, Elasticity); // elasticity

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
	virtual void Update3D(float duration) = 0;
	virtual void Update(float duration , CHeight* pMap) = 0;
	virtual void UpdateLand(float duration);
	virtual void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos) = 0;
	virtual void Render() = 0;
	virtual void SetPickState(bool set) = 0;
	virtual void OutlineRender();

	virtual string GetName() { return string(); }
	virtual void ReceiveEvent(ST_EVENT eventMsg);

	// physics
	virtual void SetMass(const float mass);
	virtual float GetMass() const;
	virtual bool hasFiniteMass() const;
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