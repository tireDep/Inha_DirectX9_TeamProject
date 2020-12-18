#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "stdafx.h"
#include "IObject.h"

#include "Background.h"

#include "Gimmick.h"
#include "RotationBoard.h"
#include "Switch.h"
#include "Door.h"
#include "MovingCube.h"
#include "ColorChanger.h"
#include "Orb.h"
#include "Trace.h"

#include "ImguiClass.h"

int CImguiClass::m_nowSelectindex = -1;
int CImguiClass::m_prevSelectIndex = 0;
int CImguiClass::m_FileLoadIndex = 0;
ObjectType CImguiClass::m_nowObjType = ObjectType::eNull;

void CImguiClass::SetVecItem()
{
	vector<string> tempVec;
	vector<ObjectType> tempObjType;
	if (m_NowLoadType == LoadType::eMap)
	{
		tempVec.push_back("Tile_01_grass");		tempObjType.push_back(eTile01);
		tempVec.push_back("Tile_02_ground");	tempObjType.push_back(eTile02);
		tempVec.push_back("Tile_04_ground2");	tempObjType.push_back(eTile03);
		tempVec.push_back("Tile_05_rock");		tempObjType.push_back(eTile04);
		tempVec.push_back("Tile_07_rock2");		tempObjType.push_back(eTile05);
		tempVec.push_back("Tile_11_sand");		tempObjType.push_back(eTile06);
		tempVec.push_back("Tile_12_sand2");		tempObjType.push_back(eTile07);
		tempVec.push_back("Tile_13_water");		tempObjType.push_back(eTile08);
		tempVec.push_back("Tile_14_water2");	tempObjType.push_back(eTile09);
		tempVec.push_back("Tile_15_water3");	tempObjType.push_back(eTile10);
		tempVec.push_back("Tile_16_water4");	tempObjType.push_back(eTile11);
		tempVec.push_back("Tile_17_yellow");	tempObjType.push_back(eTile12);

		tempVec.push_back("Tile_Ocean");		tempObjType.push_back(eTile13);

		tempVec.push_back("Bridge");			tempObjType.push_back(eBridge);
	}
	else if (m_NowLoadType == LoadType::eObject)
	{
		tempVec.push_back("Object_Box");			tempObjType.push_back(eBox);
		tempVec.push_back("Object_Sphere");			tempObjType.push_back(eSphere);
		tempVec.push_back("Object_Cylinder");		tempObjType.push_back(eCylinder);
	}
	else if (m_NowLoadType == LoadType::eBackground)
	{
		if (m_SubType == LoadType::eAutumnTree)
		{
			tempVec.push_back("autumn_tree_01");
			tempVec.push_back("autumn_tree_02");
			tempVec.push_back("autumn_tree_03");
			tempVec.push_back("autumn_tree_04");
			tempVec.push_back("autumn_ctree_07");
			tempVec.push_back("autumn_tree_08");

			for (int i = 0; i < tempVec.size(); i++)
				tempObjType.push_back(eATree);
		}
		else if (m_SubType == LoadType::eSummerTree)
		{
			tempVec.push_back("summer_tree_01");
			tempVec.push_back("summer_tree_02");
			tempVec.push_back("summer_tree_03");
			tempVec.push_back("summer_tree_04");
			tempVec.push_back("summer_ctree_07");
			tempVec.push_back("summer_tree_08");

			for (int i = 0; i < tempVec.size(); i++)
				tempObjType.push_back(eSTree);
		}
		else if (m_SubType == LoadType::eWinterTree)
		{
			tempVec.push_back("winter_tree_01");
			tempVec.push_back("winter_tree_02");
			tempVec.push_back("winter_tree_03");
			tempVec.push_back("winter_tree_04");
			tempVec.push_back("winter_ctree_07");
			tempVec.push_back("winter_tree_08");

			for (int i = 0; i < tempVec.size(); i++)
				tempObjType.push_back(eWTree);
		}
		else if (m_SubType == LoadType::eColorTree)
		{
			tempVec.clear();
			tempVec.push_back("A_Tree_blue_016");
			tempVec.push_back("A_Tree_blue_020");
			tempVec.push_back("C_Bush_blue_070");
			tempVec.push_back("C_Bush_blue_071");
			tempVec.push_back("D_Shrub_blue_101");
			tempVec.push_back("D_Shrub_blue_102");

			for (int i = 0; i < tempVec.size(); i++)
				tempObjType.push_back(eCTree);
		}

		else if (m_SubType == LoadType::eSomethingElse)
		{
			tempVec.clear();
			tempVec.push_back("flower_white");		tempObjType.push_back(eFlower);
			tempVec.push_back("flower_purple");		tempObjType.push_back(eFlower);
			tempVec.push_back("flower_red");		tempObjType.push_back(eFlower);
			tempVec.push_back("flower_orange");		tempObjType.push_back(eFlower);
			tempVec.push_back("flower_blue");		tempObjType.push_back(eFlower);
			tempVec.push_back("flower_yellow");		tempObjType.push_back(eFlower);

			tempVec.push_back("sprout");			tempObjType.push_back(eSprout);

			tempVec.push_back("ball");				tempObjType.push_back(eBall);
			tempVec.push_back("blue chair");		tempObjType.push_back(eChair);
			tempVec.push_back("Umbrella_blue");		tempObjType.push_back(eUmbrella);
			tempVec.push_back("Snowman");			tempObjType.push_back(eSnowman);

			tempVec.push_back("BackGround_InvisibleWall"); tempObjType.push_back(eInvisibleWall);
		}


	} // << background


	else if (m_NowLoadType == LoadType::eGimmick)
	{
		tempVec.push_back("Gimmick_RotationBoard");		tempObjType.push_back(eG_RotationBoard);
		tempVec.push_back("Gimmick_MovingCube");		tempObjType.push_back(eG_MovingCube);
#ifdef _DEBUG
		tempVec.push_back("Gimmick_Switch");			tempObjType.push_back(eG_Switch);
		tempVec.push_back("Gimmick_Door");				tempObjType.push_back(eG_DoorFrame);
		tempVec.push_back("Gimmick_ColorChanger");		tempObjType.push_back(eG_ColorChanger);
		tempVec.push_back("Gimmick_BreakWall");			tempObjType.push_back(eG_BreakWall);
#endif
	}

#ifdef _DEBUG
	else if (m_NowLoadType == LoadType::eItem)
	{
		tempVec.push_back("Item_Book");	tempObjType.push_back(eBook);
		tempVec.push_back("Item_Orb");	tempObjType.push_back(eOrb);
		tempVec.push_back("Item_Trace");	tempObjType.push_back(eTrace);
	}
#endif

	m_vecItem = tempVec;
	m_vecObjType = tempObjType;
}

void CImguiClass::SetObjectColor()
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
}

void CImguiClass::SetGimmickTexture()
{
	CGimmick* temp = static_cast<CGimmick*> (&g_pObjectManager->GetIObject(m_nowSelectindex));

	if(g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eG_DoorFrame)
		temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(m_nowSelectindex));

	ImGui::Text("Texture");
	int pushIndex = temp->GetTextureIndex();
	string charName[4] = { "Glow", "Metal", "Rough", "Texture" };
	for (int i = 0; i < 4; i++)
	{
		if (ImGui::RadioButton(charName[i].c_str(), pushIndex == i))
		{
			pushIndex = i;
			temp->SetTexture(pushIndex);
		}
	} // << : for

	ImGui::Separator();
}

void CImguiClass::SetGimmickCondition()
{
	CGimmick* temp = static_cast<CGimmick*> (&g_pObjectManager->GetIObject(m_nowSelectindex));

	if (g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eG_DoorFrame)
		temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(m_nowSelectindex));

	ImGui::Text("On/Off Condition");
	int pushIndex = temp->GetOpenConditionIndex();
	string charName[3] = { "Orb", "Item", "Switch" };

	for (int i = 0; i < 3; i++)
	{
		if (ImGui::RadioButton(charName[i].c_str(), pushIndex == i))
		{
			pushIndex = i;
		}
		if (i < 2) ImGui::SameLine();
	} // << : for

	ImGui::Separator();

	int conditionNum = temp->GetOpenConditionIndex();
	if (pushIndex == 0)
	{
		if (conditionNum > 0)
		{
			g_pObjectManager->RemoveCondition(temp->GetConditionName());
			temp->SetConditionName("Black");
			temp->SetConditionOrbIndex(0);
		}

		// >> 오브 선택
		int orbType = temp->GetConditionOrbIndex();
		string charName[6] = { "Black", "White", "Yellow", "Green", "Red", "Blue" };

		for (int i = 0; i < 6; i++)
		{
			if (ImGui::RadioButton(charName[i].c_str(), orbType == i))
			{
				temp->SetConditionOrbIndex(i);
				temp->SetConditionName(charName[i]);
			}

			if (i != 2 && i != 5)
				ImGui::SameLine();
		} // << : for

		temp->SetOpenCondition(pushIndex);

		ImGui::Separator();
	}
	else if (pushIndex == 1 && pushIndex != conditionNum)
	{
		// >> 조건 바뀔 시 기존 조건 삭제
		if (temp->GetConditionName() != "")
		{
			if (conditionNum >  0)
				g_pObjectManager->RemoveCondition(temp->GetConditionName());
			temp->SetConditionName("");
		}

		// >> 아이템 선택
		if (temp->GetConditionName() == "")
			IObject::CreateObject(eBook, 0);

		D3DXVECTOR3 pos = temp->GetTranslate();
		pos.x -= 2;		pos.z -= 2;
		g_pObjectManager->GetIObject(g_pObjectManager->GetVecSize() - 1).SetTranslate(pos);
		g_pObjectManager->GetIObject(g_pObjectManager->GetVecSize() - 1).SetConditionName(temp->GetObjectName());

		temp->SetOpenCondition(pushIndex);
		temp->SetConditionName(g_pObjectManager->GetIObject(g_pObjectManager->GetVecSize() - 1).GetObjectName());
	}
	else if (pushIndex == 2 && pushIndex != conditionNum)
	{
		// >> 조건 바뀔 시 기존 조건 삭제
		if (temp->GetConditionName() != "")
		{
			if (conditionNum >  0)
				g_pObjectManager->RemoveCondition(temp->GetConditionName());
			temp->SetConditionName("");
		}

		// >> 스위치 선택
		if (temp->GetConditionName() == "")
			IObject::CreateObject(eG_Switch, 0);

		D3DXVECTOR3 pos = temp->GetTranslate();
		pos.x -= 2;		pos.z -= 2;
		g_pObjectManager->GetIObject(g_pObjectManager->GetVecSize() - 1).SetTranslate(pos);
		g_pObjectManager->GetIObject(g_pObjectManager->GetVecSize() - 1).SetConditionName(temp->GetObjectName());

		temp->SetOpenCondition(pushIndex);
		temp->SetConditionName(g_pObjectManager->GetIObject(g_pObjectManager->GetVecSize() - 1).GetObjectName());
	}

	ImGui::Text("[ Now Condition ]");
	ImGui::Text("OpenType : ");
	ImGui::SameLine(); ImGui::Text(temp->GetOpenConditionType().c_str());
}

CImguiClass::CImguiClass() :
	m_isReset(false),
	m_showItem("\0"),
	m_pMesh(NULL)
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
	SafeRelease(m_pMesh);
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

	Update_MenuTitleBar();
	Update_Hiearachy();
	Update_FileLoader();
	Update_Inspector();
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

		// >> testLoad
		if (ImGui::BeginMenu("TestLoad"))
		{
			if (ImGui::MenuItem("ModelLoad", " ")) 
			{
				ST_XFile* temp = new ST_XFile;
				g_pFileLoadManager->FileLoad_XFile("Resource/XFile/Test", "Model.X", temp);

				m_pMesh = temp->pMesh;
				m_adjBuffer = temp->adjBuffer;
				m_vecMtrls = temp->vecMtrl;
				m_vecTextures = temp->vecTextrure;
				m_numMtrls = temp->nMtrlNum;

				delete temp;
			}

			if (ImGui::MenuItem("ModelDelete", " "))
			{
				SafeRelease(m_pMesh);
				m_adjBuffer->Release();
				m_vecMtrls.clear();
				m_vecTextures.clear();
				m_numMtrls = 0;
			}

			ImGui::EndMenu();
		}
		// << testLoad

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

	if (ImGui::RadioButton("MapTile", m_NowLoadType == LoadType::eMap)) { m_NowLoadType = LoadType::eMap; m_FileLoadIndex = 0; }
	ImGui::SameLine(); if (ImGui::RadioButton("Object", m_NowLoadType == LoadType::eObject)) { m_NowLoadType = LoadType::eObject; m_FileLoadIndex = 0; }

	if (ImGui::RadioButton("Background", m_NowLoadType == LoadType::eBackground)) { m_NowLoadType = LoadType::eBackground; m_FileLoadIndex = 0; }

	ImGui::SameLine();  if (ImGui::RadioButton("Gimmick", m_NowLoadType == LoadType::eGimmick)) { m_NowLoadType = LoadType::eGimmick; m_FileLoadIndex = 0; }
#ifdef _DEBUG
	if (ImGui::RadioButton("Item", m_NowLoadType == LoadType::eItem)) { m_NowLoadType = LoadType::eItem; m_FileLoadIndex = 0; }
	// ImGui::SameLine();  if (ImGui::RadioButton("EventTrigger", m_NowLoadType == LoadType::eTrigger)) { m_NowLoadType = LoadType::eTrigger; m_FileLoadIndex = -1; }
#endif // _DEBUG

	ImGui::Separator();

	if (m_NowLoadType != m_PreLoadType && m_NowLoadType != LoadType::eBackground)
	{
		SetVecItem();
		m_PreLoadType = m_NowLoadType;
	}
	else if (m_NowLoadType == LoadType::eBackground)
	{
		// >> 배경 나무들은 세부 선택 존재
		if (ImGui::RadioButton("AutumnTree", m_SubType == LoadType::eAutumnTree)) { m_SubType = LoadType::eAutumnTree; m_FileLoadIndex = 0; }
		ImGui::SameLine(); if (ImGui::RadioButton("SummerTree", m_SubType == LoadType::eSummerTree)) { m_SubType = LoadType::eSummerTree; m_FileLoadIndex = 0; }

		if (ImGui::RadioButton("WinterTree", m_SubType == LoadType::eWinterTree)) { m_SubType = LoadType::eWinterTree; m_FileLoadIndex = 0; }
		ImGui::SameLine(); if (ImGui::RadioButton("ColorTree", m_SubType == LoadType::eColorTree)) { m_SubType = LoadType::eColorTree; m_FileLoadIndex = 0; }

		if (ImGui::RadioButton("SomethingElse", m_SubType == LoadType::eSomethingElse)) { m_SubType = LoadType::eSomethingElse; m_FileLoadIndex = 0; }

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
	m_nowObjType = m_vecObjType[m_FileLoadIndex];
	if (ImGui::Button("Load") && m_FileLoadIndex != -1)
	{
		g_pObjectManager->SetSelectAllFalse();

		IObject::CreateObject(m_nowObjType, m_FileLoadIndex);
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
			IObject& nowObject = g_pObjectManager->GetIObject(m_nowSelectindex);

			char name[1024] = "\0";
			int strLength = nowObject.GetObjectName().length();
			for (int i = 0; i < strLength; i++)
			{
				name[i] = nowObject.GetObjectName()[i];
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

				if (!isSame) nowObject.SetObjectName(name);
			}
			// << 이름 변경 판정 다시 하기?

			ImGui::Separator();

			D3DXVECTOR3 vScale = nowObject.GetScale();
			ObjectType tempType = nowObject.GetObjType();
			if (ImGui::InputFloat3("Scale", vScale))
			{
				switch (tempType)
				{
				case eSphere:	case eCylinder:

				case eATree:	case eSTree:	case eWTree:	case eCTree:
				case eSomethingElse:	case eBall:	case eChair:	case eUmbrella:
				case eSnowman:	

				case eFlower:	case eSprout:
				
				case eInvisibleWall:

				case eG_RotationBoard:	case eG_MovingCube:

#ifdef _DEBUG 				
				case eG_BreakWall:
				case eG_ColorChanger:	case eG_Switch:		

				case eBook:				case eOrb:
				case eTrace:
#endif
				{
					nowObject.SetDiffScale(vScale);
				}
					break;

#ifdef _DEBUG
				case eG_DoorFrame:	 case eG_Door:
				{
					CDoor* temp = static_cast<CDoor*> (&nowObject);
					temp->SetAnotherScale(vScale);
				}
				break;
#endif // _DEBUG

				default:
				{
					nowObject.SetScale(vScale);
				}
					break;
				}
			}

			D3DXVECTOR3 vRot = nowObject.GetRotate();
			if (ImGui::InputFloat3("Rotate", vRot))
			{
#ifdef _DEBUG
				if (tempType == ObjectType::eG_DoorFrame || tempType == ObjectType::eG_Door)
				{
					CDoor* temp = dynamic_cast<CDoor*> (&nowObject);
					temp->SetAnotherRotation(vRot);
				}
				else
					nowObject.SetRotate(vRot);
#else
				nowObject.SetRotate(vRot);
#endif // _DEBUG
			}

			D3DXVECTOR3 vTrans = nowObject.GetTranslate();
			D3DXVECTOR3 temp = vTrans;
			if (ImGui::InputFloat3("Translate", vTrans))
			{
				// >> 격자에 맞춰 이동(체스 느낌)
				if (temp.x != vTrans.x)
				{
					if (vTrans.x == 0)
						temp.x = 0;
					else
					{
						temp.x = floor(vTrans.x);
						temp.x = temp.x <= 0 ? temp.x + 0.5f : temp.x - 0.5f;
					}
				}

				if (temp.y != vTrans.y)
				{
					temp.y = vTrans.y;
					// >> 오브젝트 별 적용이 달라서 임시 적용

					// if (g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() != eSphere
					//  && g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() != eCylinder
					//  && g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() != eBox)
					// 	temp.y = floor(vTrans.y);
					// else
					// 	temp.y = vTrans.y;
					// // >> 오브젝트는 크기 변경에 따라 값이 변동되기 때문에 일단 제외

					// // >> 구, 실린더는 보정 값 적용?
					// if (g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eSphere)
					// 	temp.y += 0.25f;
					// 
					// if(g_pObjectManager->GetIObject(m_nowSelectindex).GetObjType() == eCylinder)
					// 	temp.y += 0.5f;
				}
				
				if (temp.z != vTrans.z)
				{
					if (vTrans.z == 0)
						temp.z = 0;
					else
					{
						temp.z = floor(vTrans.z);
						temp.z = temp.z <= 0 ? temp.z + 0.5f : temp.z - 0.5f;
					}
				}

				vTrans = temp;

#ifdef _DEBUG
				if (tempType == ObjectType::eG_DoorFrame || tempType == ObjectType::eG_Door)
				{
					CDoor* temp = dynamic_cast<CDoor*> (&nowObject);
					temp->SetAnotherTranslation(vTrans);
				}
				else if (tempType == ObjectType::eTrace)
				{
					CTrace* temp = static_cast<CTrace*>(&nowObject);
					temp->SetTranslate(vTrans);
				}
				else
					nowObject.SetTranslate(vTrans);
#else
				nowObject.SetTranslate(vTrans);
#endif // _DEBUG

			}

			ImGui::Separator();

			// >> 선택된 오브젝트에 따라 인스펙터 변경

			// >> 물리 적용 오브젝트 : 색상 선택
			ObjectType nowObjectType = nowObject.GetObjType();
			if (nowObjectType == eBox || nowObjectType == eSphere || nowObjectType == eCylinder)
			{
				// >> object만 색 지정 가능
				SetObjectColor();
			}

			// >> 배경 관련
			// >> 색상 나무 : 텍스쳐 선택
			else if (nowObjectType == eUmbrella)
			{
				CBackground* temp = static_cast<CBackground*> (&g_pObjectManager->GetIObject(m_nowSelectindex));

				ImGui::Text("Texture");
				int pushIndex = temp->GetTextureIndex();
				string charName[4] = { "Blue", "BlueRed", "Red", "White" };
				for (int i = 0; i < 4; i++)
				{
					if (ImGui::RadioButton(charName[i].c_str(), pushIndex == i))
					{
						pushIndex = i;
						temp->SetTexture(pushIndex);
					}
				} // << : for

				ImGui::Separator();
			}

			// >> 파라솔 : 텍스쳐 선택
			else if (nowObjectType == eCTree)
			{
				CBackground* temp = static_cast<CBackground*> (&g_pObjectManager->GetIObject(m_nowSelectindex));

				ImGui::Text("Texture");
				int pushIndex = temp->GetTextureIndex();
				string charName[4] = { "Blue", "Green", "Yellow", "Red" };
				for (int i = 0; i < 4; i++)
				{
					if (ImGui::RadioButton(charName[i].c_str(), pushIndex == i))
					{
						pushIndex = i;
						temp->SetTexture(pushIndex);
					}
				} // << : for

				ImGui::Separator();
			}
			
			// >> 기믹 관련
			// >> 회전판자 기믹 : 기믹 관련 변수 설정
			else if (nowObjectType == eG_RotationBoard)
			{
				CRotationBoard* temp = static_cast<CRotationBoard*> (&g_pObjectManager->GetIObject(m_nowSelectindex));

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

			// >> 스위치 기믹 : 텍스쳐 선택, 조건 선택
			else if (nowObjectType == eG_Switch)
			{
				SetGimmickTexture();
				// todo : switchCondition
			}

			// >> 무빙 큐브 기믹 : 시작점&끝점, 속도, 방향
			else if (nowObjectType == eG_MovingCube)
			{
				CMovingCube* temp = static_cast<CMovingCube*> (&g_pObjectManager->GetIObject(m_nowSelectindex));
				ImGui::Text("Direction");
				static int pushIndex = 0;
				pushIndex = temp->GetDirection();
				string charName[3] = { "X", "Y", "Z" };
				for (int i = 0; i < 3; i++)
				{
					if (ImGui::RadioButton(charName[i].c_str(), pushIndex == i))
					{
						pushIndex = i;
						temp->SetDirection(pushIndex);
					}
				} // << : for

				ImGui::Separator();

				float inputS = temp->GetStartPos();
				if (ImGui::InputFloat("StartPos", &inputS))
					temp->SetStartPos(inputS);

				float inputE = temp->GetEndPos();
				if (ImGui::InputFloat("EndPos", &inputE))
					temp->SetEndPos(inputE);

				ImGui::Separator();

				float inputSpeed = temp->GetSpeed();
				if (ImGui::InputFloat("Speed", &inputSpeed))
					temp->SetSpeed(inputSpeed);

			}

			// >> 문, 컬러레이저 기믹 : 텍스쳐 선택, On/Off 조건 선택
			else if (nowObjectType == eG_DoorFrame 
				  || nowObjectType == eG_ColorChanger)
			{
				SetGimmickTexture();
				SetGimmickCondition();
			}

			// >> 오브, 흔적 : 스프라이트 선택
			else if (nowObjectType == eOrb || nowObjectType == eTrace)
			{
				CItem* temp = static_cast<CItem*> (&nowObject);

				ImGui::Text("Texture");
				int pushIndex = temp->GetSpriteIndex();
				string charName[6] = { "Black", "White", "Yellow", "Green", "Red", "Blue" };
				for (int i = 0; i < 6; i++)
				{
					if (ImGui::RadioButton(charName[i].c_str(), pushIndex == i))
					{
						pushIndex = i;
						temp->SetSpriteIndex(pushIndex);
					}
				} // << : for

				ImGui::Separator();
			}
			
			if (nowObject.GetConditionName() != "" 
			 && (nowObjectType == ObjectType::eG_Door
				 || nowObjectType == ObjectType::eG_DoorFrame
				 || nowObjectType == ObjectType::eG_ColorChanger
				 || nowObjectType == ObjectType::eG_Switch
				 || nowObjectType == ObjectType::eBook
				 || nowObjectType == ObjectType::eOrb))
			{
				// >> 선택한 오브젝트에 조건 변수가 존재할 경우
				// >> 스위치 등 기믹에서 출력되지 않아서 if문으로 처리
				ImGui::Text("Select Condition : ");
				ImGui::SameLine(); ImGui::Text(g_pObjectManager->GetIObject(m_nowSelectindex).GetConditionName().c_str());
			}

			// >> tag
			switch (nowObjectType)
			{
				case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
				case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
				case eBridge:
				case eATree:  case eSTree:	case eWTree:  case eCTree:
				case eBall:	  case eChair:	case eUmbrella:	case eSnowman:	case eFlower: 	case eSprout:
				{
					ImGui::Text("ColorTag");
					vector<string> tag = nowObject.GetVecColorTag();
					ImVec4 buttonColor(1, 1, 1, 0.7);
					for (int i = 0; i < tag.size(); i++)
					{
						// ImGui::Text(tag[i].c_str());
						//ImGui::TextColored(ImVec4(0.0f, 0.0f, 1.0f, 1.0f), tag[i].c_str());
						//ImGui::ColorButton(tag[i].c_str(), ImVec4(0.0f, 0.0f, 1.0f, 1.0f));

						if (tag[i] == "Black")			buttonColor = ImVec4(0, 0, 0, 0.7f);
						else if (tag[i] == "White")		buttonColor = ImVec4(1, 1, 1, 0.7f);
						else if (tag[i] == "Red")		buttonColor = ImVec4(1, 0, 0, 0.7f);
						else if (tag[i] == "Blue")		buttonColor = ImVec4(0, 0, 1, 0.7f);
						else if (tag[i] == "Green")		buttonColor = ImVec4(0, 1, 0, 0.7f);
						else if (tag[i] == "Yellow")	buttonColor = ImVec4(1, 1, 0, 0.7f);

						ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
						ImGui::Button(tag[i].c_str());
						ImGui::PopStyleColor(2);
					}
				}
					break;
			}
			// << tag

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
	// >> testLoad
	
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	matWorld._41 = 0.5f; matWorld._43 = 0.5f;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

		if (m_vecTextures[i] != 0)
			g_pD3DDevice->SetTexture(0, m_vecTextures[i]);

		if(m_pMesh)
			m_pMesh->DrawSubset(i);
	}
	g_pD3DDevice->SetTexture(0, NULL);
	// << testLoad
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

void CImguiClass::CreateMouseRBtn()
{
	if (m_FileLoadIndex != -1)
	{
		g_pObjectManager->SetSelectAllFalse();

		if (m_nowObjType == eG_Door)
			m_nowObjType = eG_DoorFrame;

		IObject::CreateObject(m_nowObjType, m_FileLoadIndex);
	}
}

float CImguiClass::GetObjecFirstHeight()
{
	float height = 0.0f;
	switch (m_nowObjType)
	{
	case eBox:
	case eCylinder:
	case eSphere:
		height = 0.5f;
		break;

	case eBook:
		height = 0.5f;
		break;

	case eOrb:
		height = 0.6f;
		break;

	default:
		height = 0.0f;
		break;
	}

	return height;
}

