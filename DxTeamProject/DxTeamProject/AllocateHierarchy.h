#pragma once
#include "d3dx9anim.h"

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	vector<D3DMATERIAL9> vecMtl;
	vector<LPDIRECT3DTEXTURE9> vecTexture;

	LPD3DXMESH		pOriginMesh;
	D3DXMATRIX**	ppBoneMatrixPtrs;		// 각 본에 영향 미치는 포인터 배열
	D3DXMATRIX*		pBoneOffsetMatrices;	// 원본 매트릭스 -> 로컬
	D3DXMATRIX*		pCurrentBoneMatrices;
};
class CAllocateHierarchy : public ID3DXAllocateHierarchy
{
protected:
	Synthesize(string, m_sFolder, Folder);
	Synthesize(D3DXVECTOR3, m_vMin, Min);
	Synthesize(D3DXVECTOR3, m_vMax, Max);

public:
	CAllocateHierarchy();
	~CAllocateHierarchy();

	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME* ppNewFrame) override;

	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override;
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;

};

