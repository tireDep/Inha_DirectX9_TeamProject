#include "stdafx.h"
#include "HeigthMap.h"

CHeigthMap::CHeigthMap() :
	m_pTexture(NULL),
	m_pMesh(NULL),
	m_pViewMesh(NULL)
{
}

CHeigthMap::~CHeigthMap()
{
	Destroy();
}

void CHeigthMap::SetUp(char * szFolder, char * szRaw, char * szTex, DWORD dwBytesPerPixel)
{
	string sFolder(szFolder);
	string sRaw = sFolder + string(szRaw);
	string sTex = sFolder + string(szTex);

	m_pTexture = g_pTextureManager->GetTexture(sTex);

	// >> raw
	FILE* fp = NULL;
	fopen_s(&fp, sRaw.c_str(), "rb");

	fseek(fp, 0, SEEK_END);
	int nFileSize = ftell(fp);
	int nNumVertex = nFileSize / dwBytesPerPixel;	// ���� ����Ʈ 1�����Ƿ� ���� ������ == ���ؽ� ����
													// ���� ũ�� ���

	int nRow = (int)(sqrt((float)nNumVertex) + 0.0001f);
	int nCol = nRow;
	// +0.0001f : �Ǽ� ���� �� �� ���� �ٿ���
	// �������̶� col == row
	int nTileN = nRow - 1;
	m_nTileN = nTileN;
	// ��, �� ���

	fseek(fp, 0, SEEK_SET);
	// 

	vector<ST_PNT_VERTEX> vecVertex(nNumVertex);
	m_vecVertex.resize(nNumVertex);

	vector<DWORD> vecIndex;	// �ε��� ����
	vecIndex.reserve(nTileN * nTileN * 2 * 3);
	// �� 3��, �ﰢ�� 2��

	for (int i = 0; i < nNumVertex; i++)
	{
		ST_PNT_VERTEX v;
		v.p = D3DXVECTOR3(i % nCol, ((unsigned char)fgetc(fp)) / 10.0f, i / nCol);
		v.n = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2((i%nCol) / (float)nCol, (i / nCol) / (float)nCol);

		vecVertex[i] = v;
		m_vecVertex[i] = v.p;	// ���� ����

		if (dwBytesPerPixel == 3)
		{
			// 1����Ʈ�� �ƴ� 3����Ʈ�� �� ���� ��� �ڿ� ���� ������ ��
			fgetc(fp), fgetc(fp);
		}
	}

	fclose(fp);
	// << raw

	// >> normalVector
	// ���
	// 1. �� �� ���� normalVector ���ϰ�(������ ���ϴ� ���), ������ �� ����
	// 2. �� �� ���� ���� �� ����, �¿� �� ���� ���ϰ� ũ�ν�-> �븻����, �ܰ����� ��쿡�� ������ ������ ����Ʈ �� �����
	// 2�� ���
	for (int x = 1; x < nTileN; x++)
	{
		for (int z = 1; z < nTileN; z++)
		{
			int left = (z + 0) * nCol + x - 1;
			int right = (z + 0) * nCol + x + 1;

			int up = (z + 1) * nCol + x;
			int down = (z - 1) * nCol + x;

			D3DXVECTOR3 leftToRight = m_vecVertex[right] - m_vecVertex[left];
			D3DXVECTOR3 downToUp = m_vecVertex[up] - m_vecVertex[down];

			D3DXVECTOR3 normal;
			D3DXVec3Cross(&normal, &downToUp, &leftToRight);
			D3DXVec3Normalize(&normal, &normal);

			int nIndex = z * nCol + x;
			vecVertex[nIndex].n = normal;
		}
	}
	// << normalVector

	// >> Added
	m_vecPNTVertex = vecVertex;

	// >> indexBuffer
	for (int x = 0; x < nTileN; x++)
	{
		for (int z = 0; z < nTileN; z++)
		{
			// �ε���
			// 1 2
			// 0 3
			int _0 = (z + 0) * nCol + x + 0;
			int _1 = (z + 1) * nCol + x + 0;
			int _2 = (z + 1) * nCol + x + 1;
			int _3 = (z + 0) * nCol + x + 1;

			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_3);

			vecIndex.push_back(_2);
			vecIndex.push_back(_3);
			vecIndex.push_back(_1);
		} // : for_z
	} // : for_x
	// << indexBuffer

	// >> Added
	m_vecindex = vecIndex;
	  
	// >> mesh
	D3DXCreateMeshFVF(vecIndex.size() / 3, vecVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_pMesh);
	// ���� ����, ���ؽ� ����

	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD)); // ��ü 0���� ����
	m_pMesh->UnlockAttributeBuffer();

	vector<DWORD> vecAdj(vecIndex.size());
	m_pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);
	// << mesh

	// >> material
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	// << material
}

void CHeigthMap::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	if(m_pViewMesh!=NULL)
		m_pViewMesh->DrawSubset(0);
	else
		m_pMesh->DrawSubset(0);
}

bool CHeigthMap::GetHeight(IN float x, OUT float & y, IN float z)
{
	if (x < 0.f || z < 0.f || x >= m_nTileN || z >= m_nTileN)
	{
		// ������ ��� ���
		y = 0;
		return false;
	}

	int nX = x;
	int nZ = z;
	// �Ҽ��� ���� ����

	float fDeltaX = x - nX;
	float fDeltaZ = z - nZ;

	// �ε���
	// 1 2
	// 0 3
	int _0 = (nZ + 0) * (m_nTileN + 1) + nX + 0;
	int _1 = (nZ + 1) * (m_nTileN + 1) + nX + 0;
	int _2 = (nZ + 1) * (m_nTileN + 1) + nX + 1;
	int _3 = (nZ + 0) * (m_nTileN + 1) + nX + 1;

	// �밢�� == 1
	if (fDeltaX + fDeltaZ < 1.0f)
	{
		// �밢�� �Ʒ��δ� 1�� �Ѿ�� ����
		D3DXVECTOR3 v01 = m_vecVertex[_1] - m_vecVertex[_0];
		D3DXVECTOR3 v03 = m_vecVertex[_3] - m_vecVertex[_0];

		y = m_vecVertex[_0].y + (v01 * fDeltaZ + v03 * fDeltaX).y;
	}
	else
	{
		// �밢�� ���δ� 1�� �Ѿ
		fDeltaX = 1.0f - fDeltaX;
		fDeltaZ = 1.0f - fDeltaZ;

		D3DXVECTOR3 v21 = m_vecVertex[_1] - m_vecVertex[_2];
		D3DXVECTOR3 v23 = m_vecVertex[_3] - m_vecVertex[_2];

		y = m_vecVertex[_2].y + (v21 * fDeltaX + v23 * fDeltaZ).y;
	}

	return true;
}

void CHeigthMap::Destroy()
{
	SafeRelease(m_pTexture);
	SafeRelease(m_pMesh);
	SafeRelease(m_pViewMesh);
}

vector<D3DXVECTOR3> CHeigthMap::GetVecVertex()
{
	return m_vecVertex;
}

// >> Added
void CHeigthMap::SetFrustumMap(const vector<bool>& vecCheck)
{
	vector<DWORD> vecIndex;
	for (int i = 0; i < m_vecindex.size() - 3; i+=3)
	{
		if (vecCheck[m_vecindex[i + 0]] == false && vecCheck[m_vecindex[i + 1]] == false && vecCheck[m_vecindex[i + 2]] == false)
		{
			continue;
		}

		vecIndex.push_back(m_vecindex[i + 0]);
		vecIndex.push_back(m_vecindex[i + 1]);
		vecIndex.push_back(m_vecindex[i + 2]);

	} // : for

	if (vecIndex.size() == 0)
	{
		// ���� ���� �ڵ�
		m_pViewMesh = NULL;
		return;
	}

	m_pViewMesh = NULL;
	D3DXCreateMeshFVF(vecIndex.size() / 3, m_vecPNTVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_pViewMesh);

	ST_PNT_VERTEX* pV = NULL;
	m_pViewMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecPNTVertex[0], m_vecPNTVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pViewMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_pViewMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	m_pViewMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pViewMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD)); // ��ü 0���� ����
	m_pViewMesh->UnlockAttributeBuffer();

	vector<DWORD> vecAdj(vecIndex.size());
	m_pViewMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	m_pViewMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);
	// << mesh

	// // >> material
	// ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	// m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	// m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	// m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	// // << material
}
