#pragma once

class IObject
{
protected:
	static int m_nRefCnt;

	ID3DXMesh* m_pMesh;
	D3DMATERIAL9 m_pMtrl;
	LPDIRECT3DTEXTURE9 m_pTexture;

	Synthesize(string, m_strObjName, ObjectName);
	Synthesize(string, m_strFilePath, FilePath);
	Synthesize(ObjectType, m_ObjectType, ObjType);

	Synthesize(D3DXVECTOR3, m_vScale, Scale);
	Synthesize(D3DXVECTOR3, m_vRotate, Rotate);
	Synthesize(D3DXVECTOR3, m_vTranslate, Translate);

	Synthesize(bool, m_isClick, Click);

public:
	IObject();
	virtual ~IObject();
	virtual void Release();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

