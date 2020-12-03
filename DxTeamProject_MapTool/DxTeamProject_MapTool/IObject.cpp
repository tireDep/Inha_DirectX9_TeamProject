#include "stdafx.h"
#include "IObject.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Tile.h"
#include "Background.h"

int IObject::m_nRefCnt = 0;

IObject::IObject() : 
	m_pTexture(NULL),
	m_pMesh(NULL),
	m_adjBuffer(NULL),
	m_numMtrls(0),
	m_strObjName(""),
	m_strFolder(""),
	m_strXFile(""),
	m_strTxtFile(""),
	m_ObjectType(ObjectType::eNull),
	m_vScale(0,0,0),
	m_vRotate(0,0,0),
	m_vTranslate(0,0,0),
	m_isClick(false),
	m_isPick(false),
	m_dxColor(0.5, 0.5, 0.5, 1),
	m_pShader(NULL)
{
	ZeroMemory(&m_pMtrl, sizeof(D3DMATERIAL9));
	m_pMtrl.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_pMtrl.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_pMtrl.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	g_pObjectManager->AddObject(this);
	IObject::m_nRefCnt += 1;

	g_pFileLoadManager->FileLoad_Shader("Resource/Shader", "outLine.fx", m_pShader);
}

void IObject::SetShader(const D3DXMATRIXA16 & setMatWorld)
{
	// >> : OutLine
	D3DXMATRIXA16 matView, matProj, matViewPro, matViewInvTrans;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	matViewPro = setMatWorld * matView * matProj;
	m_pShader->SetMatrix("matViewProjection", &matViewPro);
	m_pShader->SetFloat("OutlineWidth", 0.05f);
	// << : OutLine

	// >> : Light Shader
	m_pShader->SetMatrix("gWorldMatrix", &setMatWorld);
	m_pShader->SetMatrix("gViewMatrix", &matView);
	m_pShader->SetMatrix("gProjectionMatrix", &matProj);

	// ===== 외부변수 받아오기?
	D3DXMATRIXA16 temp;
	D3DXMatrixIdentity(&temp);
	m_pShader->SetMatrix("gWorldCameraPos", &temp);

	m_pShader->SetVector("gLightColor", &D3DXVECTOR4(D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1.0f));
	m_pShader->SetVector("gWorldLightPos", &D3DXVECTOR4(D3DXVECTOR3(0, 10.0f, 0), 1));
	// ===== 외부변수 받아오기?
	// << : Light Shader

	m_pShader->SetVector("OutlineColor", &D3DXVECTOR4(0, 0, 0, 1));
	m_pShader->SetVector("SurfaceColor", &D3DXVECTOR4(m_dxColor));
}

IObject::~IObject()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_pTexture);
	SafeRelease(m_pShader);
}

void IObject::Release()
{
	g_pObjectManager->RemoveObject(this);
	IObject::m_nRefCnt -= 1;
}

void IObject::Update(CRay * ray)
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

	D3DXVECTOR3* pVertices;
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	D3DXVECTOR3 m_vMin, m_vMax;
	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	// later.. rotation add
	// m_vMin += m_vTranslate;				m_vMax += m_vTranslate;
	D3DXVec3TransformCoord(&m_vMin, &m_vMin, &matWorld);
	D3DXVec3TransformCoord(&m_vMax, &m_vMax, &matWorld);
	// >> 월드 좌표계로 돌림

	if (D3DXBoxBoundProbe(&m_vMin, &m_vMax, &ray->GetOrigin(), &ray->GetDirection()) == true)
		m_isPick = true;
	else
		m_isPick = false;

	m_pMesh->UnlockVertexBuffer();
}

void IObject::Render()
{
	UINT numPasses = 0;
	m_pShader->Begin(&numPasses, NULL);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			m_pShader->BeginPass(i);
			if (i == 0)
				g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW); // 외곽선
			else
				g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// 내부
			m_pMesh->DrawSubset(0);
			m_pShader->EndPass();
		}
	}
	m_pShader->End();
}

void IObject::SetRefCnt(int set)
{
	IObject::m_nRefCnt = set;
}

void IObject::CreateObject(const ObjectType objType, int index)
{
	// >> FileLoader 생성
	switch (objType)
	{
	case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
	case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
	{
		ST_MapData mapData;
		mapData.vScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
		mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mapData.vTranslate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// >> todo : translate 현 위치 중앙으로 받아오기

		mapData.objType = objType;

		mapData.strObjName = string("Tile") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Tile";
		mapData.strTxtPath = "Texture_01.png";

		if(objType == eTile10 || objType == eTile11 || objType == eTile12 || objType == eTile13)
			mapData.strXFilePath = string("Tile_") + to_string(objType + 1) + ".X";
		else
			mapData.strXFilePath = string("Tile_0") + to_string(objType + 1) + ".X";

		CTile* tile = new CTile;
		tile->Setup(mapData);
	}
		break;

	// todo : setup에서 화면 중앙 위치로 이동
	case eBox:
	{
		CBox* box = new CBox;
		box->Setup();
	}
		break;

	case eSphere:
	{
		CSphere* sphere = new CSphere;
		sphere->Setup();
	}
		break;

	case eCylinder:
	{
		CCylinder* cylinder = new CCylinder;
		cylinder->Setup();
	}
		break;

	case eATree:
	{
		ST_MapData mapData;
		mapData.vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
		mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mapData.vTranslate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// >> todo : translate 현 위치 중앙으로 받아오기

		mapData.objType = objType;

		mapData.strObjName = string("AutumnTree") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background";
		mapData.strTxtPath = "autumn_texture.png";

		mapData.strXFilePath = string("AutumnTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eSTree:
	{
		ST_MapData mapData;
		mapData.vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
		mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mapData.vTranslate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// >> todo : translate 현 위치 중앙으로 받아오기

		mapData.objType = objType;

		mapData.strObjName = string("SummerTree") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background";
		mapData.strTxtPath = "summer_texture.png";

		mapData.strXFilePath = string("SummerTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eWTree:
	{
		ST_MapData mapData;
		mapData.vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
		mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mapData.vTranslate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// >> todo : translate 현 위치 중앙으로 받아오기

		mapData.objType = objType;

		mapData.strObjName = string("WinterTree") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background";
		mapData.strTxtPath = "winter_texture.png";

		mapData.strXFilePath = string("WinterTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	}
}

void IObject::CreateObject(const ST_MapData& mapData)
{
	// >> SaveLoad 파일 생성
	switch (mapData.objType)
	{
	case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
	case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
	{
		CTile* tile = new CTile;
		tile->Setup(mapData);
	}
	break;

	case eBox:
	{
		CBox* box = new CBox;
		box->Setup(mapData);
	}
	break;

	case eSphere:
	{
		CSphere* sphere = new CSphere;
		sphere->Setup(mapData);
	}
	break;

	case eCylinder:
	{
		CCylinder* cylinder = new CCylinder;
		cylinder->Setup(mapData);
	}
	break;

	case eATree:
	case eSTree:
	case eWTree:
		CBackground* background = new CBackground;
		background->Setup(mapData);
		break;
	}
}
