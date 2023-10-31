#include "Light.h"
#include <cassert>
#include "../ImGui/ImGuiManager.h"
#include "../externals/imgui/imgui.h"

Light* Light::GetInstance() {
	static Light instance;

	return &instance;
}

Microsoft::WRL::ComPtr<ID3D12Resource> Light::CreateBufferResource(const Microsoft::WRL::ComPtr<ID3D12Device>& device, size_t sizeInBytes) {
	HRESULT hr;
	// 頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; // UploadHeapを使う
	// 頂点リソースの設定
	D3D12_RESOURCE_DESC vertexResourceDesc{};
	// バッファソース。テクスチャの場合はまた別の設定をする
	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexResourceDesc.Width = sizeInBytes; // リソースのサイズ。今回はVector4を3頂点分
	// バッファの場合はこれからは1にする決まり
	vertexResourceDesc.Height = 1;
	vertexResourceDesc.DepthOrArraySize = 1;
	vertexResourceDesc.MipLevels = 1;
	vertexResourceDesc.SampleDesc.Count = 1;
	// バッファの場合はこれにする決まり
	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	// 実際に頂点リソースを作る
	hr = device.Get()->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexResource));
	assert(SUCCEEDED(hr));

	return vertexResource;
}

void Light::CreateDirectionalResource(const Microsoft::WRL::ComPtr<ID3D12Device>& device) {
	directionalLightResource_ = CreateBufferResource(device.Get(), sizeof(DirectionalLight)).Get();
	// マテリアルにデータを書き込む
	directionalLightData_ = nullptr;
	// 書き込むためのアドレスを取得
	directionalLightResource_->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData_));
}

Light::~Light() {

}

void Light::Initialize(const Microsoft::WRL::ComPtr<ID3D12Device>& device) {
	CreateDirectionalResource(device.Get());

	// Lightingのデフォ値
	directionalLightData_->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	directionalLightData_->direction = { 0.0f, -1.0f, 0.0f };
	directionalLightData_->intensity = 1.0f;
}

void Light::ImGuiAdjustParameter() {
	ImGui::SliderFloat3("Lighting.direction", &directionalLightData_->direction.x, -1, 1);
	ImGui::ColorEdit3("Lighting.color", &directionalLightData_->color.x);
	ImGui::SliderFloat("Lighting.intensity", &directionalLightData_->intensity, 0, 1);
}
