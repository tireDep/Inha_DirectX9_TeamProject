#include "stdafx.h"
#include "IObject.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Tile.h"
#include "Background.h"
#include "Gimmick.h"

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
	m_vTranslate(1.0f,0,1.0f),
	m_isClick(false),
	m_isPick(false),
	m_dxColor(0.5, 0.5, 0.5, 1),
	m_pOBB(NULL)
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
	if (m_pShader)
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

		D3DXMATRIXA16 temp;
		D3DXMatrixIdentity(&temp);
		m_pShader->SetMatrix("gWorldCameraPos", &temp);

		m_pShader->SetVector("gLightColor", &D3DXVECTOR4(D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1.0f));
		m_pShader->SetVector("gWorldLightPos", &D3DXVECTOR4(D3DXVECTOR3(0, 10.0f, 0), 1));
		// << : Light Shader

		m_pShader->SetVector("OutlineColor", &D3DXVECTOR4(0, 0, 0, 1));
		m_pShader->SetVector("SurfaceColor", &D3DXVECTOR4(1, 1, 1, 1));

	}
}

IObject::~IObject()
{
	SafeRelease(m_pMesh);
	SafeDelete(m_pOBB);
}

void IObject::Release()
{
	g_pObjectManager->RemoveObject(this);
	IObject::m_nRefCnt -= 1;
}

void IObject::Setup_OBB_Box()
{
	m_pOBB = new COBB;
	m_pOBB->Setup(this);
}

void IObject::Update(CRay * ray)
{
	// >> MOLLER-Trumbore 선 삼각 교차점 알고리즘

	const float EPSILON = 0.00000001f;

	D3DXMATRIXA16 matWorld = GetmatWorld();
	vector<D3DXVECTOR3> vecCheck = m_pOBB->GetOBBVertex();
	for (int i = 0; i<vecCheck.size(); i++)
		D3DXVec3TransformCoord(&vecCheck[i], &vecCheck[i], &matWorld);

	D3DXVECTOR3 rayOrigin = ray->GetOrigin();
	D3DXVECTOR3 rayDir = ray->GetDirection();
	for (int i = 0; i < vecCheck.size(); i += 3)
	{
		D3DXVECTOR3 vertex0 = vecCheck[i + 0];
		D3DXVECTOR3 vertex1 = vecCheck[i + 1];
		D3DXVECTOR3 vertex2 = vecCheck[i + 2];

		D3DXVECTOR3 edge1, edge2, h, s, q;
		float a, f, u, v;

		edge1 = vertex1 - vertex0;
		edge2 = vertex2 - vertex0;

		D3DXVec3Cross(&h, &rayDir, &edge2);
		a = D3DXVec3Dot(&edge1, &h);
		if (a > -EPSILON && a < EPSILON)
		{
			// 광선이 삼각형과 평행
			m_isPick = false;
			continue;
		}

		f = 1.0 / a;
		s = rayOrigin - vertex0;
		u = f * D3DXVec3Dot(&s, &h);
		if (u<0.0 || u>1.0)
		{
			m_isPick = false;
			continue;
		}

		D3DXVec3Cross(&q, &s, &edge1);
		v = f * D3DXVec3Dot(&rayDir, &q);
		if (v<0.0 || u + v>1.0)
		{
			m_isPick = false;
			continue;
		}

		float t = f * D3DXVec3Dot(&edge2, &q);
		if (t > EPSILON)
		{
			// 광선 교차
			// t를 계산하여 선에서 교차점이 어디있는지 알아낼 수 있음
			// D3DXVECTOR3 result = ray->GetOrigin() + ray->GetDirection() * t;

			m_isPick = true;
			return;
		}
		else
		{
			// 선교차 존재, 광선교차는 아님
			m_isPick = false;
			continue;
		}
	}
}

void IObject::Render()
{
	if (m_pShader)
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
}

void IObject::Render_OBB_Box()
{
#ifdef _DEBUG
	if (m_pOBB)
	{
		m_pOBB->Update(&GetmatWorld());
		m_pOBB->Render();
	}
#endif // _DEBUG
}

D3DXMATRIXA16 IObject::GetmatWorld()
{
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(m_vRotate.x);
	v.y = D3DXToRadian(m_vRotate.y);
	v.z = D3DXToRadian(m_vRotate.z);

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

	return matWorld;
}

void IObject::SetRefCnt(int set)
{
	IObject::m_nRefCnt = set;
}

void IObject::CreateObject(const ObjectType& objType, int index)
{
	// >> FileLoader 생성
	
	ST_MapData mapData;
	mapData.vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mapData.vTranslate = D3DXVECTOR3(0.5f, 0.0f, 0.5f);
	// >> todo : translate 현 위치 중앙으로 받아오기

	mapData.objType = objType;

	switch (objType)
	{
	case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
	case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
	{
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
		mapData.strObjName = string("AutumnTree") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/SeasonTree";
		mapData.strTxtPath = "autumn_texture.png";

		mapData.strXFilePath = string("AutumnTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eSTree:
	{
		mapData.strObjName = string("SummerTree") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/SeasonTree";
		mapData.strTxtPath = "summer_texture.png";

		mapData.strXFilePath = string("SummerTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eWTree:
	{
		mapData.strObjName = string("WinterTree") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/SeasonTree";
		mapData.strTxtPath = "winter_texture.png";

		mapData.strXFilePath = string("WinterTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eCTree:
	{
		mapData.strObjName = string("ColorTree") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/ColorTree";
		mapData.strTxtPath = "TreesBlue.png";

		mapData.strXFilePath = string("Tree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

#ifdef _DEBUG
	case eBall:
	{
		mapData.strObjName = string("BeachBall") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/Else";
		mapData.strTxtPath = "BeachBall_Base_Color.png";
		mapData.strXFilePath = "ball.X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eChair:
	{
		mapData.strObjName = string("Chair") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/Else";
		mapData.strTxtPath = "";
		mapData.strXFilePath = "blue_chair.X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eUmbrella:
	{
		mapData.strObjName = string("Umbrella") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/Else";
		mapData.strTxtPath = "Umbrella_Blue.png";
		mapData.strXFilePath = "Umbrella.X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eSnowman:
	{
		mapData.strObjName = string("Snowman") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/Else";
		mapData.strTxtPath = "Snowman.png";
		mapData.strXFilePath = "Snowman.X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eInvisibleWall:
	{
		mapData.strObjName = string("InvisibleWall") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "";
		mapData.strTxtPath = "";
		mapData.strXFilePath = "";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

#endif // _DEBUG

	case eG_RotationBoard:
	case eG_BreakWall:
	case eG_Door:
	case eG_ColorChanger:
	case eG_Switch:
	{
		CGimmick::CreateGimmick(objType);
	}
		break;

	} // << : switch
}

void IObject::CreateObject(ST_MapData& mapData)
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
	case eCTree:
#ifdef _DEBUG
	case eBall:
	case eChair:
	case eUmbrella:
	case eSnowman:
	case eInvisibleWall:
#endif // _DEBUG
	{
		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eG_RotationBoard:
	case eG_BreakWall:
	case eG_Door:
	case eG_ColorChanger:
	case eG_Switch:
	{
		CGimmick::CreateGimmick_SaveData(mapData);
	}
	break;

	} // << : switch
}
