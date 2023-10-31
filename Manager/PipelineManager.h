#pragma once
#include "../Blossom Engine/WinApp/WinApp.h"
#include "../Blossom Engine/Common/Common.h"
#include "../Blossom Engine/Sys/Sys.h"
#include "../ImGui/ImGuiManager.h"
#include "../Manager/TextureManager.h"
#include "../Blossom Engine/components/light/Light.h"
#include "../Blossom Engine/Sphere/Sphere.h"
#include "../Blossom Engine/Sprite/Sprite.h"
//#include "../object/Plane.h"

class BlossomEngine {
public:
	// DXCの初期化
	void DXCInitialize();

	// シェーダのコンパイル
	IDxcBlob* CompileShader(
		// CompilerするShaderファイルへのパス
		const std::wstring& filePath,
		// Compilerに使用するProfile
		const wchar_t* profile,
		// 初期化で生成したものを3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);

	// DescriptorRangeの生成
	void CreateDescriptorRange();

	// DescriptorTableの生成
	void CraeteDescriptorTable();

	// Samplerの設定
	void SettingSampler();

	// RootSignatureの生成
	void CreateRootSignature();

	// RootParameter生成
	void CreateRootParameter();

	// InputLayerの設定
	void SettingInputLayout();

	// BlendStateの設定
	void SettingBlendState();

	// RasterizerStateの設定
	void SettingRasterizerState();

	// ピクセルシェーダー
	void PixelSharder();

	// 頂点シェーダー
	void VertexSharder();

	// PSOの生成
	void CreatePSO();

	// PSO
	void PSO();

	// ビューポート
	void CreateViewport();

	// シザー矩形
	void CreateScissor();

	~BlossomEngine() = default;

	// エンジンの初期化
	void Initialize();

	// 描画前の処理
	void BeginFrame();

	// 描画後の処理
	void EndFrame();

private:
	IDxcUtils* dxcUtils_;
	IDxcCompiler3* dxcCompiler_;
	IDxcIncludeHandler* includeHandler_;
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature_;
	ID3DBlob* signatureBlob_;
	ID3DBlob* errorBlob_;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;
	D3D12_INPUT_ELEMENT_DESC inputElementDescs_[3];
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc_;
	D3D12_BLEND_DESC blendDesc_;
	D3D12_RASTERIZER_DESC rasterizerDesc_;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDescs_;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState_;
	IDxcBlob* vertexShaderBlob_;
	IDxcBlob* pixelShaderBlob_;

	D3D12_VIEWPORT viewport_;
	D3D12_RECT scissorRect_;
	D3D12_ROOT_PARAMETER rootParameters_[4];
	D3D12_DESCRIPTOR_RANGE descriptorRange_[1];
	D3D12_STATIC_SAMPLER_DESC staticSamplers_[1];
};
