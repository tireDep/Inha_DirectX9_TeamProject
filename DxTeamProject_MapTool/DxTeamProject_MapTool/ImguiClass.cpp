#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "stdafx.h"
#include "ImguiClass.h"

CImguiClass::CImguiClass()
{
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
	static bool show_demo_window = true;
	static bool show_another_window = false;
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

#ifdef _DEBUG
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	// ============================================================================================

	{ // >> : Menu Title Bar
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open", " ")) { /* todo Load Map File */ }
				if (ImGui::MenuItem("Save", " ")) { /* todo Load Map File */ }

				ImGui::Separator();

				if (ImGui::MenuItem("Reset", " ")) { /* todo Load Map File */ }

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				// if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				// if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}
				// ImGui::Separator();
				// if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				// if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				// if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	} // << : Menu Title Bar

	{ // >> : Controller
		static LPDIRECT3DTEXTURE9 temp;
		D3DXCreateTextureFromFileA(g_pD3DDevice, "Resource/Test.png", &temp);
		static ImTextureID test = temp;

		ImGui::Begin(" ");

		for (int i = 0; i < 5 ; i++)
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
		}
		ImGui::End();
	} // << : Controller

	{
		ImGui::Begin("Hiearachy");

		static bool temp = false;
		static bool temp2 = false;
		ImGui::Selectable("todo Something", &temp);
		ImGui::Selectable("todo Something2", &temp2);
		// >> 현 상태 : 여러개 선택 가능 => 하나만 선택 가능으로?
		/*
		if (ImGui::TreeNode("Basic"))
		{
		static bool selection[5] = { false, true, false, false, false };
		ImGui::Selectable("1. I am selectable", &selection[0]);
		ImGui::Selectable("2. I am selectable", &selection[1]);
		ImGui::Text("3. I am not selectable");
		ImGui::Selectable("4. I am selectable", &selection[3]);
		if (ImGui::Selectable("5. I am double clickable", selection[4], ImGuiSelectableFlags_AllowDoubleClick))
		if (ImGui::IsMouseDoubleClicked(0))
		selection[4] = !selection[4];
		ImGui::TreePop();
		}
		if (ImGui::TreeNode("Selection State: Single Selection"))
		{
		static int selected = -1;
		for (int n = 0; n < 5; n++)
		{
		char buf[32];
		sprintf(buf, "Object %d", n);
		if (ImGui::Selectable(buf, selected == n))
		selected = n;
		}
		ImGui::TreePop();
		}
		if (ImGui::TreeNode("Selection State: Multiple Selection"))
		{
		HelpMarker("Hold CTRL and click to select multiple items.");
		static bool selection[5] = { false, false, false, false, false };
		for (int n = 0; n < 5; n++)
		{
		char buf[32];
		sprintf(buf, "Object %d", n);
		if (ImGui::Selectable(buf, selection[n]))
		{
		if (!ImGui::GetIO().KeyCtrl)    // Clear selection when CTRL is not held
		memset(selection, 0, sizeof(selection));
		selection[n] ^= 1;
		}
		}
		*/

		ImGui::End();
	}


	{ // >> : FileLoad
		ImGui::Begin("File Loader");

		static int index = -1;
		enum class LoadType { eMap, eBackground, eObject };
		static LoadType mode = LoadType::eBackground;
		if (ImGui::RadioButton("Background", mode == LoadType::eBackground)) { mode = LoadType::eBackground; index = -1; } 
		ImGui::SameLine(); 
		if (ImGui::RadioButton("Object", mode == LoadType::eObject)) { mode = LoadType::eObject; index = -1; }

		vector<char *> vecItem;
		if (mode == LoadType::eBackground)
		{
			vecItem.push_back("BackObj"); vecItem.push_back("BackObj1");
			// >> todo : item 추가
		}
		else if (mode == LoadType::eObject)
		{
			vecItem.push_back("Obj"); vecItem.push_back("Obj1");
			// >> todo : item 추가
		}

		// << combo
		const char* showItem;
		if (index == -1)
			showItem = " ";
		else
			showItem = vecItem[index];

		if (ImGui::BeginCombo(" ", showItem))
		{
			for (int n = 0; n < vecItem.size(); n++)
			{
				const bool is_selected = (index == n);
				if (ImGui::Selectable(vecItem[n], is_selected))
					index = n;

				if (is_selected)
					ImGui::SetItemDefaultFocus(); // focus
			}
			ImGui::EndCombo();
		}
		// << combo

		ImGui::SameLine();
		if (ImGui::Button("Load") && index != -1)
		{
			// >> todo : File load
			cout << "load" << endl;
		}

		ImGui::Separator();

		ImGui::End();
	} // << : FileLoad

	{
		ImGui::Begin("Inspector");

		ImGui::End();
	}
#else
	{
		ImGui::Begin(" ");

		ImGui::End();
	}

	{
		ImGui::Begin("Hiearachy");

		ImGui::End();
	}


	{
		ImGui::Begin("File Loader");

		ImGui::End();
	}

	{
		ImGui::Begin("Inspector");

		ImGui::End();
	}

#endif // _DEBUG
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
