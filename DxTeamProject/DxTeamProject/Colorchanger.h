#pragma once
#include "Gimmick.h"
class COBB;

class Color_changer : public CGimmick
{
public:
	Color_changer();
	~Color_changer();
private:

	 LPD3DXMESH m_pMeshBeam; //�� �޽�.
	

	D3DXMATRIXA16 matWorld , BeamWorld; //��ġ���� , ������
	D3DXMATRIXA16 matS, matT , matR;
	D3DXVECTOR3  m_scale; //�������� , �� ũ�� 

	float angle; //��ġ , �� �ޱ� ����.

	float length; // �� ���� ����.
	
	

	D3DXCOLOR c; 
	D3DXVECTOR3 m_vMin, m_vMax;

	// KT
	float m_fHitLength;
public:
	D3DMATERIAL9 m_stMtl;
	D3DXVECTOR3 m_position;
	COBB *m_BeamOBB;
	void Setup(string folder, string file); // x����
	void Update();
	void Render();

	void Update(float duration) { };

	void SetColor(D3DXCOLOR color);
	
	// KT
	void SetHitLength(float HitLength); // ���� �¾����� �Ÿ� ������.


	//���ͼ�Ʈ
	
};

