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

	/// Color
	//bool		  m_isPicked;
	//bool		  m_isClicked;
	//D3DXCOLOR	  m_outLineColor;
	//LPD3DXEFFECT  m_pShader;
	//bool LoadAssets();
	//void SetShader(const D3DXMATRIXA16& setMatWorld);
	//Synthesize(D3DXCOLOR, m_Color, DxColor);
	//Color		  m_tmpColor;

	/// Physics
	//	Synthesize(bool, m_isForceApplied, ForceApplied);
	//	Synthesize(float, m_finverseMass, InverseMass);	// mass
	//	Synthesize(D3DXVECTOR3, m_vRotationInertia, RotationInertia);	// Rotation Inertia;
	// force
	//Synthesize(D3DXVECTOR3, m_vForceAccum, ForceAccum);
	//Synthesize(D3DXVECTOR3, m_vForceVector, ForceVector);
	//Synthesize(D3DXVECTOR3, m_vForceLocation, ForceLocation);
	// linear
	//Synthesize(D3DXVECTOR3, m_vPosition, Position);	// center position
	//Synthesize(D3DXVECTOR3, m_vLinearVelocity, LinearVelocity); // velocity
	//Synthesize(D3DXVECTOR3, m_vLinearAcceleration, LinearAcceleration); // acceleration
	//Synthesize(float, m_fDamping, Damping);	// floating point error
	//Synthesize(float, m_fLinearDrag, Drag);	// linear drag
	//Synthesize(D3DXVECTOR3, m_vLastFrameAcceleration, LastFrameAcceleration);
	// rotation
	//CTestAngleSet m_stOrientation; // Orientation
	//Synthesize(D3DXVECTOR3, m_vAngularVelocity, AngularVelocity); // Angular Velocity
	//Synthesize(D3DXVECTOR3, m_vAngularAcceleration, AngularAcceleration);	// Angular Accerleration
	//Synthesize(D3DXVECTOR3, m_vTorque, Torque);	// Torque;
	// collision
	//Synthesize(float, m_fBoundingSphere, BoundingSphere);	// collision radius
	//Synthesize(float, m_fElasticity, Elasticity); // elasticity
	//Synthesize(float, m_fMotion, Motion);
	//bool m_isAwake;
	//Synthesize(bool, m_canSleep, Sleep);
	// =========================================================================
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
	/// Color
	//virtual void ReceiveEvent(ST_EVENT eventMsg);
	//virtual void OutlineRender();
	//virtual void SetPickState(bool set) = 0;
	//virtual void ChangeObjectColor();

	/// Physics
	//virtual void Update3D(float duration) = 0;
	//virtual void Update(float duration , CHeight* pMap) = 0;
	//virtual void SetMass(const float mass);
	//virtual float GetMass() const;
	//virtual bool hasFiniteMass() const;
	//virtual void SetOrientation(CTestAngleSet Orientation);
	//virtual CTestAngleSet GetOrientation();
	//virtual void SetPusingForce(D3DXVECTOR3 forcedirection) = 0;
	//virtual void AddForce(const D3DXVECTOR3 & force) = 0;
	//virtual void ClearAccumulator() = 0;
	//virtual void Integrate(float duration) = 0;
	//virtual void RunPhysics(float duration) = 0;
	//virtual bool hasIntersected(CObject * otherobject) = 0;
	//virtual void CollisionOtherObject(CObject * otherobject) = 0;
	//virtual bool GetAwake() const;
	//virtual void SetAwake(const bool awake = true);
};