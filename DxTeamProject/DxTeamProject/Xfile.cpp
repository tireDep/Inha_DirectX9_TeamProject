#include "stdafx.h"
#include "Xfile.h"


CXfile::CXfile()
{
}


CXfile::~CXfile()
{
}

void CXfile::Setup()
{
	HRESULT hr = 0;
	hr = D3DXLoadMeshFromX(L"Sky/skydome_text.X", D3DXMESH_MANAGED, g_pD3DDevice, &adjBuffer, &mtrlBuffer, 0, &numMtrls, &Mesh);

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
}

void CXfile::Render()
{
	if (g_pD3DDevice)
	{
		D3DXMATRIX scale;

		D3DXMatrixScaling(&scale, 0.1f, 0.1f, 0.1f);
		D3DXMATRIX World = scale;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &World);


		for (int i = 0; i < Mtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&Mtrls[i]);
			g_pD3DDevice->SetTexture(0, Textures[i]);
			Mesh->DrawSubset(i);
		}
	}
}
