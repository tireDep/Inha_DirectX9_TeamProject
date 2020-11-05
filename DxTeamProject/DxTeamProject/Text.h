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
	void Render(int fps);
};