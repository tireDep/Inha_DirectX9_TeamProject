#include "stdafx.h"
#include "Tile.h"

CTile::CTile()
{
	m_pMesh = NULL;
	m_pTexture = NULL;
}

CTile::~CTile()
{
}

void CTile::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;
	m_vScale = setData.vScale;
	m_vRotate = setData.vRotate;
	m_vTranslate = setData.vTranslate;

	m_vecColorTag = setData.vecColorTag;

	if (m_ObjectType == ObjectType::eTile13)
	{
		m_pMtrl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_pMtrl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_pMtrl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (m_strTxtFile != "")
			g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

		ST_PNT_VERTEX v;
		float f = 1.0f;
		v.p = D3DXVECTOR3(-f, 0, -f);	v.t = D3DXVECTOR2(1, 0); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-f, 0, f);	v.t = D3DXVECTOR2(0, 0); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(f, 0, f);		v.t = D3DXVECTOR2(0, 1); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-f, 0, -f);	v.t = D3DXVECTOR2(1, 0); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(f, 0, f);		v.t = D3DXVECTOR2(0, 1); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(f, 0, -f);	v.t = D3DXVECTOR2(1, 1); m_vecVertex.push_back(v);

		D3DXVECTOR3 n1, n2, normal;
		for (int i = 0; i < m_vecVertex.size(); i += 3)
		{
			n1 = m_vecVertex[i].p - m_vecVertex[i + 1].p;
			n2 = m_vecVertex[i].p - m_vecVertex[i + 2].p;
			D3DXVec3Cross(&normal, &n1, &n2);

			m_vecVertex[i + 0].n = normal;
			m_vecVertex[i + 1].n = normal;
			m_vecVertex[i + 2].n = normal;
		}

		// >> createMesh
		vector<DWORD> vecAttrBuf;
		for (int i = 0; i < m_vecVertex.size(); i++)
			vecAttrBuf.push_back(0);

		D3DXCreateMeshFVF(vecAttrBuf.size(), m_vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_pMesh);

		ST_PNT_VERTEX* pV = NULL;
		m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
		memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEX));
		m_pMesh->UnlockVertexBuffer();

		WORD* pI = NULL;
		m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
		for (int i = 0; i < m_vecVertex.size(); i++)
			pI[i] = i;
		m_pMesh->UnlockIndexBuffer();

		DWORD* pA = NULL;
		m_pMesh->LockAttributeBuffer(0, &pA);
		memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
		m_pMesh->UnlockAttributeBuffer();
		// << createMesh

		m_vecMtrls.push_back(m_pMtrl);
	}
	else
	{
		ST_XFile* xfile = new ST_XFile;

		g_pFileLoadManager->FileLoad_XFile(m_strFolder, m_strXFile, xfile);

		if (m_strTxtFile != "")
			g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

		m_pMesh = xfile->pMesh;
		m_adjBuffer = xfile->adjBuffer;
		m_vecMtrls = xfile->vecMtrl;
		m_vecTextures = xfile->vecTextrure;
		m_numMtrls = xfile->nMtrlNum;

		delete xfile;
	}

	IObject::Setup_OBB_Box();
}

void CTile::Update()
{
}

void CTile::Render()
{
	IObject::Render_OBB_Box();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetmatWorld());
	
	if (m_pMesh == NULL)
		return;

	if (!m_isPick && !m_isClick || !m_pShader)
	{
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

			if (ObjectType::eTile13 == m_ObjectType)
			{
				if (m_pTexture != NULL)
					g_pD3DDevice->SetTexture(0, m_pTexture);
			}
			else
			{

				if (m_vecTextures[i] != 0)
					g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
				else if (m_pTexture != NULL)
					g_pD3DDevice->SetTexture(0, m_pTexture);
				// >> 텍스처 매치 안되있을 때
			}

			m_pMesh->DrawSubset(i);
		}
	}
	else
	{
		SetShader(GetmatWorld());
		IObject::Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
}
