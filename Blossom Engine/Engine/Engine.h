#pragma once

#include "../Blossom Engine/Common/Common.h"
#include <dxcapi.h>
#include "../Blossom Engine/Math/Vector4.h"
#include "../Blossom Engine/Sys/Sys.h"
#include "../ImGui/ImGuiManager.h"


#include <../externals/DirectXTex/d3dx12.h>

#pragma comment(lib,"dxcompiler.lib")

class ModelEngine {
public:
	void VariableInitialize();

	void Initialize(WinApp* winApp, int32_t width, int32_t height);

	void BeginFrame();

	void EndFrame();

	void Finalize();

	void Update();

	void Draw();

	void LoadTexture(const std::string& filePath, uint32_t index);

	DirectXCommon* GetDirectXCommon() { return directXCommon_; }

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_[2];
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_[2];

	D3D12_CPU_DESCRIPTOR_HANDLE GetTextureSrvHandleCPU(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureSrvHandleGPU(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);
private:
    WinApp* winApp_;
    DirectXCommon* directXCommon_;

	D3D12_DEPTH_STENCIL_DESC depthStencilDesc_{};

	ImGuiManager* imguiManager_;

	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource_[2];

	IDxcUtils* dxcUtils_;
	IDxcCompiler3* dxcCompiler_;

	IDxcIncludeHandler* includeHandler_;

	Microsoft::WRL::ComPtr<ID3DBlob> signatureBlob_;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob_;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc_{};
	D3D12_BLEND_DESC blendDesc_{};

	IDxcBlob* vertexShaderBlob_;
	IDxcBlob* pixelShaderBlob_;

	D3D12_RASTERIZER_DESC rasterizerDesc_{};
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState_;

	D3D12_VIEWPORT viewPort_{};
	D3D12_RECT scissorRect_{};
	D3D12_INPUT_ELEMENT_DESC inputElementDescs_[3];

	Vector4 vertexData_;

	Microsoft::WRL::ComPtr<ID3D12Resource> textureResource_[2];

	uint32_t descriptorSizeSRV_;
	uint32_t descriptorSizeRTV_;
	uint32_t descriptorSizeDSV_;

	IDxcBlob* CompileShader(
		const std::wstring& filePath,
		const wchar_t* profile,
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);

	void InitializeDxcCompiler();
	void InitializePSO();

	void CreateRootSignature();
	void CreateInputlayOut();

	void SettingBlendState();
	void SettingRasterizerState();

	void SettingViewPort();
	void SettingScissor();

	void SettingDepth();

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages, uint32_t index);

	DirectX::ScratchImage LoadTexture(const std::string& filePath);
};