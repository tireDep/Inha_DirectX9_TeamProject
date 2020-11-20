#pragma once
class CPhysicsSphere;

class CWall
{
private:
	float					m_x;
	float					m_z;
	float                   m_width;
	float                   m_depth;
	float					m_height;
	D3DXMATRIXA16	m_matWorld;

public:
	CWall(void);
	~CWall(void) {}
public:
	void Setup(float iwidth, float iheight, float idepth);
	void destroy(void);
	void draw();


	bool hasIntersected(CPhysicsSphere& ball);

	void hitBy(CPhysicsSphere& ball);
	
	void setPosition(float x, float y, float z);

	float getHeight(void) const { return 0.01; }



private:
	void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }

	D3DXMATRIX              m_mLocal;
	D3DMATERIAL9            m_mtrl;
	ID3DXMesh*              m_pBoundMesh;
};

