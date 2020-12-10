#include "stdafx.h"
#include "Colorchanger.h"
#include "MeshTile.h"
#include "OBB.h"
Color_changer::Color_changer()
	:m_position(0, 0, 0)
	, m_pMeshBeam(NULL)
	, length(0)
	, m_fHitLength(50)
	, angle(0)
	, m_scale(0.5, 0.5, 1)
	, m_BeamOBB(NULL)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	
	m_stMtl.Ambient = RED;
	m_stMtl.Diffuse = RED;
	m_stMtl.Specular = RED;
}

Color_changer::~Color_changer()
{
	

}

void Color_changer::Setup()
{
	//BEAM
	{ 
		length = 50;
		D3DXCreateCylinder(g_pD3DDevice, 0.5f, 0.5f, length, 20, 20, &m_pMeshBeam, NULL);

		D3DXVECTOR3* pVertices;
		

		m_pMeshBeam->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
		D3DXComputeBoundingBox(pVertices, m_pMeshBeam->GetNumVertices(), m_pMeshBeam->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
		m_pMeshBeam->UnlockVertexBuffer();

		m_BeamOBB = new COBB;
		m_BeamOBB->SetupMesh(m_vMin,m_vMax, 0.5f);

	
	}

	// COLORCHANGER
	ST_XFile* xfile = new ST_XFile;

	if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Gimmick/ColorChanger", "Color_changer.X", xfile)) //"Resource/XFile/Gimmick/ColorChanger", "Color_changer.X"
	{
		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
		return;
	}

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	/*if (m_vecTextures.size() > 1)
	{
		for (int i = 0; i < m_vecTextures.size(); i++)
		{
			string filePath;
			filePath = string(folder) + "/tower_defense_texture.tga";
			if (m_vecTextures[i] == NULL)
				D3DXCreateTextureFromFileA(g_pD3DDevice, filePath.c_str(), &m_vecTextures[i]);
		}
	}*/
	delete xfile;


	
	
}

void Color_changer::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;
	
	D3DXVECTOR3 vScale, vRotate, vTranslate;

	vScale = setData.vScale; 
							 
	m_vScale = vScale;
	vRotate = setData.vRotate;
	vTranslate = setData.vTranslate;

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

	D3DXMatrixScaling(&m_matS, vScale.x, vScale.y, vScale.z); // ¸ãµ¥ÀÌÅÍ Å©±â

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(vRotate.x);
	v.y = D3DXToRadian(vRotate.y);
	v.z = D3DXToRadian(vRotate.z);

	D3DXMatrixRotationYawPitchRoll(&m_matR, v.x, v.y, v.z); //¸ãµ¥ÀÌÅÍ

	D3DXMatrixTranslation(&m_matT, vTranslate.x, vTranslate.y, vTranslate.z); //¸ãµ¥ÀÌÅÍ

	//m_matWorld = m_matS * m_matR * m_matT

	//---------------------------------------------------------------------

	D3DXMatrixRotationY(&matR, D3DXToRadian(angle));
	D3DXMatrixScaling(&matS, 0.3f, 0.3f, 0.3f);
	D3DXMatrixTranslation(&matT, m_position.x, m_position.y, m_position.z);
	
	m_matWorld = matS * matR * matT;
	

	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	g_pObjectManager->AddGimmick(this);

}

void Color_changer::Update()
{
	/*if (istrue == false)
	{
		m_position.y += 0.001f;
		if (m_position.y > 5)
			istrue = true;

	}
	else if (istrue == true)
	{
		m_position.y -= 0.001f;
		if (m_position.y < -5)
			istrue = false;
	}*/

	angle += 0.01;
	D3DXMatrixRotationY(&matR, D3DXToRadian(angle));// D3DXToRadian(angle)

	D3DXMatrixTranslation(&matT, m_position.x, m_position.y + 1.5f, m_position.z - m_fHitLength / 2.0);
	D3DXMatrixScaling(&matS, m_scale.x, m_scale.y, m_fHitLength / length);
	BeamWorld = matS * matT * matR;
	
	m_BeamOBB->Update(&BeamWorld);
	
}

void Color_changer::Render()
{

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);	
	//Beam
	{
		
		
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &BeamWorld);
		g_pD3DDevice->SetMaterial(&m_stMtl);
		m_BeamOBB->Render();
		m_pMeshBeam->DrawSubset(0);
	}
	// ÄÃ·¯Ã¼ÀÎÀú
	{
		D3DXMatrixRotationY(&matR, D3DXToRadian(angle));
		D3DXMatrixScaling(&matS, 0.3f, 0.3f, 0.3f);
		D3DXMatrixTranslation(&matT, m_position.x, m_position.y, m_position.z);
		m_matWorld = matS * matR * matT;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

		if (m_pMesh == NULL)
			return;
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
		}

		m_pMesh->DrawSubset(0);
		g_pD3DDevice->SetTexture(0, NULL);
	}
}


//
//bool Color_changer::RayCheck(MeshTile& meshtile)
//{
//	BOOL Hit = false;
//	DWORD FaceIndex;
//	float U, V;
//	float Dist;
//	D3DXVECTOR3 rayOrigin = m_position;
//	rayOrigin.x -= meshtile.GetMatWorld()._41;
//	rayOrigin.y -= meshtile.GetMatWorld()._42;
//	rayOrigin.z -= meshtile.GetMatWorld()._43;
//	D3DXVECTOR3 m_direction = D3DXVECTOR3(1, 0, 0);
//	D3DXIntersect(meshtile.GetMesh(), &rayOrigin, &m_direction,
//		&Hit, &FaceIndex, &U, &V, &Dist, NULL, NULL);
//	if (Hit)
//	{
//		/*m_stMtlSphere2.Ambient = YELLOW;
//		m_stMtlSphere2.Diffuse = YELLOW;
//		m_stMtlSphere2.Specular = YELLOW;*/
//		
//		return true;
//	}
//	else
//	{
//		/*m_stMtlSphere2.Ambient = RED;
//		m_stMtlSphere2.Diffuse = RED;
//		m_stMtlSphere2.Specular = RED;*/
//		return false;
//
//	}
//
//}

void Color_changer::SetColor(D3DXCOLOR color)
{
	c = color;
}

void Color_changer::SetHitLength(float HitLength)
{
	m_fHitLength = HitLength;
}
