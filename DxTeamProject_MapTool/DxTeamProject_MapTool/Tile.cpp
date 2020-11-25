#include "stdafx.h"
#include "Tile.h"

CTile::CTile()
{
	m_pMesh = NULL;
	m_pTexture = NULL;

	m_strObjName = string("Tile") + to_string(m_nRefCnt);	

	m_ObjectType = ObjectType::eTile;

	m_vScale = D3DXVECTOR3(1, 1, 1);
	m_vRotate = D3DXVECTOR3(0, 0, 0);
	m_vTranslate = D3DXVECTOR3(0, 0.5f, 0);
}

CTile::~CTile()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_pTexture);
}

void CTile::Setup()
{
	D3DXCreateBox(g_pD3DDevice, m_vScale.x, m_vScale.y, m_vScale.z, &m_pMesh, NULL);
	// todo : 파일 로드
	
	ZeroMemory(&m_pMtrl, sizeof(D3DMATERIAL9));
	m_pMtrl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMtrl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMtrl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// todo : 임시 매터리얼 설정 -> 변경

	ST_XFile* xfile = new ST_XFile;

	g_pFileLoadManager->FileLoad_XFile("Resource/Tile", "Cube_01.X", xfile);

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	delete xfile;
}

void CTile::Setup(ST_MapData setData)
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
	
	g_pFileLoadManager->FileLoad_XFile("Resource/Tile", "Cube_01.X", xfile);
	
	// g_pFileLoadManager->FileLoad_XFile(m_strFolder, m_strXFile, xfile);
	// 
	// if (m_strTxtFile != "")
	// 	g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	delete xfile;


	// Setup();
}

void CTile::Update()
{
}

void CTile::Update(CRay * ray)
{
}

void CTile::Render()
{
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
	
	// if(m_pMtrl!=NULL)
	// 	g_pD3DDevice->SetMaterial(&m_pMtrl);
	
	if (m_pMesh == NULL)
		return;

	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		g_pD3DDevice->SetMaterial(m_vecMtrls[i]);

		if (m_vecTextures[i] != 0)
			g_pD3DDevice->SetTexture(0, m_vecTextures[i]);

		else if (m_pTexture != NULL)
		{
			g_pD3DDevice->SetTexture(0, m_pTexture);
			cout << "temp";
		}
		// >> 텍스처 매치 안되있을 때

		m_pMesh->DrawSubset(i);
	}
}
