#pragma once
class CText
{
private:
	LPD3DXFONT	m_pFont;
public:
	CText();
	~CText();
	void Setup();
	void RenderFPS(int fps);
	void RenderCharacterPosition(D3DXVECTOR3 CharacterPosition);
};