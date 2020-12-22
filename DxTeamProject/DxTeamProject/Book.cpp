#include "stdafx.h"
#include "Book.h"
#include "SkinnedMesh.h"

int CBook::m_nCount = 0;

CBook::CBook()
	: m_fRotationSpeed(1.0f)
	, m_fRotAngle(0.0f)
	, pBox(false)
	, render(true)
{
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);

	CBook::m_nCount += 1;
}

CBook::~CBook()
{
}

void CBook::Setup()
{
	ST_XFile* xfile = new ST_XFile;

	if (!g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Book", "book.X", xfile))
	{
		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
		return;
	}

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	delete xfile;

	/*m_pOBB = new CPSOBB;
	m_pOBB->Setup(*this);*/
	//g_pObjectManager->AddOBBbox(m_pOBB);
}

void CBook::Setup(ST_MapData setData)
{
	CItem::Setup(setData);

	if (g_pGameManager->SaveBook() == false)
		render = false;
	else
		render = true;

	//m_strObjName = setData.strObjName;
	//m_strFolder = setData.strFolderPath;
	//m_strXFile = setData.strXFilePath;
	//m_strTxtFile = setData.strTxtPath;
	//m_ObjectType = setData.objType;

	//D3DXVECTOR3 vScale, vRotate, vTranslate;

	//vScale = setData.vScale; // 0.01, 0.03, 0.01, 0.01
	//						 // JW ADD...
	//m_vScale = vScale;
	//vRotate = setData.vRotate;
	//vTranslate = setData.vTranslate;

	//m_strConditionName = setData.gimmickData.conditionName;

	//ST_XFile* xfile = new ST_XFile;

	//g_pFileLoadManager->FileLoad_XFile(m_strFolder, m_strXFile, xfile);

	//if (m_strTxtFile != "")
	//	g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

	//m_pMesh = xfile->pMesh;
	//m_adjBuffer = xfile->adjBuffer;
	//m_vecMtrls = xfile->vecMtrl;
	//m_vecTextures = xfile->vecTextrure;
	//m_numMtrls = xfile->nMtrlNum;

	//delete xfile;

	//D3DXMatrixScaling(&m_matS, vScale.x, vScale.y, vScale.z);

	//D3DXVECTOR3 v;
	//v.x = D3DXToRadian(vRotate.x);
	//v.y = D3DXToRadian(vRotate.y);
	//v.z = D3DXToRadian(vRotate.z);

	//D3DXMatrixRotationYawPitchRoll(&m_matR, v.y, v.x, v.z);

	//D3DXMatrixTranslation(&m_matT, vTranslate.x, vTranslate.y, vTranslate.z);
	//m_matWorld = m_matS * m_matR * m_matT;

	//// OBB TEST
	//m_pOBB = new COBB;
	//m_pOBB->Setup(*this);
	//g_pObjectManager->AddOBBbox(m_pOBB);
	//m_pOBB->Update(&m_matWorld);

}

void CBook::Update(float duration)
{
	m_fRotAngle += m_fRotationSpeed * duration;

	if (m_fRotAngle > 2 * D3DX_PI)
		m_fRotAngle -= 2 * D3DX_PI;

	D3DXMatrixRotationY(&m_matRot, m_fRotAngle);
	m_matWorld = m_matS * m_matRot * m_matT;
	m_pOBB->Update(&m_matWorld);
}

bool CBook::hasIntersected(CSkinnedMesh * Character)
{
	/*if (this->m_pOBB->IsCollision(Character->GetOBB()))
	{
		CObject::Release();
		return true;
	}*/
	return false;
}

void CBook::Render()
{
	//D3DXMATRIXA16 matWorld;
	//D3DXMatrixIdentity(&matWorld);
	//D3DXMATRIXA16 matS, matR ,matT;
	//static float Rot = 0;
	//Rot++;
	//D3DXMatrixScaling(&matS, 0.3f, 0.3f, 0.3f);
	//D3DXMatrixRotationY(&matR,Rot*0.01f);
	//D3DXMatrixTranslation(&matT, 12, 0, 0);
	//matWorld = matS* matR * matT;
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (m_pMesh == NULL)
		return;

	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		if (m_vecTextures[i] != 0)
			g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
		g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
		m_pMesh->DrawSubset(i);
	}
	if (player == true || render == false)
	{	
		if (m_strConditionName != "")
		{
			ST_EVENT msg;
			msg.eventType = EventType::eConditionChange;
			msg.isCondition = false;
			msg.conditionName = m_strObjName;

			g_pEventManager->CheckEvent(msg);
		}
		render = false;
		g_pEventManager->RemoveListener(this);

		SafeRelease(m_pMesh);
		g_pObjectManager->RemoveObject(m_pOBB);
	}

	
	g_pD3DDevice->SetTexture(0, NULL);
}
