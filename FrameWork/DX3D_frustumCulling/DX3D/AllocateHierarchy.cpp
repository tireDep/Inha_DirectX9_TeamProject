#include "stdafx.h"
#include "AllocateHierarchy.h"


CAllocateHierarchy::CAllocateHierarchy() :
	m_vMax(0,0,0),
	m_vMin(0,0,0)
{
}


CAllocateHierarchy::~CAllocateHierarchy()
{
}

STDMETHODIMP CAllocateHierarchy::CreateFrame(THIS_ LPCSTR Name, LPD3DXFRAME* ppNewFrame)
{
	ST_BONE* pBone = new ST_BONE;
	ZeroMemory(pBone, sizeof(ST_BONE));

	if (Name)
	{
		pBone->Name = new char[lstrlenA(Name) + 1];
		UINT length = lstrlenA(Name) + 1;
		strcpy_s(pBone->Name, length * sizeof(CHAR), Name);
	}	// : if

	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	D3DXMatrixIdentity(&pBone->CombinedTransformationMatrix);

	*ppNewFrame = pBone;

	return S_OK; // return false가 존재하지 x
}

STDMETHODIMP CAllocateHierarchy::CreateMeshContainer(THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;
	ZeroMemory(pBoneMesh, sizeof(ST_BONE_MESH));

	// >> material & texture
	for (DWORD i = 0; i < NumMaterials; i++)
	{
		pBoneMesh->vecMtl.push_back(pMaterials[i].MatD3D);
		string sFullPath = m_sFolder;
		sFullPath = string(sFullPath) + string("/") + string(pMaterials[i].pTextureFilename);

		pBoneMesh->vecTexture.push_back(g_pTextureManager->GetTexture(sFullPath));
	}	// : for
	// << material & texture

	pSkinInfo->AddRef();
	pBoneMesh->pSkinInfo = pSkinInfo;

	pMeshData->pMesh->AddRef();
	pBoneMesh->MeshData.pMesh = pMeshData->pMesh;

	// >> Bounding Box
	if (pMeshData && pMeshData->pMesh)
	{
		D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);
		LPVOID pV = NULL;
		pMeshData->pMesh->LockVertexBuffer(0, &pV);

		D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
			pMeshData->pMesh->GetNumVertices(), 
			D3DXGetFVFVertexSize(pMeshData->pMesh->GetFVF()), 
			&vMin, 
			&vMax);
		// 바운딩 박스의 최소, 최대 구해짐

		D3DXVec3Minimize(&m_vMin, &m_vMin, &vMin);
		D3DXVec3Maximize(&m_vMax, &m_vMax, &vMax);
		// 비교해서 작은 값, 큰 값 저장

		pMeshData->pMesh->UnlockVertexBuffer();
	}
	// << Bounding Box

	pMeshData->pMesh->CloneMeshFVF(
		pMeshData->pMesh->GetOptions(),
		pMeshData->pMesh->GetFVF(),
		g_pD3DDevice,
		&pBoneMesh->pOriginMesh
	);

	// >> 뼈 숫자
	DWORD dwNumBones = pSkinInfo->GetNumBones();
	pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[dwNumBones];
	pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[dwNumBones];
	pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[dwNumBones];

	for (DWORD i = 0; i < dwNumBones; i++)
	{
		pBoneMesh->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
	}
	// << 뼈 숫자

	*ppNewMeshContainer = pBoneMesh;

	return S_OK;
}

STDMETHODIMP CAllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	ST_BONE* pBone = (ST_BONE*)pFrameToFree;
	SafeDeleteArray(pBone->Name);
	SafeDelete(pFrameToFree);

	return S_OK;
}

STDMETHODIMP CAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;
	
	SafeRelease(pBoneMesh->pSkinInfo);
	SafeRelease(pBoneMesh->MeshData.pMesh);
	SafeRelease(pBoneMesh->pOriginMesh);

	SafeDeleteArray(pBoneMesh->pCurrentBoneMatrices);
	SafeDeleteArray(pBoneMesh->ppBoneMatrixPtrs);
	SafeDeleteArray(pBoneMesh->pBoneOffsetMatrices);

	SafeDelete(pBoneMesh);

	return S_OK;
}
