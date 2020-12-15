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

	D3DXMATRIXA16  BeamWorld; //��ġ���� , ������
	D3DXMATRIXA16 matS, matT , matR;  // ��
	D3DXVECTOR3  m_scale; //�������� , �� ũ�� 

	float angle; //��ġ , �� �ޱ� ����.

	float length; // �� ���� ����.

	D3DXCOLOR c; 
	D3DXVECTOR3 m_vMin, m_vMax;
	bool pObject, player;
	// KT
	float m_fHitLength;
	// D3DXMATRIXA16 m_matS, m_matR, m_matT;  //�� ������
public:
	D3DMATERIAL9 m_stMtl;
	D3DXVECTOR3 m_position;
	COBB *m_BeamOBB;
	
	void Setup(); // x����
	void Setup(ST_MapData setData);

	void Update();
	void Render();

	void Update(float duration) { };

	void SetColor(D3DXCOLOR color);
	
	void pOjbectBool(bool set) { pObject = set; }
	void SetBool(bool set) { player = set; }

	// KT
	void SetHitLength(float HitLength); // ���� �¾����� �Ÿ� ������.


	//���ͼ�Ʈ
	
};

