#include "stdafx.h"
#include "cMtlTex.h"

cMtlTex::cMtlTex() 
	: m_pTexture(NULL)
	, m_nAttrID(NULL)
{
	ZeroMemory(&m_stMtl,sizeof(D3DMATERIAL9));
}

cMtlTex::~cMtlTex()
{
	SafeRelease(m_pTexture)
}
