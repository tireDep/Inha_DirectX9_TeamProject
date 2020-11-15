#pragma once
class CText
{
public:
	CText();
	~CText();
private:
	LPD3DXFONT	m_pFont;
public:
	void Setup();
	void RenderFPS(int fps);
	void RenderCharacterPosition(D3DXVECTOR3 CharacterPosition);
	void RenderBoxPosition(D3DXVECTOR3 BoxPosition);
};