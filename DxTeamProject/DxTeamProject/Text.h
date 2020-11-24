#pragma once
class CText
{
public:
	CText();
	~CText();
private:
	LPD3DXFONT	m_pFont;
	Synthesize(bool, m_isGrabState, isGrabstate);
public:
	void Setup();
	void RenderFPS(int fps);
	void RenderCharacterPosition(D3DXVECTOR3 CharacterPosition);
	void RenderBoxPosition(D3DXVECTOR3 BoxPosition);
	//void RenderGrab(vector<CObject*> ObjectPosition, D3DXVECTOR3 PlayerPosition);
	void RenderGrab();
};