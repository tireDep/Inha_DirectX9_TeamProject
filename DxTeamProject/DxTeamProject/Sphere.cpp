#include "stdafx.h"
#include "Sphere.h"

CSphere::CSphere() 
	: m_fRadius(1.0f)
{
	m_strName = string("Sphere") + to_string(m_nRefCount);
}

CSphere::~CSphere()
{
}

void CSphere::Setup()
{
	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMesh, NULL);
	m_fBoundingSphere = m_fRadius;
	m_vInverseRotationInertia.x = 5.0f / (2 * GetMass() * m_fRadius * m_fRadius);
	m_vInverseRotationInertia.y = 5.0f / (2 * GetMass() * m_fRadius * m_fRadius);
	m_vInverseRotationInertia.z = 5.0f / (2 * GetMass() * m_fRadius * m_fRadius);
}

void CSphere::Setup(const ST_MapData & mapData)
{
	m_strObjName = mapData.strObjName;

	m_strFolder = mapData.strFolderPath;
	m_strXFile = mapData.strXFilePath;
	m_strTxtFile = mapData.strTxtPath;

	m_ObjectType = mapData.objType;

	D3DXVECTOR3 vScale, vRotate;
	vScale = mapData.vScale;
	vRotate = mapData.vRotate;
	m_vPosition = mapData.vTranslate;

	m_Color = mapData.dxColor;
	this->ChangeObjectColor();

	m_fRadius = vScale.x;
	m_fRadius = vScale.y;
	m_fRadius = vScale.z;

	Setup();

	// ============================================================

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(vRotate.x);
	v.y = D3DXToRadian(vRotate.y);
	v.z = D3DXToRadian(vRotate.z);

	// D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);
	D3DXMatrixRotationX(&matR, v.x);
	D3DXMatrixRotationY(&matR, v.y);
	D3DXMatrixRotationZ(&matR, v.z);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matR * matT;
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

string CSphere::GetName()
{
	return m_strName;
}