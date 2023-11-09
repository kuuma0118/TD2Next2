#include "ImGuiManager.h"

ImGuiManager* ImGuiManager::GetInstance() {
	static ImGuiManager instance;
	return &instance;
}

void ImGuiManager::Initialize() {

	//ウィンドウズアプリケーションのインスタンスを取得
	winApp_ = WinApp::GetInstance();
	//DirectXCommonのインスタンスを取得
	dxCommon_ = DirectXCommon::GetInstance();


	//SRVDescriptorHeapの作成
	srvDescriptorHeap_ = dxCommon_->CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1, true);


	//ImGuiの初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winApp_->GetHwnd());
	ImGui_ImplDX12_Init(dxCommon_->GetDevice(),
		2,
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		srvDescriptorHeap_.Get(),
		srvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart(),
		srvDescriptorHeap_->GetGPUDescriptorHandleForHeapStart());
}

void ImGuiManager::Begin() {

	//ImGuiにフレームの開始を伝える
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End() {

	//ImGuiの内部コマンドを生成する
	ImGui::Render();
}

void ImGuiManager::Draw() {

	//コマンドリストを取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();


	//描画用のDescriptorHeapの設定
	ID3D12DescriptorHeap* descriptorHeaps[] = { srvDescriptorHeap_.Get() };
	commandList->SetDescriptorHeaps(1, descriptorHeaps);


	//実際にcommandListのImGuiの描画コマンドを積む
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList);
}

void ImGuiManager::Release() {

	//解放処理
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}