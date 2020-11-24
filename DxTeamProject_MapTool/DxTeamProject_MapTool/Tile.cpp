#include "stdafx.h"
#include "Tile.h"

CTile::CTile()
{
	m_pMesh = NULL;
	m_pTexture = NULL;

	m_strObjName = string("Tile") + to_string(m_nRefCnt);	
	// todo : 이름 변경 가능해야 함

	m_strFilePath = "tempPath";
	// todo : 파일 경로로 불러와야 함
	// todo : text 따로 불러와야 할 수도?

	m_ObjectType = ObjectType::eTile;

	m_vScale = D3DXVECTOR3(1, 1, 1);
	m_vRotate = D3DXVECTOR3(0, 0, 0);
	m_vTranslate = D3DXVECTOR3(0, 0.5f, 0);
}

CTile::~CTile()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_pTexture);
}

void CTile::Setup()
{
	D3DXCreateBox(g_pD3DDevice, m_vScale.x, m_vScale.y, m_vScale.z, &m_pMesh, NULL);
	// todo : 파일 로드
	
	ZeroMemory(&m_pMtrl, sizeof(D3DMATERIAL9));
	m_pMtrl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMtrl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMtrl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// todo : 임시 매터리얼 설정 -> 변경
}

void CTile::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFilePath = setData.strFilePath;
	m_ObjectType = setData.objType;

	m_vScale = setData.vScale;
	m_vRotate = setData.vRotate;
	m_vTranslate = setData.vTranslate;

	Setup();
}

void CTile::Update()
{
}

void CTile::Render()
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

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_pMtrl);
	
	g_pD3DDevice->SetTexture(0, 0);
	// >> todo : 예외처리 추가

	if (m_pMesh)
	{
		m_pMesh->DrawSubset(0);
	}
}
