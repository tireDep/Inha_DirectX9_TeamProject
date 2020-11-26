#include "stdafx.h"
#include "Object.h"

CObject::CObject()
{
	m_vScale = D3DXVECTOR3(1, 1, 1);
	m_vRotate = D3DXVECTOR3(0, 0, 0);
	m_vTranslate = D3DXVECTOR3(0, 0.5f, 0);

	ZeroMemory(&m_pMtrl, sizeof(D3DMATERIAL9));
	m_pMtrl.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_pMtrl.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_pMtrl.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	m_dxColor = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
}

CObject::~CObject()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_pTexture);
}

void CObject::Setup()
{
}

void CObject::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;

	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;

	m_ObjectType = setData.objType;

	m_vScale = setData.vScale;
	m_vRotate = setData.vRotate;
	m_vTranslate = setData.vTranslate;

	m_dxColor = setData.dxColor;
}

void CObject::Update()
{
}

void CObject::Render()
{
	m_pMtrl.Ambient = m_dxColor;
	m_pMtrl.Specular = m_dxColor;
	m_pMtrl.Diffuse = m_dxColor;

	g_pD3DDevice->SetMaterial(&m_pMtrl);
	g_pD3DDevice->SetTexture(0, NULL);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(m_vRotate.x);
	v.y = D3DXToRadian(m_vRotate.y);
	v.z = D3DXToRadian(m_vRotate.z);

	D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);

	D3DXMatrixTranslation(&matT, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);
	matWorld = matS * matR * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	if (m_pMesh == NULL)
		return;

	m_pMesh->DrawSubset(0);
}
