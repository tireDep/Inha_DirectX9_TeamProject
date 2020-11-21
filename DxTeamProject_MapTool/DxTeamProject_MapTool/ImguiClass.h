#pragma once

class CImguiClass
{
public:
	CImguiClass();
	~CImguiClass();

	void Setup();
	void Update();

	void SetFrameEnd();
	void Render();

	void ResetDevice();
	void Destroy();
};

