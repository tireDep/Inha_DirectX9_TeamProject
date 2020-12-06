#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "stdafx.h"
#include "IObject.h"

#include "Gimmick.h"
#include "RotationBoard.h"

#include "ImguiClass.h"

int CImguiClass::m_nowSelectindex = -1;
int CImguiClass::m_prevSelectIndex = 0;

void CImguiClass::SetVecItem()
{
	vector<string> tempVec;
	vector<ObjectType> tempObjType;
	if (m_NowLoadType == LoadType::eMap)
	{
		tempVec.push_back("Tile01"); tempObjType.push_back(eTile01);
		tempVec.push_back("Tile02"); tempObjType.push_back(eTile02);
		tempVec.push_back("Tile03"); tempObjType.push_back(eTile03);
		tempVec.push_back("Tile04"); tempObjType.push_back(eTile04);
		tempVec.push_back("Tile05"); tempObjType.push_back(eTile05);
		tempVec.push_back("Tile06"); tempObjType.push_back(eTile06);
		tempVec.push_back("Tile07"); tempObjType.push_back(eTile07);
		tempVec.push_back("Tile08"); tempObjType.push_back(eTile08);
		tempVec.push_back("Tile09"); tempObjType.push_back(eTile09);
		tempVec.push_back("Tile10"); tempObjType.push_back(eTile10);
		tempVec.push_back("Tile11"); tempObjType.push_back(eTile11);
		tempVec.push_back("Tile12"); tempObjType.push_back(eTile12);
		tempVec.push_back("Tile13"); tempObjType.push_back(eTile13);
	}
	else if (m_NowLoadType == LoadType::eObject)
	{
		tempVec.push_back("Box");			tempObjType.push_back(eBox);
		tempVec.push_back("Sphere");		tempObjType.push_back(eSphere);
		tempVec.push_back("Cylinder");		tempObjType.push_back(eCylinder);
	}
	else if (m_NowLoadType == LoadType::eBackground)
	{
		tempVec.push_back("Tree01");
		tempVec.push_back("Tree02");
		tempVec.push_back("Tree03");
		tempVec.push_back("Tree04");
		tempVec.push_back("Tree05");
		tempVec.push_back("Tree06");

		if (m_SubType == LoadType::eAutumnTree)
		{
			for (int i = 0; i < tempVec.size(); i++)
				tempObjType.push_back(eATree);
		}
		else if (m_SubType == LoadType::eSummerTree)
		{
			for (int i = 0; i < tempVec.size(); i++)
				tempObjType.push_back(eSTree);
		}
		else if (m_SubType == LoadType::eWinterTree)
		{
			for (int i = 0; i < tempVec.size(); i++)
				tempObjType.push_back(eWTree);
		}
#ifdef _DEBUG
		else if (m_SubType == LoadType::eInvisibleWall)
		{
			tempVec.clear();
			tempVec.push_back("InvisibleWall"); tempObjType.push_back(eInvisibleWall);
		}
#endif // _DEBUG

	}
	else if (m_NowLoadType == LoadType::eGimmick)
	{
		tempVec.push_back("RotationBoard");		tempObjType.push_back(eG_RotationBoard);
		tempVec.push_back("BreakWall");			tempObjType.push_back(eG_BreakWall);
		tempVec.push_back("Door");				tempObjType.push_back(eG_Door);
		tempVec.push_back("ColorChanger");		tempObjType.push_back(eG_ColorChanger);
		tempVec.push_back("Switch");			tempObjType.push_back(eG_Switch);
	}
	
	m_vecItem = tempVec;
	m_vecObjType = tempObjType;
}

void CImguiClass::SetObjectColor()
{
	{
		ImGui::Text("Set Color");
		string charName[8] = { "Gray", "Black", "White", "Red", "Blue", "Green", "Yellow" };
		for (int i = 0; i < m_vecColor.size(); i++)
		{
			if (ImGui::RadioButton(charName[i].c_str(), m_NowcolorType == m_vecColor[i]))
			{
				m_NowcolorType = m_vecColor[i];

				D3DXCOLOR color;
				switch (m_NowcolorType)
				{
				case ColorType::eGray:
					color = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					break;
				case ColorType::eBlack:
					color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					break;
				case ColorType::eWhite:
					color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					break;
				case ColorType::eRed:
					color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					break;
				case ColorType::eBlue:
					color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
					break;
				case ColorType::eGreen:
					color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
					break;
				case ColorType::eYellow:
					color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
					break;
				}
				g_pObjectManager->GetIObject(m_nowSelectindex).SetColor(color);
			}

			if (i != 2 && i != m_vecColor.size() - 1)
				ImGui::SameLine();

		} // << : for
		ImGui::Separator();
	} // << : if
}

CImguiClass::CImguiClass() :
	m_isReset(false),
	m_FileLoadIndex(-1),
	m_showItem("\0")
{
 	m_PreLoadType = LoadType::eNull;
 	m_NowLoadType = LoadType::eMap;

	m_PrecolorType = ColorType::eNull;
	m_NowcolorType = ColorType::eGray;

	m_SubType = LoadType::eAutumnTree;
	
	m_vecColor.push_back(ColorType::eGray);
	m_vecColor.push_back(ColorType::eBlack);
	m_vecColor.push_back(ColorType::eWhite);
	m_vecColor.push_back(ColorType::eRed);
	m_vecColor.push_back(ColorType::eBlue);
	m_vecColor.push_back(ColorType::eGreen);
	m_vecColor.push_back(ColorType::eYellow);
}

CImguiClass::~CImguiClass()
{
}

void CImguiClass::Setup()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(g_pD3DDevice);
}

void CImguiClass::Update()
{
// Our state
// 	static bool show_demo_window = true;
// 	static bool show_another_window = false;
// 	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

#ifdef _DEBUG
//	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
//	if (show_demo_window)
//		ImGui::ShowDemoWindow(&show_demo_window);
//
//	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
//	{
//		static float f = 0.0f;
//		static int counter = 0;
//
//		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//		ImGui::Checkbox("Another Window", &show_another_window);
//
//		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//
//		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//			counter++;
//		ImGui::SameLine();
//		ImGui::Text("counter = %d", counter);
//
//		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//		ImGui::End();
//	}
//
//	// 3. Show another simple window.
//	if (show_another_window)
//	{
//		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//		ImGui::Text("Hello from another window!");
//		if (ImGui::Button("Close Me"))
//			show_another_window = false;
//		ImGui::End();
//	}
//
	// ============================================================================================
	
	g_pObjectManager->CheckSameName();

	Update_MenuTitleBar();
	Update_Hiearachy();
	Update_FileLoader();
	Update_Inspector();

	{ // >> : Controller
		// >> 렉걸려서 주석처리
		// static LPDIRECT3DTEXTURE9 temp;
		// D3DXCreateTextureFromFileA(g_pD3DDevice, "Resource/Test.png", &temp);
		// static ImTextureID test = temp;

		// ImGui::Begin(" ");

		/*for (int i = 0; i < 5 ; i++)
		{
			ImGui::PushID(i);
			int frame_padding = 2;
			ImVec2 size = ImVec2(32.0f, 32.0f);
			ImVec2 uv0 = ImVec2(0.0f, 0.0f);
			ImVec2 uv1 = ImVec2(32.0f / 32, 32.0f / 32);
			ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

			if (ImGui::ImageButton(test, size, uv0, uv1, frame_padding, bg_col, tint_col))
			{
				if (i == 0) cout << "Mouse Move Mode" << endl;
				else if (i == 1) cout << "Object Move Mode" << endl;
				else if (i == 2) cout << "Object Rotate Mode" << endl;
				else if (i == 3) cout << "Object Scale Mode" << endl;
				else if (i == 4) cout << "Object OBB Mode" << endl;
			}
			
			ImGui::SameLine();
			ImGui::PopID();
		}*/
		// ImGui::End();
	} // << : Controller

#else
	g_pObjectManager->CheckSameName();
	
	{ // >> : Menu Title Bar
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open", " ")) { g_pFileLoadManager->FileLoad_OpenMapData(); }
				if (ImGui::MenuItem("Save", " ")) { g_pFileLoadManager->FileLoad_SaveMapData(); }
	
				ImGui::Separator();
	
				if (ImGui::MenuItem("Reset", " "))
					m_isReset = true;
	
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	
		if (m_isReset)
		{
			ImGui::Begin("ResetWindow", &m_isReset);
			ImGui::Text("Reset?");
	
			if (ImGui::Button("Yes"))
			{
				g_pObjectManager->Destroy();
				m_isReset = false;
			}
	
			ImGui::SameLine();
			if (ImGui::Button("No"))
				m_isReset = false;
	
			ImGui::End();
		}
	
	} // << : Menu Title Bar
	
	{
		ImGui::Begin("Hiearachy");
	
		vector<IObject *> vecObj = g_pObjectManager->GetVecObject();
		bool isClick = false;
		int checkIndex = -1;
		int vecSize = g_pObjectManager->GetVecObject().size();
		if (vecSize > 0)
		{
			for (int i = 0; i < vecObj.size(); i++)
			{
				if (vecObj[i]->GetPick())
				{
					checkIndex = i;
					break;
					// todo : ray 판정 수정
					// 같은 라인의 맨 앞에 저장 된 것이 선택 됨
				}
			} // << : check pick object
	
			if (checkIndex == -1)
			{
				for (int i = 0; i < vecObj.size(); i++)
				{
					isClick = vecObj[i]->GetClick();
					if (ImGui::Selectable(vecObj[i]->GetObjectName().c_str(), &isClick))
					{
						CImguiClass::m_nowSelectindex = i;
						vecObj[i]->SetClick(isClick);
						vecObj[i]->SetPick(true);
					}
				}
	
			} // << : if_pick not exist
			else
			{
				for (int i = 0; i < vecObj.size(); i++)
				{
					if (i == checkIndex)
					{
						CImguiClass::m_nowSelectindex = i;
						ImGui::Selectable(vecObj[i]->GetObjectName().c_str(), true);
						vecObj[i]->SetClick(true);
						vecObj[i]->SetPick(true);
					}
					else
						ImGui::Selectable(vecObj[i]->GetObjectName().c_str(), false);
				} // << : for
	
			} // << : else_Pick exist
	
			for (int i = 0; i < vecObj.size(); i++)
			{
				if (i != CImguiClass::m_nowSelectindex)
				{
					vecObj[i]->SetClick(false);
					vecObj[i]->SetPick(false);
				}
			} // << : for
	
		} // << : if_objectVector size is not zero
	
	
		  // >> todo : 오브젝트 정렬 필요?(이름순)
		ImGui::End();
	}
	
	
	{ // >> : FileLoad
		ImGui::Begin("File Loader");
	
		if (ImGui::RadioButton("MapTile", m_NowLoadType == LoadType::eMap)) { m_NowLoadType = LoadType::eMap; m_FileLoadIndex = -1; }
		ImGui::SameLine(); if (ImGui::RadioButton("Object", m_NowLoadType == LoadType::eObject)) { m_NowLoadType = LoadType::eObject; m_FileLoadIndex = -1; }
	
		if (ImGui::RadioButton("Background", m_NowLoadType == LoadType::eBackground)) { m_NowLoadType = LoadType::eBackground; m_FileLoadIndex = -1; }

#ifdef _DEBUG
		ImGui::SameLine();  if (ImGui::RadioButton("Gimmik", m_NowLoadType == LoadType::eGimmik)) { m_NowLoadType = LoadType::eGimmik; m_FileLoadIndex = -1; }
#endif // _DEBUG
	
		// if (ImGui::RadioButton("Item", m_NowLoadType == LoadType::eItem)) { m_NowLoadType = LoadType::eItem; m_FileLoadIndex = -1; }
		// ImGui::SameLine();  if (ImGui::RadioButton("EventTrigger", m_NowLoadType == LoadType::eTrigger)) { m_NowLoadType = LoadType::eTrigger; m_FileLoadIndex = -1; }
		// >> todo
	
		ImGui::Separator();
	
		if (m_NowLoadType != m_PreLoadType && m_NowLoadType != LoadType::eBackground)
		{
			SetVecItem();
			m_PreLoadType = m_NowLoadType;
		}
		else if (m_NowLoadType == LoadType::eBackground)
		{
			// >> 배경 나무들은 세부 선택 존재
			if (ImGui::RadioButton("AutumnTree", m_SubType == LoadType::eAutumnTree)) { m_SubType = LoadType::eAutumnTree; m_FileLoadIndex = -1; }
			ImGui::SameLine(); if (ImGui::RadioButton("SummerTree", m_SubType == LoadType::eSummerTree)) { m_SubType = LoadType::eSummerTree; m_FileLoadIndex = -1; }
	
			if (ImGui::RadioButton("WinterTree", m_SubType == LoadType::eWinterTree)) { m_SubType = LoadType::eWinterTree; m_FileLoadIndex = -1; }
#ifdef _DEBUG
			ImGui::SameLine(); if (ImGui::RadioButton("InvisibleWall", m_SubType == LoadType::eInvisibleWall)) { m_SubType = LoadType::eInvisibleWall; m_FileLoadIndex = -1; }
			// >> 구 버전 클라에서 box로 인식됨
#endif
	
			SetVecItem();
			m_PreLoadType = m_NowLoadType;
		}
	
		// << combo
		if (m_FileLoadIndex == -1)
			m_showItem = " ";
		else
			m_showItem = m_vecItem[m_FileLoadIndex].c_str();
	
		if (ImGui::BeginCombo(" ", m_showItem.c_str()))
		{
			for (int n = 0; n < m_vecItem.size(); n++)
			{
				const bool is_selected = (m_FileLoadIndex == n);
				if (ImGui::Selectable(m_vecItem[n].c_str(), is_selected))
					m_FileLoadIndex = n;
	
				if (is_selected)
					ImGui::SetItemDefaultFocus(); // focus
			}
			ImGui::EndCombo();
		}
		// << combo
	
		ImGui::SameLine();
		if (ImGui::Button("Load") && m_FileLoadIndex != -1)
		{
			IObject::CreateObject(m_vecObjType[m_FileLoadIndex], m_FileLoadIndex);
		}
	
		ImGui::Separator();
	
		ImGui::End();
	} // << : FileLoad
	
	{
		ImGui::Begin("Inspector");
	
		bool isCheck = false;
		int vecSize = g_pObjectManager->GetVecSize();
		for (int i = 0; i < vecSize; i++)
		{
			if (g_pObjectManager->GetIObject(i).GetClick() || g_pObjectManager->GetIObject(i).GetPick())
				isCheck = true;
		}
		// >> : 선택된 것이 없으면 인스펙터 창 뜨지 않음
	
		if (m_prevSelectIndex == m_nowSelectindex && isCheck)
		{
			if (m_nowSelectindex >= 0)
			{
				char name[1024] = "\0";
				int strLength = g_pObjectManager->GetIObject(m_nowSelectindex).GetObjectName().length();
				for (int i = 0; i < strLength; i++)
				{
					name[i] = g_pObjectManager->GetIObject(m_nowSelectindex).GetObjectName()[i];
				}
				name[strLength] = '\0';
	
				bool isCheck = false;
				if (ImGui::InputText("Name", name, 1024))
					isCheck = true;
	
				if (isCheck)
				{
					bool isSame = false;
					int vecSize = g_pObjectManager->GetVecSize();
					for (int i = 0; i < vecSize; i++)
					{
						if (strcmp(g_pObjectManager->GetIObject(i).GetObjectName().c_str(), name) == 0)
							isSame = true;
					}
	
					if (!isSame) g_pObjectManager->GetIObject(m_nowSelectindex).SetObjectName(name);
				}
	
				ImGui::Separator();
	
				D3DXVECTOR3 vScale = g_pObjectManager->GetIObject(m_nowSelectindex).GetScale();
				if (ImGui::InputFloat3("Scale", vScale))
				{
					if (g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eSphere
						|| g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eCylinder)
						g_pObjectManager->GetIObject(m_nowSelectindex).SetDiffScale(vScale);
					else
						g_pObjectManager->GetIObject(m_nowSelectindex).SetScale(vScale);
				}
	
				D3DXVECTOR3 vRot = g_pObjectManager->GetIObject(m_nowSelectindex).GetRotate();
				if (ImGui::InputFloat3("Rotate", vRot))
					g_pObjectManager->GetIObject(m_nowSelectindex).SetRotate(vRot);
	
				D3DXVECTOR3 vTrans = g_pObjectManager->GetIObject(m_nowSelectindex).GetTranslate();
				if (ImGui::InputFloat3("Translate", vTrans))
					g_pObjectManager->GetIObject(m_nowSelectindex).SetTranslate(vTrans);
	
				ImGui::Separator();
	
				// >> object만 색 지정 가능
				if (g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eBox
					|| g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eSphere
					|| g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eCylinder)
				{
					ImGui::Text("Set Color");
					string charName[8] = { "Gray", "Black", "White", "Red", "Blue", "Green", "Yellow" };
					for (int i = 0; i < m_vecColor.size(); i++)
					{
						if (ImGui::RadioButton(charName[i].c_str(), m_NowcolorType == m_vecColor[i]))
						{
							m_NowcolorType = m_vecColor[i];
	
							D3DXCOLOR color;
							switch (m_NowcolorType)
							{
							case ColorType::eGray:
								color = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
								break;
							case ColorType::eBlack:
								color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
								break;
							case ColorType::eWhite:
								color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
								break;
							case ColorType::eRed:
								color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
								break;
							case ColorType::eBlue:
								color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
								break;
							case ColorType::eGreen:
								color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
								break;
							case ColorType::eYellow:
								color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
								break;
							}
							g_pObjectManager->GetIObject(m_nowSelectindex).SetColor(color);
						}
	
						if (i != 2 && i != m_vecColor.size() - 1)
							ImGui::SameLine();
	
					} // << : for
					ImGui::Separator();
				} // << : if
	
			} // << : if (m_nowSelectindex >= 0)
	
		} // << : if (m_prevSelectIndex == m_nowSelectindex)
		else
		{
			m_prevSelectIndex = m_nowSelectindex;
			if (g_pObjectManager->GetVecSize() != 0 && m_nowSelectindex >= 0)
			{
				D3DXCOLOR temp = g_pObjectManager->GetIObject(CImguiClass::m_nowSelectindex).GetColor();
	
				if (temp == D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))		m_NowcolorType = ColorType::eGray;
				else if (temp == D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)) m_NowcolorType = ColorType::eBlack;
				else if (temp == D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)) m_NowcolorType = ColorType::eWhite;
				else if (temp == D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)) m_NowcolorType = ColorType::eRed;
				else if (temp == D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)) m_NowcolorType = ColorType::eGreen;
				else if (temp == D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)) m_NowcolorType = ColorType::eBlue;
				else if (temp == D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)) m_NowcolorType = ColorType::eYellow;
			}
			//else
			//	m_NowcolorType = ColorType::eGray;
		}
	
		ImGui::End();
	
		//if
	}
#endif // _DEBUG
}

void CImguiClass::Update_MenuTitleBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", " ")) { g_pFileLoadManager->FileLoad_OpenMapData(); }
			if (ImGui::MenuItem("Save", " ")) { g_pFileLoadManager->FileLoad_SaveMapData(); }

			ImGui::Separator();

			if (ImGui::MenuItem("Reset", " "))
				m_isReset = true;

			ImGui::EndMenu();
		}

		//if (ImGui::BeginMenu("Edit"))
		//{
		//	// if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
		//	// if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}
		//	// ImGui::Separator();
		//	// if (ImGui::MenuItem("Cut", "CTRL+X")) {}
		//	// if (ImGui::MenuItem("Copy", "CTRL+C")) {}
		//	// if (ImGui::MenuItem("Paste", "CTRL+V")) {}
		//	ImGui::EndMenu();
		//}

		ImGui::EndMainMenuBar();
	}

	if (m_isReset)
	{
		ImGui::Begin("ResetWindow", &m_isReset);
		ImGui::Text("Reset?");

		if (ImGui::Button("Yes"))
		{
			g_pObjectManager->Destroy();
			m_isReset = false;
		}

		ImGui::SameLine();
		if (ImGui::Button("No"))
			m_isReset = false;

		ImGui::End();
	}
}

void CImguiClass::Update_Hiearachy()
{
	ImGui::Begin("Hiearachy");

	vector<IObject *> vecObj = g_pObjectManager->GetVecObject();
	bool isClick = false;
	int checkIndex = -1;
	int vecSize = g_pObjectManager->GetVecObject().size();
	if (vecSize > 0)
	{
		for (int i = 0; i < vecObj.size(); i++)
		{
			if (vecObj[i]->GetPick())
			{
				checkIndex = i;
				break;
			}
		} // << : check pick object

		if (checkIndex == -1)
		{
			// >> 피킹 된 오브젝트가 없을 경우
			for (int i = 0; i < vecObj.size(); i++)
			{
				isClick = vecObj[i]->GetClick();
				if (ImGui::Selectable(vecObj[i]->GetObjectName().c_str(), &isClick))
				{
					CImguiClass::m_nowSelectindex = i;
					vecObj[i]->SetClick(isClick);
					vecObj[i]->SetPick(true);
				}
			}

		} // << : if_pick not exist
		else
		{
			// >> 피킹 된 오브젝트가 존재
			for (int i = 0; i < vecObj.size(); i++)
			{
				if (i == checkIndex)
				{
					CImguiClass::m_nowSelectindex = i;
					ImGui::Selectable(vecObj[i]->GetObjectName().c_str(), true);
					vecObj[i]->SetClick(true);
					vecObj[i]->SetPick(true);
				}
				else
					ImGui::Selectable(vecObj[i]->GetObjectName().c_str(), false);
			} // << : for

		} // << : else_Pick exist

		for (int i = 0; i < vecObj.size(); i++)
		{
			// >> 피킹&선택된 오브젝트 제외 선택 해제
			if (i != CImguiClass::m_nowSelectindex)
			{
				vecObj[i]->SetClick(false);
				vecObj[i]->SetPick(false);
			}
		} // << : for

	} // << : if_objectVector size is not zero


	// >> todo : 오브젝트 정렬 필요?(이름순)
	ImGui::End();
}

void CImguiClass::Update_FileLoader()
{
	ImGui::Begin("File Loader");

	if (ImGui::RadioButton("MapTile", m_NowLoadType == LoadType::eMap)) { m_NowLoadType = LoadType::eMap; m_FileLoadIndex = -1; }
	ImGui::SameLine(); if (ImGui::RadioButton("Object", m_NowLoadType == LoadType::eObject)) { m_NowLoadType = LoadType::eObject; m_FileLoadIndex = -1; }

	if (ImGui::RadioButton("Background", m_NowLoadType == LoadType::eBackground)) { m_NowLoadType = LoadType::eBackground; m_FileLoadIndex = -1; }
	ImGui::SameLine();  if (ImGui::RadioButton("Gimmick", m_NowLoadType == LoadType::eGimmick)) { m_NowLoadType = LoadType::eGimmick; m_FileLoadIndex = -1; }

	// if (ImGui::RadioButton("Item", m_NowLoadType == LoadType::eItem)) { m_NowLoadType = LoadType::eItem; m_FileLoadIndex = -1; }
	// ImGui::SameLine();  if (ImGui::RadioButton("EventTrigger", m_NowLoadType == LoadType::eTrigger)) { m_NowLoadType = LoadType::eTrigger; m_FileLoadIndex = -1; }
	// >> todo

	ImGui::Separator();

	if (m_NowLoadType != m_PreLoadType && m_NowLoadType != LoadType::eBackground)
	{
		SetVecItem();
		m_PreLoadType = m_NowLoadType;
	}
	else if (m_NowLoadType == LoadType::eBackground)
	{
		// >> 배경 나무들은 세부 선택 존재
		if (ImGui::RadioButton("AutumnTree", m_SubType == LoadType::eAutumnTree)) { m_SubType = LoadType::eAutumnTree; m_FileLoadIndex = -1; }
		ImGui::SameLine(); if (ImGui::RadioButton("SummerTree", m_SubType == LoadType::eSummerTree)) { m_SubType = LoadType::eSummerTree; m_FileLoadIndex = -1; }

		if (ImGui::RadioButton("WinterTree", m_SubType == LoadType::eWinterTree)) { m_SubType = LoadType::eWinterTree; m_FileLoadIndex = -1; }
		ImGui::SameLine(); if (ImGui::RadioButton("InvisibleWall", m_SubType == LoadType::eInvisibleWall)) { m_SubType = LoadType::eInvisibleWall; m_FileLoadIndex = -1; }

		SetVecItem();
		m_PreLoadType = m_NowLoadType;
	}

	// << combo
	if (m_FileLoadIndex == -1)
		m_showItem = " ";
	else
		m_showItem = m_vecItem[m_FileLoadIndex].c_str();

	if (ImGui::BeginCombo(" ", m_showItem.c_str()))
	{
		for (int n = 0; n < m_vecItem.size(); n++)
		{
			const bool is_selected = (m_FileLoadIndex == n);
			if (ImGui::Selectable(m_vecItem[n].c_str(), is_selected))
				m_FileLoadIndex = n;

			if (is_selected)
				ImGui::SetItemDefaultFocus(); // focus
		}
		ImGui::EndCombo();
	}
	// << combo

	ImGui::SameLine();
	if (ImGui::Button("Load") && m_FileLoadIndex != -1)
	{
		IObject::CreateObject(m_vecObjType[m_FileLoadIndex], m_FileLoadIndex);
	}

	ImGui::Separator();

	ImGui::End();
}

void CImguiClass::Update_Inspector()
{
	ImGui::Begin("Inspector");

	bool isCheck = false;
	int vecSize = g_pObjectManager->GetVecSize();
	for (int i = 0; i < vecSize; i++)
	{
		if (g_pObjectManager->GetIObject(i).GetClick() || g_pObjectManager->GetIObject(i).GetPick())
			isCheck = true;
	}
	// >> : 선택된 것이 없으면 인스펙터 창 뜨지 않음

	if (m_prevSelectIndex == m_nowSelectindex && isCheck)
	{
		if (m_nowSelectindex >= 0)
		{
			char name[1024] = "\0";
			int strLength = g_pObjectManager->GetIObject(m_nowSelectindex).GetObjectName().length();
			for (int i = 0; i < strLength; i++)
			{
				name[i] = g_pObjectManager->GetIObject(m_nowSelectindex).GetObjectName()[i];
			}
			name[strLength] = '\0';

			bool isCheck = false;
			if (ImGui::InputText("Name", name, 1024))
				isCheck = true;

			// >> 이름 변경 판정 다시 하기?
			if (isCheck)
			{
				bool isSame = false;
				int vecSize = g_pObjectManager->GetVecSize();
				for (int i = 0; i < vecSize; i++)
				{
					if (strcmp(g_pObjectManager->GetIObject(i).GetObjectName().c_str(), name) == 0)
						isSame = true;
				}

				if (!isSame) g_pObjectManager->GetIObject(m_nowSelectindex).SetObjectName(name);
			}
			// << 이름 변경 판정 다시 하기?

			ImGui::Separator();

			D3DXVECTOR3 vScale = g_pObjectManager->GetIObject(m_nowSelectindex).GetScale();
			if (ImGui::InputFloat3("Scale", vScale))
			{
				ObjectType tempType = g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType();

				if (tempType == eSphere || tempType == eCylinder
				 || tempType == eG_RotationBoard || tempType == eG_BreakWall || tempType == eG_Door
				 || tempType == eG_ColorChanger || tempType == eG_Switch)
					g_pObjectManager->GetIObject(m_nowSelectindex).SetDiffScale(vScale);
				else
					g_pObjectManager->GetIObject(m_nowSelectindex).SetScale(vScale);
			}

			D3DXVECTOR3 vRot = g_pObjectManager->GetIObject(m_nowSelectindex).GetRotate();
			if (ImGui::InputFloat3("Rotate", vRot))
				g_pObjectManager->GetIObject(m_nowSelectindex).SetRotate(vRot);

			D3DXVECTOR3 vTrans = g_pObjectManager->GetIObject(m_nowSelectindex).GetTranslate();
			if (ImGui::InputFloat3("Translate", vTrans))
				g_pObjectManager->GetIObject(m_nowSelectindex).SetTranslate(vTrans);

			ImGui::Separator();

			// >> 선택된 오브젝트에 따라 인스펙터 변경
			if (g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eBox
				|| g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eSphere
				|| g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eCylinder)
			{
				// >> object만 색 지정 가능
				SetObjectColor();
			}
			else if (g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eG_RotationBoard)
			{
				// >> 회전판자 기믹
				CRotationBoard* temp = dynamic_cast<CRotationBoard*> (&g_pObjectManager->GetIObject(m_nowSelectindex));

				ImGui::Text("RotationAxial");
				static int pushIndex = 0;
				string charName[3] = { "Rot_X", "Rot_Y", "Rot_Z" };
				for (int i = 0; i < 3; i++)
				{
					if (ImGui::RadioButton(charName[i].c_str(), pushIndex == i))
					{
						pushIndex = i;
						temp->SetRotationAxialIndex(pushIndex);
					}

					if (i + 1 != 3) ImGui::SameLine();
				} // << : for

				ImGui::Separator();

				float fSpeed = temp->GetRotationSpeed();
				if(ImGui::InputFloat("RoationSpeed", &fSpeed))
					temp->SetRotationSpeed(fSpeed);
				
				ImGui::Separator();

			} // << : Rotation Board

		} // << : if (m_nowSelectindex >= 0)

	} // << : if (m_prevSelectIndex == m_nowSelectindex)
	else
	{
		m_prevSelectIndex = m_nowSelectindex;
		if (g_pObjectManager->GetVecSize() != 0 && m_nowSelectindex >= 0)
		{
			D3DXCOLOR temp = g_pObjectManager->GetIObject(CImguiClass::m_nowSelectindex).GetColor();

			if (temp == D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))		m_NowcolorType = ColorType::eGray;
			else if (temp == D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)) m_NowcolorType = ColorType::eBlack;
			else if (temp == D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)) m_NowcolorType = ColorType::eWhite;
			else if (temp == D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)) m_NowcolorType = ColorType::eRed;
			else if (temp == D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)) m_NowcolorType = ColorType::eGreen;
			else if (temp == D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)) m_NowcolorType = ColorType::eBlue;
			else if (temp == D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)) m_NowcolorType = ColorType::eYellow;
		}
		//else
		//	m_NowcolorType = ColorType::eGray;
	}

	ImGui::End();
}

void CImguiClass::SetFrameEnd()
{
	ImGui::EndFrame();
}

void CImguiClass::Render()
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void CImguiClass::ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	g_pDeviceManager->ResetDevice();
	ImGui_ImplDX9_CreateDeviceObjects();
}

void CImguiClass::Destroy()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
