#pragma once

#include <../Blossom Engine/Common/Common.h>
#include "../Blossom Engine/WinApp/WinApp.h"
#include <stdint.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>

#include "../externals/ImGui/imgui.h"
#include "../externals/ImGui/imgui_impl_dx12.h"
#include "../externals/ImGui/imgui_impl_win32.h"
#include <wrl.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class ImGuiManager {
public:
	void Initialize(HWND hwnd);
	void PreDraw();
	void PostDraw();
	void Release();
};