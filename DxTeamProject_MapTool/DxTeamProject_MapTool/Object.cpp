#include "stdafx.h"
#include "Object.h"

CObject::CObject()
{
	m_vScale = D3DXVECTOR3(1, 1, 1);
	m_vRotate = D3DXVECTOR3(0, 0, 0);
	m_vTranslate = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	m_dxColor = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
}

CObject::~CObject()
{
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

void CObject::Render()
{
	IObject::Render_OBB_Box();

	m_pMtrl.Ambient = m_dxColor;
	m_pMtrl.Specular = m_dxColor;
	m_pMtrl.Diffuse = m_dxColor;

	g_pD3DDevice->SetMaterial(&m_pMtrl);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetmatWorld());

	if (m_pMesh == NULL)
		return;

	if (!m_isPick && !m_isClick || !m_pShader)
		m_pMesh->DrawSubset(0);
	else
	{
		SetShader(GetmatWorld());
		// m_pShader->SetVector("OutlineColor", &D3DXVECTOR4(m_dxColor));
		// m_pShader->SetVector("SurfaceColor", &D3DXVECTOR4(m_dxColor));
		IObject::Render();
	}
}
