#include "stdafx.h"
#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"
#include "OBB.h"

CSkinnedMesh::CSkinnedMesh() :
	m_pRoot(NULL),
	m_pAniController(NULL),
	m_fBlendTime(0.0f),
	m_fPassedBlendTime(0.03f),
	m_isAniBlend(false),
	m_passedTime(0.0f),
	m_maxPlayTime(0.0f),
	m_pOBB(NULL)
{
}

CSkinnedMesh::~CSkinnedMesh()
{
	CAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SafeRelease(m_pAniController);
	SafeDelete(m_pOBB);
}

void CSkinnedMesh::SetUp(char * szFolder, char * szFile)
{
	string sFullPath = string(szFolder) + string("/") + string(szFile);

	CAllocateHierarchy ah;
	ah.SetFolder(szFolder);

	D3DXLoadMeshHierarchyFromXA(sFullPath.c_str(), 
		D3DXMESH_MANAGED, 
		g_pD3DDevice,
		&ah,
		NULL,
		&m_pRoot,
		&m_pAniController);

	SetUpBoneMatrixPtrs(m_pRoot);

	m_pOBB = new COBB;
	m_pOBB->Setup(ah);
	g_pObjectManager->AddOBBbox(m_pOBB);

	LPD3DXANIMATIONSET pAniSet = NULL;
	m_pAniController->GetAnimationSet(10, &pAniSet);
	SafeRelease(pAniSet);
}

void CSkinnedMesh::Update(float duration)
{
	/// Animation Index
	// 10 idle
	// 9 walk
	// 8 running
	// 7 jump
	// 6 fall
	// 5 push
	// 4 pull
	// 3 changeColor
	// 2 applyColor
	// 1 Sturn
	// 0 Getup

	m_passedTime += duration;

	if (m_maxPlayTime <= m_passedTime + m_fBlendTime && strstr(m_sNowPlayAni.c_str(), "ChangeColor"))
	{
		SetAnimationIndexBlend(2); // ApplyColor
	}
	// else if (m_maxPlayTime <= m_passedTime + m_fBlendTime && strstr(m_sNowPlayAni.c_str(), "Jump"))
	// {
	// 	SetAnimationIndexBlend(6); // fall
	// }
	else if (m_maxPlayTime <= m_passedTime + m_fBlendTime
		&& (strstr(m_sNowPlayAni.c_str(), "ApplyColor") 
		 || strstr(m_sNowPlayAni.c_str(), "Push") 
		 || strstr(m_sNowPlayAni.c_str(), "Pull")
		 || strstr(m_sNowPlayAni.c_str(), "Fall")))
	{
		SetAnimationIndex(10); // Idle
	}
	
	if (m_isAniBlend)
	{
		m_fPassedBlendTime += duration;	// 시간 누적
		if (m_fPassedBlendTime >= m_fBlendTime)
		{
			m_isAniBlend = false;
			m_pAniController->SetTrackWeight(0, 1.0f);
			m_pAniController->SetTrackEnable(1, false); 
			// 같은 의미 : m_pAniController->SetTrackWeight(1, 0.0f);
			// 애니메이션 안함
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAniController->SetTrackWeight(0, fWeight);
			m_pAniController->SetTrackWeight(1, 1.0f - fWeight);
			// 시간이 지나갈 수록 더 가까운 쪽의 애니메이션이 실행됨
		}
	}
	if (m_pAniController)
		m_pAniController->AdvanceTime(duration, NULL);
	
	if (m_pRoot)
	{
		Update(m_pRoot, NULL);
		UpdateSkinnedMesh(m_pRoot);
		Update((ST_BONE*)m_pRoot, &m_matworldTM); // 캐릭터 이동
		m_pOBB->Update(&m_matworldTM);
	}
}

void CSkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;

	if (pParent)
	{
		pBone->CombinedTransformationMatrix *= ((ST_BONE*)pParent)->CombinedTransformationMatrix;
		
		//if (pBone->pMeshContainer->MeshData.pMesh)
		//{
		//	D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);
		//	LPVOID pV = NULL;
		//	pBone->pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pV);

		//	D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
		//		pBone->pMeshContainer->MeshData.pMesh->GetNumVertices(),
		//		D3DXGetFVFVertexSize(pBone->pMeshContainer->MeshData.pMesh->GetFVF()),
		//		&vMin,
		//		&vMax);
		//	D3DXVec3TransformCoord(&m_vMin, &m_vMin, &pBone->CombinedTransformationMatrix);
		//	D3DXVec3TransformCoord(&m_vMax, &m_vMax, &pBone->CombinedTransformationMatrix);
		//	D3DXVec3TransformCoord(&vMin, &vMin, &pBone->CombinedTransformationMatrix);
		//	D3DXVec3TransformCoord(&vMax, &vMax, &pBone->CombinedTransformationMatrix);
		//	D3DXVec3Minimize(&m_vMin, &m_vMin, &vMin);
		//	D3DXVec3Maximize(&m_vMax, &m_vMax, &vMax);

		//	pBone->pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
		//}
		//m_pOBB->Update(&pBone->CombinedTransformationMatrix);
	}

	if (pFrame->pFrameFirstChild)
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}
	
	if (pFrame->pFrameSibling)
	{
		Update(pFrame->pFrameSibling, pParent);
	}
}

void CSkinnedMesh::Update(ST_BONE * pCurrent, D3DXMATRIXA16 * pMatParent)
{
	if (pCurrent == NULL)
		pCurrent = (ST_BONE*)m_pRoot;

	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;

	if (pMatParent)
	{
		pCurrent->CombinedTransformationMatrix =
			pCurrent->CombinedTransformationMatrix * (*pMatParent);
	}

	if (pCurrent->pFrameSibling)
		Update((ST_BONE*)pCurrent->pFrameSibling, pMatParent);

	if (pCurrent->pFrameFirstChild)
		Update((ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombinedTransformationMatrix));
}

void CSkinnedMesh::Render(LPD3DXFRAME pFrame)
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->MeshData.pMesh)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->CombinedTransformationMatrix);

			for (size_t i = 0; i < pBoneMesh->vecMtl.size(); i++)
			{
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}	// : for

		}	// : if

	}	// : if

	if (pFrame->pFrameFirstChild)
		Render(pFrame->pFrameFirstChild); 

	if (pFrame->pFrameSibling)
		Render(pFrame->pFrameSibling);
}

void CSkinnedMesh::SetUpBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	// 각 프레임의 매쉬 콘테이너의 매트릭스 연결
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();

			for (DWORD i = 0; i < dwNumBones; i++)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot, pSkinInfo->GetBoneName(i));
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pBone->CombinedTransformationMatrix);
			}
		}
	}	// : if

	if (pFrame->pFrameFirstChild)
		SetUpBoneMatrixPtrs(pFrame->pFrameFirstChild); 

	if (pFrame->pFrameSibling)
		SetUpBoneMatrixPtrs(pFrame->pFrameSibling);
}

void CSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();

			for (DWORD i = 0; i < dwNumBones; i++)
			{
				pBoneMesh->pCurrentBoneMatrices[i] = pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);
			}
		}	// : if pBoneMesh

		// >> 정점 정보
		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOriginMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

		// 1. 새로 생성. 값 이상함
		//D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);
		//LPVOID pV = NULL;
		//D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
		//	pBoneMesh->MeshData.pMesh->GetNumVertices(),
		//	D3DXGetFVFVertexSize(pBoneMesh->MeshData.pMesh->GetFVF()),
		//	&vMin,
		//	&vMax);
		//// 바운딩 박스의 최소, 최대 구해짐

		//D3DXVec3Minimize(&m_vMin, &m_vMin, &vMin);
		//D3DXVec3Maximize(&m_vMax, &m_vMax, &vMax);

		// 2. 옮기고 비교
		//D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);
		//LPVOID pV = NULL;
		//pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, &pV);
		//D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
		//		pBoneMesh->MeshData.pMesh->GetNumVertices(),
		//		D3DXGetFVFVertexSize(pBoneMesh->MeshData.pMesh->GetFVF()),
		//		&vMin,
		//		&vMax);
		//D3DXVec3TransformCoord(&m_vMin, &m_vMin, pBoneMesh->pCurrentBoneMatrices);
		//D3DXVec3TransformCoord(&m_vMax, &m_vMax, pBoneMesh->pCurrentBoneMatrices);
		//D3DXVec3TransformCoord(&vMin, &vMin, pBoneMesh->pCurrentBoneMatrices);
		//D3DXVec3TransformCoord(&vMax, &vMax, pBoneMesh->pCurrentBoneMatrices);
		//D3DXVec3Minimize(&m_vMin, &m_vMin, &vMin);
		//D3DXVec3Maximize(&m_vMax, &m_vMax, &vMax);
		//pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		
		// 3. OBB 행렬 업데이트
		//m_pOBB->Update(pBoneMesh->pCurrentBoneMatrices);

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOriginMesh->UnlockVertexBuffer();
		// 지형 조작 시, 저장할 경우 이런식으로 처리해도 됨
		// << 정점 정보
	}	// : if pFrame

	if (pFrame->pFrameFirstChild)
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		UpdateSkinnedMesh(pFrame->pFrameSibling);
}

void CSkinnedMesh::SetAnimationIndex(int nIndex)
{
	// 새로운 애니메이션 setting
	int num = m_pAniController->GetNumAnimationSets();

	if (nIndex > num)
		nIndex = nIndex % num;

	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAniController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAniController->SetTrackAnimationSet(0, pAnimSet);
	// m_pAniController->ResetTime();	// 처음부터 실행

	SetNowPlayMaxTime(pAnimSet);
	m_passedTime = 0.0f;

	m_pAniController->GetPriorityBlend();	// 이전 동작과 섞임
}

void CSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	m_isAniBlend = true;
	m_fPassedBlendTime = 0.0f;
	
	int num = m_pAniController->GetNumAnimationSets();
	
	if (nIndex >= num)
		nIndex = nIndex%num;

	LPD3DXANIMATIONSET pPrevAniSet = NULL;
	LPD3DXANIMATIONSET pNextAniSet = NULL;

	D3DXTRACK_DESC stTrackDesc;
	m_pAniController->GetTrackDesc(0, &stTrackDesc);
	m_pAniController->GetTrackAnimationSet(0, &pPrevAniSet);
	m_pAniController->SetTrackAnimationSet(1, pPrevAniSet);
	
	m_pAniController->SetTrackDesc(1, &stTrackDesc);
	m_pAniController->GetAnimationSet(nIndex, &pNextAniSet);
	m_pAniController->SetTrackAnimationSet(0, pNextAniSet);
	m_pAniController->SetTrackPosition(0, 0.0f);

	// >> 가중치
	m_pAniController->SetTrackWeight(0, 0.0f);
	m_pAniController->SetTrackWeight(1, 1.0f);
	// << 가중치
	
	SetNowPlayMaxTime(pNextAniSet);
	m_passedTime = 0.0f;

	SafeRelease(pPrevAniSet);
	SafeRelease(pNextAniSet);
}

void CSkinnedMesh::SetNowPlayMaxTime(LPD3DXANIMATIONSET aniInfo)
{
	m_maxPlayTime = aniInfo->GetPeriod();
	m_sNowPlayAni = aniInfo->GetName();
}

void CSkinnedMesh::SetTransform(D3DXMATRIXA16 * pmat)
{
	m_matworldTM = *pmat;
}

bool CSkinnedMesh::CheckAnimationEnd()
{
	if (strstr(m_sNowPlayAni.c_str(), "Color") 
	|| strstr(m_sNowPlayAni.c_str(), "Jump")
	// || strstr(m_sNowPlayAni.c_str(), "Fall")
	 || strstr(m_sNowPlayAni.c_str(), "Stun")
	// || strstr(m_sNowPlayAni.c_str(), "Push")
	// || strstr(m_sNowPlayAni.c_str(), "Pull")
	 || strstr(m_sNowPlayAni.c_str(), "Getup"))
	{
		// >> 중간에 끊기면 안되는 애니메이션들
		// >> 색상 변경

		if (m_maxPlayTime <= m_passedTime + m_fBlendTime)
			return true;
		else
			return false;
	}

	return true;
}

