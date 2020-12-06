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

	if (m_strXFile != "")
	{
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
	else
	{
		D3DXCreateBox(g_pD3DDevice, m_vScale.x, m_vScale.y, m_vScale.z, &m_pMesh, NULL);
		
		D3DMATERIAL9 mtrl;
		m_vecMtrls.push_back(mtrl);

		m_pMtrl.Ambient = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
		m_pMtrl.Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
		m_pMtrl.Specular = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
	}

	IObject::Setup_OBB_Box();
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
	IObject::Render_OBB_Box();

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetmatWorld());

	if (m_pMesh == NULL)
		return;

	if (m_ObjectType == ObjectType::eInvisibleWall)
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	else
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	if(m_pTexture)
		g_pD3DDevice->SetTexture(0, m_pTexture);

	if (!m_isPick && !m_isClick || !m_pShader)
	{
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_ObjectType == ObjectType::eInvisibleWall)
				g_pD3DDevice->SetMaterial(&m_pMtrl);
			else
				g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

			m_pMesh->DrawSubset(i);
		}
	}
	else
	{
		SetShader(GetmatWorld());
		IObject::Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
}

void CBackground::SetDiffScale(D3DXVECTOR3 set)
{
}
