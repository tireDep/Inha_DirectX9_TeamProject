#include "stdafx.h"
#include "Object.h"
#include "Ray.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Background.h"
#include "Tile.h"
#include "Gimmick.h"
#include "Book.h"
#include "Orb.h"
#include "Trace.h"
#include "EventTrigger.h"

int CObject::m_nRefCount = 0;

CObject::CObject() : 
	m_pMesh(NULL),
	m_pTexture(NULL),
	m_adjBuffer(NULL),
	m_vScale(0, 0, 0),
	m_vRotation(0, 0, 0),
	m_vTranslation(0, 0, 0),
	m_numMtrls(0),
	m_strObjName(""),
	m_strFolder(""),
	m_strXFile(""),
	m_strTxtFile(""),
	m_ObjectType(ObjectType::eNull)
{
	CObject::m_nRefCount += 1;
	g_pObjectManager->AddObject(this);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
}

CObject::~CObject()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
}

void CObject::Release()
{
	g_pObjectManager->RemoveObject(this);
	CObject::m_nRefCount -= 1;
}

void CObject::CreateObject(const ST_MapData & mapData)
{
	switch (mapData.objType)
	{
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
	case eATree:	case eSTree:			case eWTree:	case eCTree:
	case eBall:		case eChair:			case eUmbrella:	case eSnowman:
	case eFlower:	case eInvisibleWall:	case eSprout:
	{
		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;
	case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
	case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
	case eBridge:
	{
		CTile* tile = new CTile;
		tile->Setup(mapData);
	}
	break;
	case eG_RotationBoard:	case eG_BreakWall:	case eG_DoorFrame: case eG_Door:	
	case eG_ColorChanger:	case eG_Switch:		case eG_MovingCube:
	{
		CGimmick::Setup(mapData);
	}
		break;
	case eBook:
	{
		CBook* tile = new CBook;
		tile->Setup(mapData);
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