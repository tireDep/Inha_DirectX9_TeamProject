#include "stdafx.h"
#include "IObject.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Tile.h"
#include "Background.h"
#include "Book.h"
#include "Gimmick.h"
#include "Orb.h"
#include "Trace.h"
#include "EventTrigger.h"

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
	m_isClick(true),
	m_isPick(true),
	m_dxColor(0.5, 0.5, 0.5, 1),
	m_pOBB(NULL),
	m_strConditionName(""),
	m_conditionOrbindex(0)
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

void IObject::SetShaderColor(const D3DXVECTOR4 & outLine, const D3DXVECTOR4 & inner)
{
	m_pShader->SetVector("OutlineColor", &outLine);
	m_pShader->SetVector("SurfaceColor", &inner);
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

bool IObject::Update(CRay * ray)
{
	// >> MOLLER-Trumbore �� �ﰢ ������ �˰���

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
			// ������ �ﰢ���� ����
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
			// ���� ����
			// t�� ����Ͽ� ������ �������� ����ִ��� �˾Ƴ� �� ����
			D3DXVECTOR3 result = ray->GetOrigin() + ray->GetDirection() * t;

			m_isPick = true;
			m_isClick = true;
			return true;
		}
		else
		{
			// ������ ����, ���������� �ƴ�
			m_isPick = false;
			continue;
		}
	}

	return false;
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
					g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW); // �ܰ���
				else
					g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// ����
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

void IObject::SetDiffScale(D3DXVECTOR3 set)
{
	if (set.x != m_vScale.x)
		m_vScale = D3DXVECTOR3(set.x, set.x, set.x);
	else if (set.y != m_vScale.y)
		m_vScale = D3DXVECTOR3(set.y, set.y, set.y);
	else if (set.z != m_vScale.z)
		m_vScale = D3DXVECTOR3(set.z, set.z, set.z);
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

int IObject::GetRefCnt()
{
	return m_nRefCnt;
}

void IObject::CreateObject(const ObjectType& objType, int index)
{
	// >> FileLoader ����
	
	ST_MapData mapData;
	mapData.vScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mapData.vTranslate = D3DXVECTOR3(0.5f, 0.0f, 0.5f);
	// >> todo : translate �� ��ġ �߾����� �޾ƿ���

	mapData.objType = objType;

	switch (objType)
	{
	case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
	case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
	{
		// todo : tagging
		if (objType == eTile01)
		{
			mapData.strObjName = string("Tile_01_Grass") + to_string(m_nRefCnt + 1);
			// >> tagging
			mapData.vecColorTag.push_back("Green");
			mapData.vecColorTag.push_back("Red");
			mapData.vecColorTag.push_back("Yellow");
		}
		else if (objType == eTile02)
		{
			mapData.strObjName = string("Tile_02_Ground") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("Red");
			mapData.vecColorTag.push_back("Yellow");
		}
		else if (objType == eTile03)
		{
			mapData.strObjName = string("Tile_04_Ground2_") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("Red");
			mapData.vecColorTag.push_back("Yellow");
		}
		else if (objType == eTile04)
		{
			mapData.strObjName = string("Tile_05_Rock") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("Black");
		}
		else if (objType == eTile05)
		{
			mapData.strObjName = string("Tile_07_Rock2_") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("Black");
		}
		else if (objType == eTile06)
		{
			mapData.strObjName = string("Tile_11_Sand") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("Red");
			mapData.vecColorTag.push_back("Yellow");
		}
		else if (objType == eTile07)
		{
			mapData.strObjName = string("Tile_12_Sand2") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("Red");
			mapData.vecColorTag.push_back("Yellow");
		}
		else if (objType == eTile08)
		{
			mapData.strObjName = string("Tile_13_Water") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("White");
		}
		else if (objType == eTile09)
		{
			mapData.strObjName = string("Tile_14_Water2_") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("White");
		}
		else if (objType == eTile10)
		{
			mapData.strObjName = string("Tile_15_Water3_") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("Blue");
		}
		else if (objType == eTile11)
		{
			mapData.strObjName = string("Tile_16_Water4_") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("Blue");
		}
		else if (objType == eTile12)
		{
			mapData.strObjName = string("Tile_17_Yellow") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("Yellow");
		}
		else if (objType == eTile13)
		{
			mapData.strObjName = string("Tile_Ocean") + to_string(m_nRefCnt + 1);
			mapData.vecColorTag.push_back("Blue");
		}

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

	case eBridge:
	{
		mapData.strObjName = string("Bridge") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Tile";
		mapData.strTxtPath = "Texture_01.png";

		// >> tagging
		mapData.vecColorTag.push_back("Red");
		mapData.vecColorTag.push_back("Yellow");

		mapData.strXFilePath = string("Bridge.X");

		CTile* tile = new CTile;
		tile->Setup(mapData);
	}
		break;

	// todo : setup���� ȭ�� �߾� ��ġ�� �̵�
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
		// todo : tagging
		mapData.vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

		if(index == 0)			mapData.strObjName = string("Autumn_Tree_01_") + to_string(m_nRefCnt + 1);
		else if (index == 1)	mapData.strObjName = string("Autumn_Tree_02_") + to_string(m_nRefCnt + 1);
		else if (index == 2)	mapData.strObjName = string("Autumn_Tree_03_") + to_string(m_nRefCnt + 1);
		else if (index == 3)	mapData.strObjName = string("Autumn_Tree_04_") + to_string(m_nRefCnt + 1);
		else if (index == 4)	mapData.strObjName = string("Autumn_Ctree_07_") + to_string(m_nRefCnt + 1);
		else if (index == 5)	mapData.strObjName = string("Autumn_Tree_08_") + to_string(m_nRefCnt + 1);
		
		mapData.vecColorTag.push_back("Yellow");

		mapData.strFolderPath = "Resource/XFile/Background/SeasonTree";
		mapData.strTxtPath = "autumn_texture.png";
		mapData.strXFilePath = string("AutumnTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eSTree:
	{
		// todo : tagging
		mapData.vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

		if (index == 0)			mapData.strObjName = string("Summer_Tree_01_") + to_string(m_nRefCnt + 1);
		else if (index == 1)	mapData.strObjName = string("Summer_Tree_02_") + to_string(m_nRefCnt + 1);
		else if (index == 2)	mapData.strObjName = string("Summer_Tree_03_") + to_string(m_nRefCnt + 1);
		else if (index == 3)	mapData.strObjName = string("Summer_Tree_04_") + to_string(m_nRefCnt + 1);
		else if (index == 4)	mapData.strObjName = string("Summer_Ctree_07_") + to_string(m_nRefCnt + 1);
		else if (index == 5)	mapData.strObjName = string("Summer_Tree_08_") + to_string(m_nRefCnt + 1);

		mapData.vecColorTag.push_back("Green");

		mapData.strFolderPath = "Resource/XFile/Background/SeasonTree";
		mapData.strTxtPath = "summer_texture.png";
		mapData.strXFilePath = string("SummerTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eWTree:
	{
		// todo : tagging
		mapData.vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
		
		if (index == 0)			mapData.strObjName = string("Winter_Tree_01_") + to_string(m_nRefCnt + 1);
		else if (index == 1)	mapData.strObjName = string("Winter_Tree_02_") + to_string(m_nRefCnt + 1);
		else if (index == 2)	mapData.strObjName = string("Winter_Tree_03_") + to_string(m_nRefCnt + 1);
		else if (index == 3)	mapData.strObjName = string("Winter_Tree_04_") + to_string(m_nRefCnt + 1);
		else if (index == 4)	mapData.strObjName = string("Winter_Ctree_07_") + to_string(m_nRefCnt + 1);
		else if (index == 5)	mapData.strObjName = string("Winter_Tree_08_") + to_string(m_nRefCnt + 1);

		mapData.vecColorTag.push_back("White");

		mapData.strFolderPath = "Resource/XFile/Background/SeasonTree";
		mapData.strTxtPath = "winter_texture.png";
		mapData.strXFilePath = string("WinterTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eCTree:
	{
		string name;
		if (index == 0) name = "A_Tree_Blue_016_";
		else if (index == 1) name = "A_Tree_Blue_020_";
		else if (index == 2) name = "C_Bush_Blue_070_";
		else if (index == 3) name = "C_Bush_Blue_071_";
		else if (index == 4)  name = "D_Shrub_Blue_101_";
		else if (index == 5) name = "D_Shrub_Blue_102_";

		// >> tagging
		mapData.vecColorTag.push_back("Blue");

		mapData.strObjName = name + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/ColorTree";
		mapData.strTxtPath = "TreesBlue.png";

		mapData.strXFilePath = string("Tree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eBall:
	{
		mapData.strObjName = string("Ball") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/Else";
		mapData.strTxtPath = "BeachBall_Base_Color.png";
		mapData.strXFilePath = "ball.X";

		// >> tagging
		mapData.vecColorTag.push_back("Blue");
		mapData.vecColorTag.push_back("Red");

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eChair:
	{
		mapData.strObjName = string("Blue_Chair") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/Else";
		mapData.strTxtPath = "";
		mapData.strXFilePath = "blue_chair.X";

		// >> tagging
		mapData.vecColorTag.push_back("Blue");

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eUmbrella:
	{
		// todo : tagging
		mapData.strObjName = string("Umbrella_Blue") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/Else";
		mapData.strTxtPath = "Umbrella_Blue.png";
		mapData.strXFilePath = "Umbrella.X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eSnowman:
	{
		// todo : tagging
		mapData.strObjName = string("Snowman") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/Else";
		mapData.strTxtPath = "Snowman.png";
		mapData.strXFilePath = "Snowman.X";

		mapData.vecColorTag.push_back("White");

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eFlower:
	{
		// todo : tagging
		// => material only, texture on/off set
		mapData.vScale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		
		string name;
		if (index == 0)
		{
			name = "_White";
			mapData.vecColorTag.push_back("White");
		}
		else if (index == 1)
		{
			name = "_Purple";
			mapData.vecColorTag.push_back("Red");
			mapData.vecColorTag.push_back("Blue");
		}
		else if (index == 2)
		{
			name = "_Red";
			mapData.vecColorTag.push_back("Red");
		}
		else if (index == 3)
		{
			name = "_Orange";
			mapData.vecColorTag.push_back("Red");
			mapData.vecColorTag.push_back("Yellow");
		}
		else if (index == 4)
		{
			name = "_Blue";
			mapData.vecColorTag.push_back("Blue");
		}
		else if (index == 5)
		{
			name = "_Yellow";
			mapData.vecColorTag.push_back("Yellow");
		}

		mapData.strObjName = string("Flower") + name + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/Else";
		mapData.strTxtPath = "";

		mapData.strXFilePath = string("Flower_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eSprout:
	{
		// todo : tagging
		mapData.vScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
		mapData.strObjName = string("Sprout") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background/Else";
		mapData.strTxtPath = "Sprout.png";

		mapData.vecColorTag.push_back("Green");

		mapData.strXFilePath = string("Sprout.X");

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eInvisibleWall:
	{
		mapData.vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		mapData.strObjName = string("InvisibleWall") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "";
		mapData.strTxtPath = "";
		mapData.strXFilePath = "";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eG_RotationBoard:
	case eG_MovingCube:
	case eG_Switch:
	case eG_DoorFrame:
#ifdef _DEBUG
	case eG_BreakWall:
	case eG_ColorChanger:
#endif // _DEBUG
	{
		CGimmick::CreateGimmick(objType);
	}
		break;

	case eBook:
	{
		mapData.vTranslate = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

		mapData.strObjName = string("Book") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Book";
		mapData.strTxtPath = "Bookshelf_diffuse.png";
		mapData.strXFilePath = "book.X";

		CBook* book = new CBook;
		book->Setup(mapData);
	}
	break;
	case eOrb:
	{
		mapData.vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		mapData.vTranslate = D3DXVECTOR3(0.5f, 0.6f, 0.5f);

		mapData.strObjName = string("Orb_Blue") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/Sprite/Orb";
		mapData.strTxtPath = "Orb_Blue.png";
		mapData.strXFilePath = "";

		COrb* orb = new COrb;
		orb->Setup(mapData);
	}
		break;
	case eTrace:
	{
		mapData.vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		mapData.vTranslate = D3DXVECTOR3(0.5f, 0.15f, 0.5f);

		mapData.vecColorTag.push_back("Blue");

		mapData.strObjName = string("Trace_Blue") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/Sprite/Trace";
		mapData.strTxtPath = "WaterColor_Blue.png";
		mapData.strXFilePath = "";

		CTrace* trace = new CTrace;
		trace->Setup(mapData);
	}
	break;
		
	case eTrigger:
	{
		mapData.vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		mapData.strObjName = string("EventTrigger_Save") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "";
		mapData.strTxtPath = "";
		mapData.strXFilePath = "";

		mapData.triggerIndex = 0;

		CEventTrigger* trigger = new CEventTrigger;
		trigger->Setup(mapData);
	}
		break;

	} // << : switch
}

void IObject::CreateObject(ST_MapData& mapData)
{
	// >> SaveLoad ���� ����
	switch (mapData.objType)
	{
	case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
	case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
	case eBridge:
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
	case eBall:
	case eChair:
	case eUmbrella:
	case eSnowman:
	case eFlower:
	case eSprout:
	case eInvisibleWall:
	{
		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eG_RotationBoard:	case eG_MovingCube:
	case eG_DoorFrame:		case eG_Door:
	case eG_Switch:
	
#ifdef _DEBUG
	case eG_BreakWall:	case eG_ColorChanger:
#endif // _DEBUG
	{
		CGimmick::CreateGimmick_SaveData(mapData);
	}
	break;

	case eBook:
	{
		CBook* book = new CBook;
		book->Setup(mapData);
	}
	break;

	case eOrb:
	{
		COrb* orb = new COrb;
		orb->Setup(mapData);
	}
	break;

	case eTrace:
	{
		CTrace* trace = new CTrace;
		trace->Setup(mapData);
	}
		break;

	case eTrigger:
	{
		CEventTrigger* trigger = new CEventTrigger;
		trigger->Setup(mapData);
	}
		break;
	} // << : switch
}
