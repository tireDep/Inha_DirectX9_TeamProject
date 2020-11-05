#pragma once
#include "stdafx.h"
#include "cObject.h"
#include "cMtlTex.h"

class cGroup : public cObject
{
private:
	Synthesize_Pass_by_Ref(vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	Synthesize_Add_Ref(cMtlTex*, m_pMtlTex, MtlTex);

public:
	cGroup();
	~cGroup();

	void Render();

};