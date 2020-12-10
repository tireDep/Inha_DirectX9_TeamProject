#pragma once
#include "Gimmick.h"
class CDoor : public CGimmick
{
private:
	// todo : condition variable

	int GetIndex();

public:
	CDoor();
	~CDoor();

	void Setup(ST_MapData setData);

	void Render();

	void SetAnotherScale(D3DXVECTOR3 set);
	void SetAnotherRotation(D3DXVECTOR3 set);
	void SetAnotherTranslation(D3DXVECTOR3 set);
};

