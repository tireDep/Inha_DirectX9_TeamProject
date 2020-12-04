#include "stdafx.h"
#include "Background.h"

CBackground::CBackground()
{
	m_pMesh = NULL;
	m_pTexture = NULL;
}

CBackground::~CBackground()
{
}

void CBackground::Setup()
{
}

void CBackground::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;
	m_vScale = setData.vScale;
	m_vRotate = setData.vRotate;
	m_vTranslate = setData.vTranslate;

	ST_XFile* xfile = new ST_XFile;

	g_pFileLoadManager->FileLoad_XFile(m_strFolder, m_strXFile, xfile);

	if (m_strTxtFile != "")
		g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	delete xfile;
}

void CBackground::Update()
{

}

void CBackground::Update(CRay * ray)
{
	IObject::Update(ray);
}

void CBackground::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(m_vRotate.x);
	v.y = D3DXToRadian(m_vRotate.y);
	v.z = D3DXToRadian(m_vRotate.z);

	// D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);
	
	D3DXMATRIXA16 matX, matY, matZ;
	D3DXMatrixIdentity(&matX);
	D3DXMatrixIdentity(&matY);
	D3DXMatrixIdentity(&matZ);

	D3DXMatrixRotationX(&matX, v.x);
	D3DXMatrixRotationY(&matY, v.y);
	D3DXMatrixRotationZ(&matZ, v.z);

	matR = matX * matY * matZ;

	D3DXMatrixTranslation(&matT, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);
	matWorld = matS * matR * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	if (m_pMesh == NULL)
		return;

	g_pD3DDevice->SetTexture(0, m_pTexture);

	if (!m_isPick && !m_isClick || !m_pShader)
	{
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
			m_pMesh->DrawSubset(i);
		}
	}
	else
	{
		SetShader(matWorld);
		IObject::Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
}

void CBackground::SetDiffScale(D3DXVECTOR3 set)
{
}
