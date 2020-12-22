#include "stdafx.h"
#include "IObject.h"
#include "Sphere.h"
#include "Box.h"
#include "Cylinder.h"

CSphere::CSphere() 
	: m_fRadius(0.5f)
{
	m_strName = string("Sphere") + to_string(m_nRefCount);
}

CSphere::~CSphere()
{
}

void CSphere::Setup()
{
	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 20, 10, &m_pMesh, NULL);
}

void CSphere::Setup(const ST_MapData & mapData)
{
	Setup();

	m_strObjName = mapData.strObjName;
	m_strFolder = mapData.strFolderPath;
	m_strXFile = mapData.strXFilePath;
	m_strTxtFile = mapData.strTxtPath;
	m_ObjectType = mapData.objType;

	m_vScale = mapData.vScale;
	m_vRotation = mapData.vRotate;
	m_vTranslation = mapData.vTranslate;
	m_vPosition = m_vTranslation;

	//---ÀúÀå
	saveRotation = mapData.vRotate;
	saveTranslation = mapData.vTranslate;

	m_Color = mapData.dxColor;
	ResetColor = mapData.dxColor;
	this->ChangeObjectColor();

	m_fRadius *= m_vScale.x;
	m_fBoundingSphere = m_fRadius;

	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&m_matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	D3DXMatrixTranslation(&m_matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = m_matS * m_matR * m_matT;

	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	g_pObjectManager->AddSphere(this);
}

void CSphere::Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
{
	if (D3DXSphereBoundProbe(&m_vPosition, m_fRadius, &ray.GetOrigin(), &ray.GetDirection()) == true)
	{
		m_isPicked = true;
		m_outLineColor = playerColor;
	}
	else
	{
		m_isPicked = false;
	}
	vecVPos.push_back(m_vPosition);
	vecIsPick.push_back(m_isPicked);
}

bool CSphere::hasIntersected(CSphere * otherSphere)
{
	if (this == otherSphere)
		return false;
	D3DXVECTOR3 direction = this->GetPosition() - otherSphere->GetPosition();
	if ((this->GetRadius() + otherSphere->GetRadius()) * (this->GetRadius() + otherSphere->GetRadius()) < D3DXVec3LengthSq(&direction))
		return false;
	return true;
}

bool CSphere::hasIntersected(CBox * otherBox)
{
	D3DXMATRIXA16 inverseBoxMatrix;
	D3DXMatrixInverse(&inverseBoxMatrix, NULL, &otherBox->GetmatWorld());

	D3DXVECTOR3 SphereToBoxCenter;
	D3DXVec3TransformCoord(&SphereToBoxCenter, &m_vPosition, &inverseBoxMatrix);

	if( fabsf(SphereToBoxCenter.x) - GetRadius() > otherBox->GetWidth()  / 2.0f ||
		fabsf(SphereToBoxCenter.y) - GetRadius() > otherBox->GetHeight() / 2.0f ||
		fabsf(SphereToBoxCenter.z) - GetRadius() > otherBox->GetDepth()  / 2.0f)
		return false;

	D3DXVECTOR3 closestPt(0, 0, 0);
	float dist;

	dist = SphereToBoxCenter.x;
	if (dist > otherBox->GetWidth() / 2.0f) dist = otherBox->GetWidth() / 2.0f;
	if (dist < -otherBox->GetWidth() / 2.0f) dist = -otherBox->GetWidth() / 2.0f;
	closestPt.x = dist;

	dist = SphereToBoxCenter.y;
	if (dist > otherBox->GetHeight() / 2.0f) dist = otherBox->GetHeight() / 2.0f;
	if (dist < -otherBox->GetHeight() / 2.0f) dist = -otherBox->GetHeight() / 2.0f;
	closestPt.y = dist;

	dist = SphereToBoxCenter.z;
	if (dist > otherBox->GetDepth() / 2.0f) dist = otherBox->GetDepth() / 2.0f;
	if (dist < -otherBox->GetDepth() / 2.0f) dist = -otherBox->GetDepth() / 2.0f;
	closestPt.z = dist;

	D3DXVECTOR3 tmp = closestPt - SphereToBoxCenter;
	dist = D3DXVec3LengthSq(&tmp);
	if (dist > GetRadius() * GetRadius())
		return false;
	return true;
}

bool CSphere::hasIntersected(CCylinder * otherCylinder)
{
	D3DXMATRIXA16 inverseBoxMatrix;
	D3DXMatrixInverse(&inverseBoxMatrix, NULL, &otherCylinder->GetmatWorld());

	D3DXVECTOR3 SphereToCylinderCenter;
	D3DXVec3TransformCoord(&SphereToCylinderCenter, &m_vPosition, &inverseBoxMatrix);

	if (fabsf(SphereToCylinderCenter.x) - GetRadius() > otherCylinder->GetRadius() / 2.0f ||
		fabsf(SphereToCylinderCenter.y) - GetRadius() > otherCylinder->GetHeight() / 2.0f ||
		fabsf(SphereToCylinderCenter.z) - GetRadius() > otherCylinder->GetRadius() / 2.0f)
		return false;

	D3DXVECTOR3 closestPt(0, 0, 0);
	float dist;

	dist = SphereToCylinderCenter.x;
	if (dist >  otherCylinder->GetRadius() / 2.0f) dist = otherCylinder->GetRadius() / 2.0f;
	if (dist < -otherCylinder->GetRadius() / 2.0f) dist = -otherCylinder->GetRadius() / 2.0f;
	closestPt.x = dist;

	dist = SphereToCylinderCenter.y;
	if (dist >  otherCylinder->GetHeight() / 2.0f) dist =  otherCylinder->GetHeight() / 2.0f;
	if (dist < -otherCylinder->GetHeight() / 2.0f) dist = -otherCylinder->GetHeight() / 2.0f;
	closestPt.y = dist;

	dist = SphereToCylinderCenter.z;
	if (dist >  otherCylinder->GetRadius() / 2.0f) dist = otherCylinder->GetRadius() / 2.0f;
	if (dist < -otherCylinder->GetRadius() / 2.0f) dist = -otherCylinder->GetRadius() / 2.0f;
	closestPt.z = dist;

	D3DXVECTOR3 tmp = closestPt - SphereToCylinderCenter;
	dist = D3DXVec3LengthSq(&tmp);
	if (dist > GetRadius() * GetRadius())
		return false;
	return true;
}

bool CSphere::hasIntersected(IObject * otherIObject)
{
	if (this->m_pOBB->IsCollision(otherIObject->GetOBB()))
		return true;
	else
		return false;
	//D3DXMATRIXA16 inverseBoxMatrix;
	////D3DXMatrixInverse(&inverseBoxMatrix, NULL, &otherIObject->GetOBB()->GetOBBWorldMatrix());
	// 		
	//D3DXMatrixIdentity(&inverseBoxMatrix);
	//inverseBoxMatrix._41 = -otherIObject->GetmatWorld()._41;
	//inverseBoxMatrix._42 = -otherIObject->GetmatWorld()._42;
	//inverseBoxMatrix._43 = -otherIObject->GetmatWorld()._43;
	//D3DXVECTOR3 SphereToBoxCenter;
	//D3DXVec3TransformCoord(&SphereToBoxCenter, &m_vPosition, &inverseBoxMatrix);
	//												
	////if (fabsf(SphereToBoxCenter.x) - GetRadius() > otherIObject->GetOBB()->GetOBBWidth()  ||
	////	fabsf(SphereToBoxCenter.y) - GetRadius() > otherIObject->GetOBB()->GetOBBHeight() ||
	////	fabsf(SphereToBoxCenter.z) - GetRadius() > otherIObject->GetOBB()->GetOBBDepth())
	////	return false;
	//if (fabsf(SphereToBoxCenter.x) - GetRadius() > otherIObject->GetOBB()->GetOBBWidth()  ||
	//	fabsf(SphereToBoxCenter.y) - GetRadius() > otherIObject->GetOBB()->GetOBBHeight() ||
	//	fabsf(SphereToBoxCenter.z) - GetRadius() > otherIObject->GetOBB()->GetOBBDepth())
	//	return false;
	//D3DXVECTOR3 closestPt(0, 0, 0);
	//float dist;
	//dist = SphereToBoxCenter.x;
	//if (dist > otherIObject->GetOBB()->GetOBBWidth()) dist = otherIObject->GetOBB()->GetOBBWidth();
	//if (dist < -otherIObject->GetOBB()->GetOBBWidth()) dist = -otherIObject->GetOBB()->GetOBBWidth();
	//closestPt.x = dist;
	//dist = SphereToBoxCenter.y;
	//if (dist >  otherIObject->GetOBB()->GetOBBHeight()) dist =  otherIObject->GetOBB()->GetOBBHeight();
	//if (dist < -otherIObject->GetOBB()->GetOBBHeight()) dist = -otherIObject->GetOBB()->GetOBBHeight();
	//closestPt.y = dist;
	//dist = SphereToBoxCenter.z;
	//if (dist >  otherIObject->GetOBB()->GetOBBDepth()) dist =  otherIObject->GetOBB()->GetOBBDepth();
	//if (dist < -otherIObject->GetOBB()->GetOBBDepth()) dist = -otherIObject->GetOBB()->GetOBBDepth();
	//closestPt.z = dist;
	//D3DXVECTOR3 tmp = closestPt - SphereToBoxCenter;
	//dist = D3DXVec3LengthSq(&tmp);
	//if (dist > GetRadius() * GetRadius())
	//	return false;
	//return true;
}

void CSphere::Update(float duration)
{
	PObject::Update(duration);
	m_pOBB->Update(&m_matWorld);
}

string CSphere::GetName()
{
	return m_strName;
}