#pragma once

#include "Gimmick.h"

class COBB;

class MovingCube : public CGimmick
{
public:
	MovingCube();
	~MovingCube();

private:
	

	int IndexNum; // ��ȣ.
	bool istrue; //���� ���� ��ġ
	float speed; //�ӵ�
	float startpos , endpos; // �Ÿ� ?
	D3DXVECTOR3 m_vPosition;

	

	//D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matS, matT, matR;
	D3DXVECTOR3 m_vMin, m_vMax;
public:
	void Setup(string folder, string file);
	void Update(float duration) { };
	void Update();

	void Render();


	
};

