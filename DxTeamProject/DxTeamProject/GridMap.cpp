#include "stdafx.h"
#include "GridMap.h"

#define mapSize 15
#define mapSpace 1.f

CRITICAL_SECTION cs;

CGridMap::CGridMap() :
	m_Texture(NULL),
	m_origMesh(NULL),
	m_nowMesh(NULL),
	m_frustum(NULL)
{
}

CGridMap::~CGridMap()
{
	SafeRelease(m_origMesh);
	SafeRelease(m_nowMesh);
	SafeRelease(m_Texture);
}

void CGridMap::Setup()
{
	InitializeCriticalSection(&cs);

	ST_PNT_VERTEX vertex;
	// >> vertex
	for (float j = -mapSize; j < mapSize; j += mapSpace)
	{
		for (float i = -mapSize; i < mapSize; i += mapSpace)
		{
			vertex.p = D3DXVECTOR3(j + 1, 0, i);
			vertex.n = D3DXVECTOR3(0, 1, 0);
			vertex.t = D3DXVECTOR2(0, 0);
			m_vecVertex.push_back(vertex);

			vertex.p = D3DXVECTOR3(j, 0, i);
			vertex.n = D3DXVECTOR3(0, 1, 0);
			vertex.t = D3DXVECTOR2(0, 0);
			m_vecVertex.push_back(vertex);

			vertex.p = D3DXVECTOR3(j, 0, i + 1);
			vertex.n = D3DXVECTOR3(0, 1, 0);
			vertex.t = D3DXVECTOR2(0, 0);
			m_vecVertex.push_back(vertex);

			vertex.p = D3DXVECTOR3(j + 1, 0, i);
			vertex.n = D3DXVECTOR3(0, 1, 0);
			vertex.t = D3DXVECTOR2(0, 0);
			m_vecVertex.push_back(vertex);

			vertex.p = D3DXVECTOR3(j, 0, i + 1);
			vertex.n = D3DXVECTOR3(0, 1, 0);
			vertex.t = D3DXVECTOR2(0, 0);
			m_vecVertex.push_back(vertex);

			vertex.p = D3DXVECTOR3(j + 1, 0, i + 1);
			vertex.n = D3DXVECTOR3(0, 1, 0);
			vertex.t = D3DXVECTOR2(0, 0);
			m_vecVertex.push_back(vertex);
		}	// : for_i
	}	// : for_j

	// >> index
	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		m_vecDIndex.push_back(i);
	}

	// >> mesh
	m_origMesh = NULL;
	D3DXCreateMeshFVF(m_vecDIndex.size() / 3, m_vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_origMesh);

	ST_PNT_VERTEX* pV = NULL;
	m_origMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_origMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_origMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &m_vecDIndex[0], m_vecDIndex.size() * sizeof(DWORD));
	m_origMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_origMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, (m_vecDIndex.size() / 3) * sizeof(DWORD));
	m_origMesh->UnlockAttributeBuffer();

	vector<DWORD> vecAdj(m_vecDIndex.size());
	m_origMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	m_origMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);

	// >> material
	ZeroMemory(&m_mtrl, sizeof(D3DMATERIAL9));
	m_mtrl.Ambient = D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f);
	m_mtrl.Diffuse = D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f);
	m_mtrl.Specular = D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f);
}

void CGridMap::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// g_pD3DDevice->SetMaterial(&m_mtrl);
	// g_pD3DDevice->SetTexture(0, NULL);

	if (m_nowMesh != NULL)
		m_nowMesh->DrawSubset(0);
	else
		m_origMesh->DrawSubset(0);

	// g_pD3DDevice->SetTexture(0, NULL);
}

void CGridMap::CalcFrustumMap(const vector<bool>& vecCheck)
{
	vector<DWORD> vecIndex;
	for (int i = 0; i < m_vecDIndex.size() - 3; i += 3)
	{
		if (vecCheck[m_vecDIndex[i + 0]] == false && vecCheck[m_vecDIndex[i + 1]] == false && vecCheck[m_vecDIndex[i + 2]] == false)
		{
			continue;
		}

		vecIndex.push_back(m_vecDIndex[i + 0]);
		vecIndex.push_back(m_vecDIndex[i + 1]);
		vecIndex.push_back(m_vecDIndex[i + 2]);

	} // : for

	// int a = 0;
	// a = vecIndex.size();
	// printf("%d\n", a++);

	if (vecIndex.size() == 0)
	{
		// 터짐 방지 코드
		m_nowMesh = NULL;
		return;
	}

	m_nowMesh = NULL;
	D3DXCreateMeshFVF(vecIndex.size() / 3, m_vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_nowMesh);

	ST_PNT_VERTEX* pV = NULL;
	m_nowMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_nowMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_nowMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	m_nowMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_nowMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD)); // 전체 0으로 세팅
	m_nowMesh->UnlockAttributeBuffer();

	vector<DWORD> vecAdj(vecIndex.size());
	m_nowMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	m_nowMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);
}

void CGridMap::ThreadFunc()
{
	if (m_frustum != NULL)
	{
		EnterCriticalSection(&cs);
		vector<bool> vecIsIn;
		int maxSize = m_vecDIndex.size();
		for (int i = 0; i < maxSize; i++)
		{
			if (m_frustum->IsInFrustum(m_vecVertex[i].p))
				vecIsIn.push_back(true);
			else
				vecIsIn.push_back(false);
		}

		CalcFrustumMap(vecIsIn);

		LeaveCriticalSection(&cs);
	}
}

void CGridMap::CalcNewMap(CFrustum frustum)
{
	// DWORD id;
	// HANDLE h;
	//h = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, 0, 0, (unsigned*)&id);

	m_frustum = &frustum;
	// m_thread = thread(&CGridMap::ThreadFunc, this);
	// m_thread.join();
	// thread m_thread2 = thread(&CGridMap::ThreadFunc, this);
	// m_thread2.join();
	// WaitForSingleObject(&thread, INFINITE);

	// >>

	// vector<bool> vecIsIn;
	// int maxSize = m_vecDIndex.size();
	// for (int i = 0; i < maxSize; i++)
	// {
	// 	if (frustum.IsInFrustum(m_vecVertex[i].p))
	// 		vecIsIn.push_back(true);
	// 	else
	// 		vecIsIn.push_back(false);
	// }
	// 
	// CalcFrustumMap(vecIsIn);
}
