#include "stdafx.h"
#include "RotationBoard.h"

RotationBoard::RotationBoard()
	: m_pMesh(NULL)
	, m_adjBuffer(NULL)
	, m_numMtrls(0)
	//, rotationAxial(RotationAxial::NONE)
	// Test
	, rotationAxial(RotationAxial::Rotation_Y)
	, m_fRotationSpeed(0.1)
	, m_fRot(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRotGimmick);
}

RotationBoard::~RotationBoard()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_adjBuffer);
}

void RotationBoard::Setup(string folder, string file)
{
	ST_XFile* xfile = new ST_XFile;

	if (!g_pFileLoadManager->FileLoad_XFile(folder, file, xfile))
	{
		MessageBox(g_hWnd, L"LoadXFile Fail", L"Error", MB_OK);
		return;
	}

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	delete xfile;
}

void RotationBoard::Update(float duration)
{
	switch (rotationAxial)
	{
	case RotationAxial::Rotation_X:
		m_fRot += m_fRotationSpeed * duration;
		D3DXMatrixRotationX(&m_matRotGimmick, m_fRot);
		break;
	case RotationAxial::Rotation_Y:
		m_fRot += m_fRotationSpeed * duration;
		D3DXMatrixRotationY(&m_matRotGimmick, m_fRot);
		break;
	case RotationAxial::Rotation_Z:
		m_fRot += m_fRotationSpeed * duration;
		D3DXMatrixRotationZ(&m_matRotGimmick, m_fRot);
		break;
	case RotationAxial::NONE:
		D3DXMatrixIdentity(&m_matRotGimmick);
		break;
	default:
		break;
	}
}

void RotationBoard::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		//D3DXMATRIXA16 matWorld;
		//D3DXMatrixIdentity(&matWorld);

		//D3DXMATRIXA16 matS, matT;
		//D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
		//D3DXMatrixTranslation(&matT, -25, 0, 0);
		//matWorld = matS * matT;

		// Test
		m_matWorld = m_matRotGimmick;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		if (m_pMesh == NULL)
			return;
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			g_pD3DDevice->SetMaterial(m_vecMtrls[i]);
		}
		m_pMesh->DrawSubset(0);
		g_pD3DDevice->SetTexture(0, NULL);
	}
}