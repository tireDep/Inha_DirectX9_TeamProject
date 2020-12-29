#include "stdafx.h"
#include "Tile.h"

void CTile::SetShader_Ocean()
{
	D3DXMATRIXA16 matView, matProj;
	D3DXMATRIXA16 matWorldViewProj, matWorldInverseTranspose, matViewInverse;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	matWorldViewProj = m_matWorld * matView * matProj;

	D3DXMatrixInverse(&matWorldInverseTranspose, NULL, &m_matWorld);
	D3DXMatrixTranspose(&matWorldInverseTranspose, &matWorldInverseTranspose);

	D3DXMatrixInverse(&matViewInverse, NULL, &matView);

	float center = 0.5f;
	float bump = 0.2f;

	m_pTexture = m_vecTextures[0];
	m_pShader_Ocean->SetTexture("distortion_Tex", m_pTexture);

	m_pShader_Ocean->SetMatrix("gWorldViewProjection", &matWorldViewProj);
	m_pShader_Ocean->SetMatrix("gWorldInverseTranspose", &matWorldInverseTranspose);
	m_pShader_Ocean->SetMatrix("gWorld", &m_matWorld);
	m_pShader_Ocean->SetMatrix("gViewInverse", &matViewInverse);

	m_pShader_Ocean->SetFloat("gTime", m_shaderTime);
	m_pShader_Ocean->SetFloat("gCenter", center);
	m_pShader_Ocean->SetFloat("gTimeAngle", m_shaderTimeAngle);
	m_pShader_Ocean->SetFloat("gBump", bump);

	// >> 속도 조정 해야함
	float flowSpeed = 0.1f;
	m_shaderTime += flowSpeed * g_pTimeManager->GetElapsedTime();
	m_shaderTimeAngle = 0;
	// >> 회전 제외
	// m_shaderTimeAngle += flowSpeed * g_pTimeManager->GetElapsedTime();
}

CTile::CTile() :
	m_pShader_Ocean(NULL),
	m_shaderTime(0.0f),
	m_shaderTimeAngle(0.0f)
{
	render = false;
	m_strName = string("Tile") + to_string(m_nRefCount);
}

CTile::~CTile()
{
}

void CTile::Setup(const ST_MapData & mapData)
{
	if (mapData.strObjName == "")
		return;

	m_strObjName = mapData.strObjName;
	m_strFolder = mapData.strFolderPath;
	m_strXFile = mapData.strXFilePath;
	m_strTxtFile = mapData.strTxtPath;
	m_ObjectType = mapData.objType;

	m_vScale = mapData.vScale;
	m_vRotation = mapData.vRotate;
	m_vTranslation = mapData.vTranslate;

	m_vecColorTag = mapData.vecColorTag;

	ST_XFile* xfile = new ST_XFile;

	if (m_strXFile != "")
	{
		g_pFileLoadManager->FileLoad_XFile(m_strFolder, m_strXFile, xfile);

		m_pMesh = xfile->pMesh;
		m_adjBuffer = xfile->adjBuffer;
		m_vecMtrls = xfile->vecMtrl;
		m_vecTextures = xfile->vecTextrure;
		m_numMtrls = xfile->nMtrlNum;

		delete xfile;

		if (m_strTxtFile != "")
			g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

		g_pFileLoadManager->FileLoad_Texture("Resource/Texture", "BasicGray_127.png", m_grayTxt);

		m_pMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)m_adjBuffer->GetBufferPointer(),
			(DWORD*)m_adjBuffer->GetBufferPointer(),
			0, 0);
	}

	if (m_ObjectType == ObjectType::eTile13)
	{
		// >> ocean
		g_pFileLoadManager->FileLoad_Shader("Resource/Shader", "flow.fx", m_pShader_Ocean);
	}

	// D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&m_matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	D3DXMatrixTranslation(&m_matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = m_matS * m_matR * m_matT;

	// OBB Test
	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	//m_strObjName = setData.strObjName;
	//m_strFolder = setData.strFolderPath;
	//m_strXFile = setData.strXFilePath;
	//m_strTxtFile = setData.strTxtPath;
	//m_ObjectType = setData.objType;
	//D3DXVECTOR3 vScale, vRotate, vTranslate;
	//vScale = setData.vScale; // 0.01, 0.03, 0.01, 0.01
	//// JW ADD...
	//m_vScale = vScale;
	//vRotate = setData.vRotate;
	//vTranslate = setData.vTranslate;
	//D3DXMATRIXA16 matS, matR, matT;
	//D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);
	//D3DXVECTOR3 v;
	//v.x = D3DXToRadian(vRotate.x);
	//v.y = D3DXToRadian(vRotate.y);
	//v.z = D3DXToRadian(vRotate.z);
	//D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);
	//D3DXMatrixTranslation(&matT, vTranslate.x, vTranslate.y, vTranslate.z);
	//m_matWorld = matS * matR * matT;
	//matWorld =  matT;
	//D3DXVECTOR3 *pVertices;
	//for (int i = 0; i < m_vecMtrls.size(); ++i)
	//{
	//	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	//	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(),
	//		m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	//	m_pMesh->UnlockVertexBuffer();
	//	
	//}
	//
	//for (int i = 0; i < m_vecMtrls.size(); ++i)
	//	m_pOBB.push_back(new COBB);
	//
	//for (int i = 0; i < m_pOBB.size(); ++i)
	//{
	//	m_pOBB[i]->SetupTile(m_vMin, m_vMax, m_vMax * m_vScale.y, m_vScale.x, m_vScale.z);
	//	g_pObjectManager->AddTileOBB(m_pOBB[i]);
	//	g_pObjectManager->SetScale(m_vMax.y);
	//}
}

void CTile::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (m_pMesh == NULL)
		return;

	bool isUIMode = g_pGameManager->GetUImode();
	if (m_ObjectType == ObjectType::eTile13 && m_pShader_Ocean != NULL && !isUIMode)
	{
		SetShader_Ocean();

		UINT numPasses = 0;
		m_pShader_Ocean->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				m_pShader_Ocean->BeginPass(i);
				m_pMesh->DrawSubset(i);
				m_pShader_Ocean->EndPass();
			}
		}
		m_pShader_Ocean->End();
	}

	else
	{
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
			// >> todo : 시연할 때 주석 풀기
			/* if (!CheckIsGetColorOrb())
			{
				g_pD3DDevice->SetTexture(0, m_grayTxt);
			}
			else */
			{
				if (m_vecTextures[i] != 0)
					g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
				else if (m_pTexture != NULL)
				{
					g_pD3DDevice->SetTexture(0, m_pTexture);
					// >> 텍스처 매치 안되있을 때
				}
			}
			m_pMesh->DrawSubset(i);
		}
		g_pD3DDevice->SetTexture(0, NULL);
	}
}

/// Delete Later...
//void CTile::Update(float duration)
//{
//	//for (int i = 0; i < m_pOBB.size(); ++i)
//	//if (m_pOBB[i])
//	//	m_pOBB[i]->Update(&m_matWorld);
//}
//	matWorld = matT;
//	D3DXVECTOR3 *pVertices;
//	
//	for (int i = 0; i < m_vecMtrls.size(); ++i)
//	{
//		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
//		D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(),
//			m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
//		m_pMesh->UnlockVertexBuffer();	
//	}
//	
//	for (int i = 0; i < m_vecMtrls.size(); ++i)
//		m_pOBB.push_back(new COBB);
//	
//	for (int i = 0; i < m_pOBB.size(); ++i)
//	{
//		m_pOBB[i]->SetupTile(m_vMin, m_vMax, m_vMax * m_vScale.y, m_vScale.x, m_vScale.z);
//		g_pObjectManager->AddTileOBB(m_pOBB[i]);
//		g_pObjectManager->SetScale(m_vMax.y);
//		
//	}
//}
//void CTile::Update(float duration)
//{
//
//	//for (int i = 0; i < m_pOBB.size(); ++i)
//	//if (m_pOBB[i])
//	//	m_pOBB[i]->Update(&m_matWorld);
//
//}