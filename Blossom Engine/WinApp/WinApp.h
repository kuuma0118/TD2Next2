#pragma once

#include <../externals/imgui/imgui.h>
#include <../externals/imgui/imgui_impl_dx12.h>
#include <../externals/imgui/imgui_impl_win32.h>

#include <string>
#include <stdint.h>
#include <Windows.h>
#include <cstdint>
#include <d3d12.h>

#include <wrl.h>

#pragma comment(lib,"d3d12.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class WinApp {
public:

	static WinApp* GetInstance();

	HINSTANCE GetWc() { return wc_.hInstance; }

	Microsoft::WRL::ComPtr<ID3D12Debug1> GetDebugController() { return debugController_; }

	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;

	inline HWND GetHwnd() { return hwnd_; }

	bool ProcessMessage();

	void Finalize();

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void CreateGameWindow(const wchar_t* title, int32_t clientWidth, int32_t clientHeight);

	// デバッグレイヤ
	void DebugLayer();

	// Windowsの初期化
	void Initialize(const wchar_t* title, int32_t kClientWidth, int32_t kClientHeight);

	// 出力ウィンドウに文字を出す
	static void Log(const std::string& message);

private:
	Microsoft::WRL::ComPtr<ID3D12Debug1> debugController_;

	WNDCLASS wc_{};
	RECT wrc_ = { 0,0,kClientWidth,kClientHeight };

	HWND hwnd_;
	UINT windowStyle_;
};