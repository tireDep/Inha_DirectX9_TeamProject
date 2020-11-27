#include "stdafx.h"
#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"


CSkinnedMesh::CSkinnedMesh() :
	m_pRoot(NULL),
	m_pAniController(NULL),
	m_fBlendTime(0.3f),
	m_fPassedBlendTime(0.0f),
	m_isAniBlend(false),
	m_passedTime(0.0f),
	m_maxPlayTime(0.0f)
{

}

CSkinnedMesh::~CSkinnedMesh()
{
	CAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SafeRelease(m_pAniController);
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

	LPD3DXANIMATIONSET pAniSet = NULL;
	m_pAniController->GetAnimationSet(3, &pAniSet);
	SetNowPlayMaxTime(pAniSet);
	SafeRelease(pAniSet);
}

void CSkinnedMesh::Update()
{
	m_passedTime += g_pTimeManager->GetElapsedTime();
	if (m_maxPlayTime <= m_passedTime + m_fBlendTime && strstr(m_sNowPlayAni.c_str(), "Attack"))
	{
		// ���� �ð� �߰�
		SetAnimationIndexBlend(4);
	}
	
	if (m_isAniBlend)
	{
		m_fPassedBlendTime += g_pTimeManager->GetElapsedTime();	// �ð� ����
		if (m_fPassedBlendTime >= m_fBlendTime)
		{
			m_isAniBlend = false;
			m_pAniController->SetTrackWeight(0, 1.0f);
			m_pAniController->SetTrackEnable(1, false); 
			// ���� �ǹ� : m_pAniController->SetTrackWeight(1, 0.0f);
			// �ִϸ��̼� ����
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAniController->SetTrackWeight(0, fWeight);
			m_pAniController->SetTrackWeight(1, 1.0f - fWeight);
			// �ð��� ������ ���� �� ����� ���� �ִϸ��̼��� �����
		}
	}

	m_pAniController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
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
			D3DXMatrixScaling(&pBone->CombinedTransformationMatrix, 10, 10, 10);
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
	// �� �������� �Ž� �����̳��� ��Ʈ���� ����
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

		// >> ���� ����
		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOriginMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOriginMesh->UnlockVertexBuffer();
		// ���� ���� ��, ������ ��� �̷������� ó���ص� ��
		// << ���� ����
	}	// : if pFrame

	if (pFrame->pFrameFirstChild)
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		UpdateSkinnedMesh(pFrame->pFrameSibling);
}

void CSkinnedMesh::SetAnimationIndex(int nIndex)
{
	// ���ο� �ִϸ��̼� setting
	int num = m_pAniController->GetNumAnimationSets();

	if (nIndex > num)
		nIndex = nIndex % num;

	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAniController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAniController->SetTrackAnimationSet(0, pAnimSet);
	// m_pAniController->ResetTime();	// ó������ ����

	m_pAniController->GetPriorityBlend();	// ���� ���۰� ����
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

	// >> ����ġ
	m_pAniController->SetTrackWeight(0, 0.0f);
	m_pAniController->SetTrackWeight(1, 1.0f);
	// << ����ġ

	SetNowPlayMaxTime(pNextAniSet);
	m_passedTime = 0.0f;

	SafeRelease(pPrevAniSet);
	SafeRelease(pNextAniSet);
}

void CSkinnedMesh::SetNowPlayMaxTime(LPD3DXANIMATIONSET aniInfo)
{
//	m_maxPlayTime = aniInfo->GetPeriod();
//	m_sNowPlayAni = aniInfo->GetName();
}

