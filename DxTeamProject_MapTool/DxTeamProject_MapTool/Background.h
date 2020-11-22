#pragma once
#include "IObject.h"
class CBackground : public IObject
{
protected:
	enum class BackgroundType { eTile, eBackObj };
	
	// >> Iobject?
	ID3DXMesh* m_pMesh;
	D3DMATERIAL9 m_pMtrl;
	LPDIRECT3DTEXTURE9 m_pTexture;

	string m_strName;
	BackgroundType m_BackgroundType;

	D3DXVECTOR3 m_vScale;
	D3DXVECTOR3 m_vRotate;
	D3DXVECTOR3 m_vTranslate;
	// << Iobject?

	// >> todo
	// enum class TriggerType { eNull, eSavePoint, eAnotherStage };
	// TriggerType m_triggerType;
	// bool m_isTrigger;
	// 
	// enum class ColorType { eRed, eOrange, eYellow, eYellowGreen, eGreen, eSkyBlue, eBlue, ePurple };
	// vector<ColorType> m_vecColorType;

	CBackground();

public:
	virtual ~CBackground();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void SetName(string setName) { m_strName = setName; }
};

