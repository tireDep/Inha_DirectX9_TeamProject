#include "stdafx.h"

#include "cBody.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cLeftLeg.h"
#include "cRightLeg.h"
#include "cHead.h"

#include "cCubeMan.h"


cCubeMan::cCubeMan()
	: m_pRoot(NULL)
{

}


cCubeMan::~cCubeMan()
{
	if (m_pRoot)
		m_pRoot->Destroy(); 

	SafeRelease(m_pTexture);
}


void cCubeMan::Setup()
{
	cCharacter::Setup(); 

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9)); 
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f); 
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	cBody*	pBody = new cBody; 
	pBody->Setup(); 
	pBody->SetParentWorldTM(&m_matWorld); 
	m_pRoot = pBody; 

	cHead* pHead = new cHead; 
	pHead->Setup(); 

	m_pRoot->AddChild(pHead); 

	cLeftArm* pLArm = new cLeftArm; 
	pLArm->Setup(); 
	pLArm->SetRotDeltaX(0.1f); 
	m_pRoot->AddChild(pLArm); 

	cRightArm* pRArm = new cRightArm;
	pRArm->Setup();
	pRArm->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pRArm);

	cLeftLeg* pLLeg = new cLeftLeg;
	pLLeg->Setup();
	pLLeg->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pLLeg);

	cRightLeg* pRLeg = new cRightLeg;
	pRLeg->Setup();
	pRLeg->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(pRLeg);

	D3DXCreateTextureFromFile(g_pD3DDevice, L"../image/mkLink.png", &m_pTexture);
}

void cCubeMan::Update(iMap *pMap)
{
	cCharacter::Update(pMap);
	if (m_pRoot)
		m_pRoot->Update();	// cCubeNode -> Update() 
}

void cCubeMan::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true); 
		// g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		g_pD3DDevice->SetMaterial(&m_stMtl); 

		cCharacter::Render(); 

		D3DXMATRIXA16 matWorld; 
		D3DXMatrixIdentity(&matWorld); 
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
		
		g_pD3DDevice->SetTexture(0, m_pTexture);

		if (m_pRoot)
			m_pRoot->Render();	// cCubeNode -> Render()

		g_pD3DDevice->SetTexture(0, NULL);
	}
}

/*
[ todo ]
1. Grid : pn으로 변경, light 적용
2. Directional Light : 해 뜨고 지는 것
3. Spot Light : 키 입력에 따라 방향조정
4. Point Light : 키 입력에 따라 범위 조정
5. 각 라이트의 위치를 박스로 표시할 것
*/