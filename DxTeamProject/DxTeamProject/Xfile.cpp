#include "stdafx.h"
#include "Xfile.h"
#include "OBB.h"

CXfile::CXfile() 
{
}


CXfile::~CXfile()
{
}

void CXfile::Setup()
{
	HRESULT hr = 0;
	hr = D3DXLoadMeshFromX(L"Sky/brush_model_test.X", D3DXMESH_MANAGED, g_pD3DDevice, &adjBuffer, &mtrlBuffer, 0, &numMtrls, &Mesh);

	if (FAILED(hr))
	{
		::MessageBox(0, L"D3DXLoadMeshFromX() - FAILED", 0, 0);
		return;
	}

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (int i = 0; i < numMtrls; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			Mtrls.push_back(mtrls[i].MatD3D);
			if (mtrls[i].pTextureFilename == NULL)
				continue;
			string filename = string("Sky") + "/" + mtrls[i].pTextureFilename;

			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFileA(g_pD3DDevice, filename.c_str(), &tex);

				Textures.push_back(tex);
			}
			else
			{
				Textures.push_back(0);
			}
		}
	}
	SafeRelease(mtrlBuffer);


	//D3DXCreateBox(g_pD3DDevice, 1.0f, 1.0f, 1.0f, &Mesh, NULL);

	D3DXVECTOR3* pVertices;

	D3DXVECTOR3 m_vMin, m_vMax;

	Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);

	D3DXComputeBoundingBox(pVertices, Mesh->GetNumVertices(), Mesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);

	Mesh->UnlockVertexBuffer();

	m_pOBB = new COBB;
	m_pOBB->SetUpXFile(m_vMin , m_vMax );

}

void CXfile::Update()
{


	//m_pOBB->Update(&World);
}

void CXfile::Render(D3DXVECTOR3 eye)
{


	if (g_pD3DDevice)
	{
		D3DXMATRIXA16 scale;
		D3DXMATRIXA16 move;
		
		if (m_pOBB)
			m_pOBB->OBBBOX_RENDER(D3DCOLOR_XRGB(255, 0, 0));
		
	
		D3DXMatrixScaling(&scale, 1, 1, 1);
		D3DXMatrixTranslation(&move, eye.x, eye.y, eye.z);
		D3DXMATRIXA16 World = scale * move;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &scale);


		for (int i = 0; i < Mtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&Mtrls[i]);
			//g_pD3DDevice->SetTexture(0, Textures[i]);
			Mesh->DrawSubset(i);
		}

		
	}
	

}
