#include "stdafx.h"
#include "Tile.h"

const float fTime = 10.5f;
const float fAddTime = 0.01f;

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

	// m_pTexture = m_vecTextures[0];
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

void CTile::SetShader_Tile()
{
	D3DXMATRIXA16 matView, matProjection;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

	D3DXMATRIXA16 matWVP, matWorldInveseTranspose, matViewInverse;
	matWVP = m_matWorld * matView * matProjection;
	D3DXMatrixInverse(&matWorldInveseTranspose, NULL, &m_matWorld);
	D3DXMatrixTranspose(&matWorldInveseTranspose, &matWorldInveseTranspose);

	m_pShader_Tile->SetMatrix("WVPM", &matWVP);
	m_pShader_Tile->SetMatrix("WM", &m_matWorld);
	m_pShader_Tile->SetMatrix("WITM", &matWorldInveseTranspose);

	if (m_dwOldTime == -1)
		m_dwOldTime = GetTickCount();

	DWORD dwCurrentTime = GetTickCount();
	DWORD dwElapsedTime = dwCurrentTime - m_dwOldTime;
	m_pShader_Tile->SetFloat("time", dwElapsedTime / 3000.0f);

	if (m_vecTextures[0] != 0)
		m_pShader_Tile->SetTexture("DiffuseTexture_Tex", m_vecTextures[0]);
	else if (m_pTexture != NULL)
		m_pShader_Tile->SetTexture("DiffuseTexture_Tex", m_pTexture);

	m_pShader_Tile->SetTexture("DiffuseTexture2_Tex", m_pShaderTxt);

	// float grayColor = 45 / 255;
	m_pShader_Tile->SetVector("gGrayColor", &D3DXVECTOR4(0.17f, 0.17f, 0.17f, 1.0f));

	m_fShaderTime += fAddTime;

	/// >> 기존 코드
	//D3DXMATRIXA16 matView, matProj, matViewPro, matInverseWorld;
	//g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	//g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	//matViewPro = m_matWorld * matView * matProj;
	//
	//D3DXMATRIXA16 a, b;
	//D3DXMatrixIdentity(&a);
	//D3DXMatrixIdentity(&b);
	//
	//D3DXMatrixInverse(&a, NULL, &m_matWorld);
	//D3DXMatrixTranspose(&b, &a);
	//
	//matInverseWorld = m_matWorld * a;
	//D3DXMatrixTranspose(&matInverseWorld, &matInverseWorld);
	//
	//// >> : Light Shader
	//m_pShader_Tile->SetMatrix("gViewProjection", &matViewPro);
	//m_pShader_Tile->SetMatrix("gWorld", &m_matWorld);
	//m_pShader_Tile->SetMatrix("gInverseTranspose", &matInverseWorld);
	//
	////if (m_vecTextures[0] != 0)
	////	m_pShader->SetTexture("DiffuseSampler_Tex", m_vecTextures[0]);
	////else if (m_pTexture != NULL)
	////	m_pShader->SetTexture("DiffuseSampler_Tex", m_pTexture);
	//
	//if (m_vecColorTag[0] == "Black")		m_pShader_Tile->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "BlackTxt2.png"));
	//else if (m_vecColorTag[0] == "White")	m_pShader_Tile->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "WhiteTxt2.png"));
	//else if (m_vecColorTag[0] == "Yellow")	m_pShader_Tile->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "YellowTxt2.png"));
	//else if (m_vecColorTag[0] == "Green")	m_pShader_Tile->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "GreenTxt2.png"));
	//else if (m_vecColorTag[0] == "Red")		m_pShader_Tile->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "RedTxt2.png"));
	//else if (m_vecColorTag[0] == "Blue")	m_pShader_Tile->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "BlueTxt2.png"));
	//
	//m_pShader_Tile->SetTexture("DiffuseSampler2_Tex", m_pShaderTxt);
	//
	//m_pShader_Tile->SetVector("gColor", &D3DXVECTOR4(1.0, 0.0, 0.0, 1.0));
	//
	//m_pShader_Tile->SetFloat("gTime", m_fShaderTime);
	//
	//m_fShaderTime += fAddTime;
	//m_pShader_Tile->SetFloat("a", 0.9f);
}

CTile::CTile() :
	m_pShader_Ocean(NULL),
	m_shaderTime(0.0f),
	m_shaderTimeAngle(0.0f),
	m_pShader_Tile(NULL),
	m_pShaderTxt(NULL),
	m_fShaderTime(0.0f),
	m_dwOldTime(-1)
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

	if (m_ObjectType == ObjectType::eTile13)
	{
		m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_stMtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (m_strTxtFile != "")
			g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

		ST_PNT_VERTEX v;
		float f = 1.0f;
		v.p = D3DXVECTOR3(-f, 0, -f);	v.t = D3DXVECTOR2(1, 0); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-f, 0, f);	v.t = D3DXVECTOR2(0, 0); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(f, 0, f);		v.t = D3DXVECTOR2(0, 1); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-f, 0, -f);	v.t = D3DXVECTOR2(1, 0); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(f, 0, f);		v.t = D3DXVECTOR2(0, 1); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(f, 0, -f);	v.t = D3DXVECTOR2(1, 1); m_vecVertex.push_back(v);

		D3DXVECTOR3 n1, n2, normal;
		for (int i = 0; i < m_vecVertex.size(); i+=3)
		{
			n1 = m_vecVertex[i].p - m_vecVertex[i + 1].p;
			n2 = m_vecVertex[i].p - m_vecVertex[i + 2].p;
			D3DXVec3Cross(&normal, &n1, &n2);

			m_vecVertex[i + 0].n = normal;
			m_vecVertex[i + 1].n = normal;
			m_vecVertex[i + 2].n = normal;
		}

		// >> createMesh
		vector<DWORD> vecAttrBuf;
		for (int i = 0; i < m_vecVertex.size(); i++)
			vecAttrBuf.push_back(0);

		D3DXCreateMeshFVF(vecAttrBuf.size(), m_vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_pMesh);

		ST_PNT_VERTEX* pV = NULL;
		m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
		memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEX));
		m_pMesh->UnlockVertexBuffer();

		WORD* pI = NULL;
		m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
		for (int i = 0; i < m_vecVertex.size(); i++)
			pI[i] = i;
		m_pMesh->UnlockIndexBuffer();

		DWORD* pA = NULL;
		m_pMesh->LockAttributeBuffer(0, &pA);
		memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
		m_pMesh->UnlockAttributeBuffer();
		// << createMesh

		// >> ocean
		g_pFileLoadManager->FileLoad_Shader("Resource/Shader", "flow.fx", m_pShader_Ocean);

		m_vecMtrls.clear();
		m_vecMtrls.push_back(m_stMtl);
		m_vecTextures.clear();
		m_vecTextures.push_back(m_pTexture);
	}
	else if (m_strXFile != "")
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

		g_pFileLoadManager->FileLoad_Texture("Resource/Texture", "shader.png", m_pShaderTxt);
		g_pFileLoadManager->FileLoad_Shader("Resource/Shader", "effect.fx", m_pShader_Tile);

		m_pMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)m_adjBuffer->GetBufferPointer(),
			(DWORD*)m_adjBuffer->GetBufferPointer(),
			0, 0);
	}

	g_pFileLoadManager->FileLoad_Texture("Resource/Texture", "BasicGray_45.png", m_grayTxt);

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
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (m_pMesh == NULL)
		return;

	bool isUIMode = g_pGameManager->GetUImode();
	if (m_ObjectType == ObjectType::eTile13 && m_pShader_Ocean != NULL && !isUIMode)
	{
		// >> Ocean
		g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, false);
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
		// >> Tile
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
			
			if (!CheckIsGetColorOrb())
			{
				// >> 회색 텍스쳐
				g_pD3DDevice->SetTexture(0, m_grayTxt);
				// >> 불투명벽
				if (!m_isCameraRender)
				{
					g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
					g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
					m_isCameraRender = true;

					m_pMesh->DrawSubset(i);
				}
				else
					m_pMesh->DrawSubset(i);
			}
			else
			{
				// >> 오브 획득, 셰이더 적용
				if (m_fShaderTime < fTime && m_pShader_Tile != NULL && !isUIMode)
				{
					SetShader_Tile();
					UINT numPasses = 0;
					m_pShader_Tile->Begin(&numPasses, NULL);
					{
						for (UINT a = 0; a < numPasses; ++a)
						{
							m_pShader_Tile->BeginPass(a);
							m_pMesh->DrawSubset(a);
							m_pShader_Tile->EndPass();
						}
					}
					m_pShader_Tile->End();
				}
				else
				{
					// >> 오브 획득, 셰이더 적용 x, 불투명 벽
					if (!m_isCameraRender)
					{
						g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
						g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
						g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
						m_isCameraRender = true;
					}
					if (m_vecTextures[i] != 0)
						g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
					else if (m_pTexture != NULL)
					{
						g_pD3DDevice->SetTexture(0, m_pTexture);
						// >> 텍스처 매치 안되있을 때
					}
					m_pMesh->DrawSubset(i);
				}
			}
		}
		g_pD3DDevice->SetTexture(0, NULL);
	}

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
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