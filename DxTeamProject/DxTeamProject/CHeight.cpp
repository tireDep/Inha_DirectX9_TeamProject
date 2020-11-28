#include "StdAfx.h"
#include "CHeight.h"


CHeight::CHeight(void)
	: m_pMesh(NULL)
{
}


CHeight::~CHeight(void)
{
	SafeRelease(m_pMesh);
}

void CHeight::Setup(char* szFolder,
	char* szRawFile,
	int nBytesPerColor /*= 1*/)
{
	std::string sFullPath(szFolder);
	sFullPath = sFullPath + std::string("/") + std::string(szRawFile);


	FILE* fp = NULL;
	fopen_s(&fp, sFullPath.c_str(), "rb");

	fseek(fp, 0, SEEK_END);

	int nFileSize = ftell(fp);

	fseek(fp, 0, SEEK_SET);

	int nNumColor = nFileSize / nBytesPerColor;

	int nRowCount = (int)(sqrt((float)nNumColor) + 0.0001f);

	assert(nRowCount * nRowCount == nNumColor);

	int nTile = nRowCount - 1;

	m_nTile = nTile;

	std::vector<ST_PNT_VERTEX> vecVertex;

	vecVertex.reserve(nNumColor);

	for (int z = 0; z < nRowCount; ++z)
	{
		for (int x = 0; x < nRowCount; ++x)
		{
			float y = (float)fgetc(fp) / 10.f;

			ST_PNT_VERTEX v;
			v.p = D3DXVECTOR3(x, y, z);
			v.t = D3DXVECTOR2(x / (float)nTile, z / (float)nTile);
			v.n = D3DXVECTOR3(0, 1, 0);
			vecVertex.push_back(v);
			m_vecVertex.push_back(v.p);
		}
	}

	for (int z = 1; z < nRowCount - 1; ++z)
	{
		for (int x = 1; x < nRowCount - 1; ++x)
		{
			int nIndex = z * nRowCount + x;

			int left = nIndex - 1;
			int right = nIndex + 1;
			int up = nIndex + nRowCount;
			int down = nIndex - nRowCount;

			D3DXVECTOR3 lr = vecVertex[right].p - vecVertex[left].p;
			D3DXVECTOR3 du = vecVertex[up].p - vecVertex[down].p;
			D3DXVECTOR3 n;
			D3DXVec3Cross(&n, &du, &lr);
			D3DXVec3Normalize(&n, &n);
			vecVertex[nIndex].n = n;
		}
	}

	std::vector<DWORD> vecIndex;
	vecIndex.reserve(nTile * nTile * 3 * 2);

	//		1--3
	//		|\ |
	//		| \|
	//		0--2


	for (int z = 0; z < nTile; ++z)
	{
		for (int x = 0; x < nTile; ++x)
		{
			DWORD _0 = (z + 0) * nRowCount + x + 0;
			DWORD _1 = (z + 1) * nRowCount + x + 0;
			DWORD _2 = (z + 0) * nRowCount + x + 1;
			DWORD _3 = (z + 1) * nRowCount + x + 1;

			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_2);

			vecIndex.push_back(_3);
			vecIndex.push_back(_2);
			vecIndex.push_back(_1);
		}
	}

	fclose(fp);


	D3DXCreateMeshFVF(vecIndex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh);

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
	ZeroMemory(pA, sizeof(DWORD) * m_pMesh->GetNumFaces());
	m_pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecIndex.size());
	m_pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0]
		, 0, 0, 0);


	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));

	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

}

void CHeight::Render()
{

	D3DXMATRIXA16 matS, matR, matT;
	D3DXVECTOR3 m_vScale = D3DXVECTOR3(1, 1, 1);
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);


	
	// D3DXMatrixTranslation(&matT, eye.x, eye.y, eye.z);

	D3DXMATRIXA16 matWorld = matS;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	m_pMesh->DrawSubset(0);
}

bool CHeight::GetHeight(IN float x, OUT float& y, IN float z)
{
	int nX = (int)x;
	int nZ = (int)z;

	if (nX < 0 || nZ < 0 || nX > m_nTile || nZ > m_nTile)
	{
		y = 0.0f;
		return false;
	}
	//		1--3
	//		|\ |
	//		| \|
	//		0--2
	DWORD _0 = (nZ + 0) * (m_nTile + 1) + nX + 0;
	DWORD _1 = (nZ + 1) * (m_nTile + 1) + nX + 0;
	DWORD _2 = (nZ + 0) * (m_nTile + 1) + nX + 1;
	DWORD _3 = (nZ + 1) * (m_nTile + 1) + nX + 1;

	float fDX = x - nX;
	float fDZ = z - nZ;
	if (fDX + fDZ < 1)
	{
		D3DXVECTOR3 _01 = m_vecVertex[_1] - m_vecVertex[_0];
		D3DXVECTOR3 _02 = m_vecVertex[_2] - m_vecVertex[_0];
		D3DXVECTOR3 v = _01 * fDZ + _02 * fDX;
		y = m_vecVertex[_0].y + v.y;
	}
	else
	{
		D3DXVECTOR3 _31 = m_vecVertex[_1] - m_vecVertex[_3];
		D3DXVECTOR3 _32 = m_vecVertex[_2] - m_vecVertex[_3];

		fDX = 1.0f - fDX;
		fDZ = 1.0f - fDZ;

		D3DXVECTOR3 v = _31 * fDX + _32 * fDZ;
		y = m_vecVertex[_3].y + v.y;
	}
	return true;
}
