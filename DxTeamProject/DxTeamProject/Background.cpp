#include "stdafx.h"
#include "Background.h"

const float fTime = 1.5f;
const float fAddTime = 0.01f;

void CBackground::SetShader()
{
	D3DXMATRIXA16 matView, matProjection;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

	D3DXMATRIXA16 matWVP, matWorldInveseTranspose, matViewInverse;
	matWVP = m_matWorld * matView * matProjection;
	D3DXMatrixInverse(&matWorldInveseTranspose, NULL, &m_matWorld);
	D3DXMatrixTranspose(&matWorldInveseTranspose, &matWorldInveseTranspose);

	m_pShader->SetMatrix("WVPM", &matWVP);
	m_pShader->SetMatrix("WM", &m_matWorld);
	m_pShader->SetMatrix("WITM", &matWorldInveseTranspose);

	static DWORD dwOldTime = GetTickCount();
	DWORD dwCurrentTime = GetTickCount();
	DWORD dwElapsedTime = dwCurrentTime - dwOldTime;
	m_pShader->SetFloat("time", dwElapsedTime / 3000.0f);

	if (m_vecTextures[0] != 0)
		m_pShader->SetTexture("DiffuseTexture_Tex", m_vecTextures[0]);
	else if (m_pTexture != NULL)
		m_pShader->SetTexture("DiffuseTexture_Tex", m_pTexture);

	m_pShader->SetTexture("DiffuseTexture2_Tex", m_pShaderTxt);

	// float grayColor = 127 / 255;
	m_pShader->SetVector("gGrayColor", &D3DXVECTOR4(0.49f, 0.49f, 0.49f, 1.0f));

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
	//m_pShader->SetMatrix("gViewProjection", &matViewPro);
	//m_pShader->SetMatrix("gWorld", &m_matWorld);
	//m_pShader->SetMatrix("gInverseTranspose", &matInverseWorld);
	//
	////if (m_vecTextures[0] != 0)
	////	m_pShader->SetTexture("DiffuseSampler_Tex", m_vecTextures[0]);
	////else if (m_pTexture != NULL)
	////	m_pShader->SetTexture("DiffuseSampler_Tex", m_pTexture);
	//
	//if(m_vecColorTag[0] == "Black")			m_pShader->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "BlackTxt2.png"));
	//else if (m_vecColorTag[0] == "White")	m_pShader->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "WhiteTxt2.png"));
	//else if (m_vecColorTag[0] == "Yellow")	m_pShader->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "YellowTxt2.png"));
	//else if (m_vecColorTag[0] == "Green")	m_pShader->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "GreenTxt2.png"));
	//else if (m_vecColorTag[0] == "Red")		m_pShader->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "RedTxt2.png"));
	//else if (m_vecColorTag[0] == "Blue")	m_pShader->SetTexture("DiffuseSampler_Tex", g_pFileLoadManager->GetFileNameTexture("Resource/Texture", "BlueTxt2.png"));
	//
	//m_pShader->SetTexture("DiffuseSampler2_Tex", m_pShaderTxt);
	//
	//m_pShader->SetVector("gColor", &D3DXVECTOR4(1.0, 0.0, 0.0, 1.0));
	//
	//m_pShader->SetFloat("gTime", m_fShaderTime);
	//
	//m_fShaderTime += fAddTime;
	//m_pShader->SetFloat("a", 0.5f);
}

CBackground::CBackground() :
	m_pShader(NULL),
	m_pShaderTxt(NULL),
	m_fShaderTime(0.0f)
{
	m_strName = string("Background") + to_string(m_nRefCount);
}

CBackground::~CBackground()
{
}

//void CBackground::Update(CRay ray, D3DXCOLOR & playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
//{
//	// >> 터짐 방지
//	vecVPos.push_back(D3DXVECTOR3(0, 0, 0));
////	vecIsPick.push_back(m_isPicked);
//}

void CBackground::Setup(const ST_MapData & mapData)
{
	m_strObjName = mapData.strObjName;
	m_strFolder = mapData.strFolderPath;
	m_strXFile = mapData.strXFilePath;
	m_strTxtFile = mapData.strTxtPath;
	m_ObjectType = mapData.objType;

	m_vScale = mapData.vScale;
	m_vRotation = mapData.vRotate;
	m_vTranslation = mapData.vTranslate;
	
	m_vecColorTag = mapData.vecColorTag;

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

		m_pMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)m_adjBuffer->GetBufferPointer(),
			(DWORD*)m_adjBuffer->GetBufferPointer(),
			0, 0);
	}
	else
	{
		m_vTranslation.y = 0.5f;
		//vTranslate.y = 0.5f;
		D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMesh, NULL);

		m_stMtl.Ambient = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
		m_stMtl.Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
		m_stMtl.Specular = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);

		m_vecMtrls.push_back(m_stMtl);
	}
	g_pFileLoadManager->FileLoad_Texture("Resource/Texture", "shader.png", m_pShaderTxt);
	g_pFileLoadManager->FileLoad_Texture("Resource/Texture", "BasicGray_127.png", m_grayTxt);
	g_pFileLoadManager->FileLoad_Shader("Resource/Shader", "effect.fx", m_pShader);

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = matS * matR * matT;

	// OBB Test
	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);

	//D3DXVECTOR3 vScale, vRotate, vTranslate;
	//vScale = setData.vScale;
	//// JW ADD...
	//m_vScale = vScale;
	//vRotate = setData.vRotate;
	//vTranslate = setData.vTranslate;
	// ====================================================
	//D3DXMATRIXA16 matS, matR, matT;
	//D3DXMatrixScaling(&matS, vScale.x,vScale.y, vScale.z);
	//D3DXVECTOR3 v;
	//v.x = D3DXToRadian(vRotate.x);
	//v.y = D3DXToRadian(vRotate.y);
	//v.z = D3DXToRadian(vRotate.z);
	//D3DXMatrixRotationYawPitchRoll(&matR, v.x, v.y, v.z);
	//D3DXMatrixTranslation(&matT, vTranslate.x, vTranslate.y, vTranslate.z);
	//m_matWorld = matS * matR * matT;
}

void CBackground::Render()
{
	if (m_ObjectType == ObjectType::eInvisibleWall)
		return; // >> 투명벽 랜더하지 않음

	// if (m_ObjectType == ObjectType::eFlower) // || m_ObjectType == ObjectType::eInvisibleWall)
	// {
	// 	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	// 	// todo : setTexture
	// }
	// else
	// 	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	bool isUIMode = g_pGameManager->GetUImode();
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (m_pMesh == NULL)
		return;

	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		if (m_ObjectType != ObjectType::eFlower) // && m_ObjectType != ObjectType::eInvisibleWall)
		{
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

			if (!CheckIsGetColorOrb())
			{
				g_pD3DDevice->SetTexture(0, m_grayTxt);
				m_pMesh->DrawSubset(i);
			}
			else
			{
				if (m_fShaderTime < fTime && m_pShader != NULL && !isUIMode)
				{
					SetShader();
					UINT numPasses = 0;
					m_pShader->Begin(&numPasses, NULL);
					{
						for (UINT a = 0; a < numPasses; ++a)
						{
							m_pShader->BeginPass(a);
							m_pMesh->DrawSubset(a);
							m_pShader->EndPass();
						}
					}
					m_pShader->End();
				}
				else
				{
					if (m_vecTextures[i] != 0)
						g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
					else if (m_pTexture != NULL)
						g_pD3DDevice->SetTexture(0, m_pTexture);

					m_pMesh->DrawSubset(i);
				}
			}
		}
		else
		{
			// >> 투명벽, 꽃은 텍스쳐 없고 매터리얼 값으로만 이루어져 있음
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

			if (!CheckIsGetColorOrb())
				g_pD3DDevice->SetTexture(0, m_grayTxt);

			m_pMesh->DrawSubset(i);
		}
	}
	g_pD3DDevice->SetTexture(0, NULL);
}