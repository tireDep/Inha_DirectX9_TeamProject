#pragma once
#include "stdafx.h"
#include "cObject.h"

class cMtlTex : public cObject
{
private :
	Synthesize_Pass_by_Ref(D3DMATERIAL9, m_stMtl, Material);
	Synthesize_Add_Ref(LPDIRECT3DTEXTURE9, m_pTexture, Texture);

	// >> mesh
	Synthesize(int, m_nAttrID, AttrID);

public:
	cMtlTex();
	~cMtlTex();

};