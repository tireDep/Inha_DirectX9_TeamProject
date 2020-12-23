#pragma once
class CMap
{
private:
	// Synthesize(POINT, m_nowPosIndex, PosPointIndex);
	static int m_nowMapPos;

public:
	CMap();
	~CMap();

	static void CalcNowPositionIndex(const D3DXVECTOR3& m_characterPos);
	static void SetIsRenderState();
};

