#pragma once
#include "IListener.h"

class CCharacter;

class CDragon : public IListener
{
private:
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	LPDIRECT3DTEXTURE9 m_pTexture;
	ST_XFile* xfile = new ST_XFile;

	// >> testRotationMove
	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3 m_vDrangonPos;

	D3DXVECTOR3 m_vDirection;
	D3DXMATRIXA16 m_matRotY;

	bool m_isTrue;
	float Drangon_y;

	float rotation;
	// << testRotationMove

	bool m_isEffect;
	float m_effectDuration;
	D3DXCOLOR m_color;

public:
	CDragon();
	virtual ~CDragon(void);
	virtual void Update(D3DXVECTOR3 pos, float duration);
	virtual void Setup();
	virtual void Render();
	virtual void ChangeColor(D3DXCOLOR color);
	virtual void DoRotation();
	virtual void DirectionSet(D3DXVECTOR3 cameradirection);

	void ReceiveEvent(ST_EVENT eventMsg) override;
	virtual string GetName();
};

