#include "stdafx.h"
#include "Tile.h"
#include "OBB.h"
CTile::CTile()
{
	m_pMesh = NULL;
	m_pTexture = NULL;
	
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&matWorld);
}

CTile::~CTile()
{
}

void CTile::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;
	m_vScale = setData.vScale; // 0.01, 0.03, 0.01, 0.01
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

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(m_vRotate.x);
	v.y = D3DXToRadian(m_vRotate.y);
	v.z = D3DXToRadian(m_vRotate.z);

	D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);

	D3DXMatrixTranslation(&matT, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);
	m_matWorld = matS * matR * matT;
	matWorld =  matT;
	D3DXVECTOR3 *pVertices;
	

	

	for (int i = 0; i < m_vecMtrls.size(); ++i)
	{
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
		D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(),
			m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
		m_pMesh->UnlockVertexBuffer();
		
	}
	
	for (int i = 0; i < m_vecMtrls.size(); ++i)
		m_pOBB.push_back(new COBB);
	
	for (int i = 0; i < m_pOBB.size(); ++i)
	{
		m_pOBB[i]->SetupTile(m_vMin, m_vMax, m_vMax * m_vScale.y, m_vScale.x, m_vScale.z);
		g_pObjectManager->AddTileOBB(m_pOBB[i]);
		g_pObjectManager->SetScale(m_vMax.y);
		
	}
}

void CTile::Update()
{

	

	for (int i = 0; i < m_pOBB.size(); ++i)
	if (m_pOBB[i])
		m_pOBB[i]->Update(&m_matWorld);

}

void CTile::Render()
{
	//if (m_pOBB)
	//	m_pOBB->OBBBOX_RENDER(D3DCOLOR_XRGB(255, 0, 0));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (m_pMesh == NULL)
		return;

	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		//g_pD3DDevice->SetMaterial(m_vecMtrls[i]);

		if (m_vecTextures[i] != 0)
			g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
		else if (m_pTexture != NULL)
		{
			g_pD3DDevice->SetTexture(0, m_pTexture); 
			// >> 텍스처 매치 안되있을 때
		}

		m_pMesh->DrawSubset(i);
	}

	g_pD3DDevice->SetTexture(0, NULL);
}
