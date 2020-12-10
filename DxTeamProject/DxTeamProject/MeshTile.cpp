#include "stdafx.h"
#include "MeshTile.h"
#include "OBB.h"
MeshTile::MeshTile()
	: m_pMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	ZeroMemory(&m_stMtlSphere2, sizeof(D3DMATERIAL9));


	
}

MeshTile::~MeshTile()
{
	SafeDelete(m_pOBB);
	SafeRelease(m_pMesh);
}

void MeshTile::Setup(float x, float y, float z)
{
	D3DXCreateBox(g_pD3DDevice, 0.5,0.5,0.5, &m_pMesh, NULL);

	D3DXVECTOR3* pDVertices;
	D3DXVECTOR3 m_vMin, m_vMax;

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pDVertices);
	D3DXComputeBoundingBox(pDVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);

	m_pMesh->UnlockVertexBuffer();

	/*m_pOBB = new COBB;
	m_pOBB->Setup(this);*/
	


	m_stMtlSphere2.Ambient = RED;
	m_stMtlSphere2.Diffuse = RED;
	m_stMtlSphere2.Specular = RED;

	
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;

	//DWORD dwVertexNum = m_pMesh->GetNumVertices();
	//LPDIRECT3DVERTEXBUFFER9 pVB;
	//m_pMesh->GetVertexBuffer(&pVB);
	//float* pVertices;
	//pVB->Lock(0, sizeof(m_pMesh->GetNumBytesPerVertex()) * m_pMesh->GetNumVertices(), (void**)&pVertices, 0);
	//for (DWORD i = 0; i < dwVertexNum * 6; i += 3)
	//{
	//	pVertices[i	   ] *= m_matS._11;		pVertices[i]     += m_matT._41;
	//	pVertices[i + 1] *= m_matS._22;		pVertices[i + 1] += m_matT._42;
	//	pVertices[i + 2] *= m_matS._33;		pVertices[i + 2] += m_matT._43;
	//}
	//pVB->Unlock();


}


void MeshTile::Render()
{
	
	D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXVECTOR3 m_vScale = D3DXVECTOR3(1, 1, 1);
	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);
	m_matWorld = m_matS * m_matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	g_pD3DDevice->SetMaterial(&m_stMtlSphere2);
	
	//m_pOBB->OBBBOX_RENDER(D3DCOLOR_XRGB(255,0,0));
	m_pMesh->DrawSubset(0);
}

D3DXMATRIXA16 MeshTile::GetMatWorld()
{
	return m_matWorld;
}

void MeshTile::Update()
{
	/*D3DXMATRIXA16 matS, matR, matT;
	D3DXVECTOR3 m_vScale, m_vRotate, m_vTranslate;

	m_vScale = D3DXVECTOR3(1, 1, 1);
	m_vRotate = D3DXVECTOR3(0, 0, 0);
	m_vTranslate = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationX(&matR, m_vRotate.x);
	D3DXMatrixRotationY(&matR, m_vRotate.y);
	D3DXMatrixRotationZ(&matR, m_vRotate.z);

	D3DXMatrixTranslation(&matT, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);*/

	m_pOBB->Update(&m_matWorld);
}


