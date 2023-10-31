#pragma once
#include "../externals/DirectXTex/d3dx12.h"
#include "../externals/DirectXTex/DirectXTex.h"
#include <string>

#include "../Blossom Engine/Math/MatrixCalculate.h"
#include "../Blossom Engine/Math/Matrix4x4.h"
#include <d3d12.h>
#include "../Blossom Engine/components/light/Light.h"
#include "../Blossom Engine/utility/MaterialData.h"
#include <wrl.h>
#include "../Blossom Engine/Common/Common.h"

enum TextureName {
	UVCHEKER,
	MONSTERBALL,
	BLOCK
};

class TextureManager
{
public:
	static TextureManager* GetInstance();

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);
	// Getter
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDsvDescriptorHeap() { return dsvDescriptorHeap_.Get(); }
	Microsoft::WRL::ComPtr<ID3D12Resource> GetDepthStencilResource() { return depthStencilResource_.Get(); }
	D3D12_DEPTH_STENCIL_DESC GetDepthStencilDesc() { return depthStencilDesc_; }
	D3D12_GPU_DESCRIPTOR_HANDLE* GetTextureSrvHandleGPU() { return textureSrvHandleGPU_; }

	// COMの初期化
	void ComInit();

	// Textureを読む
	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	// DirectX12のTextureResourceを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(const DirectX::TexMetadata& metadata);

	// 中間リソースの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(const Microsoft::WRL::ComPtr<ID3D12Device>& device, size_t sizeInBytes);

	// TextureResourceにデータを転送する
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadTextureData(const Microsoft::WRL::ComPtr<ID3D12Resource>& texture, const DirectX::ScratchImage& mipImages);

	// DepthStenciltextureの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateDepthStencilTextureResource(int32_t width, int32_t height);

	// dsvDescriptorHeapの生成
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDsvDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	// CPUで書き込む用のTextureResourceを作りコマンドを積む
	void CreateDepthStencilView();

	// DepthStencilStateの設定
	void SettingDepthStencilState();

	// textureを読んで転送する
	void TransferTexture(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& srvDescriptorHeap);

	~TextureManager();

	// スプライトの初期化
	void Initialize();

	// 解放処理
	void Release();

	// COMの終了処理
	void ComUninit();
public:
	// [0]はSpriteに使用しているuvChecker.png(textureSrvHandleGPUは三角形にも使用)[1]はSphereに使用しているmonsterBall.png
	static const uint32_t kMaxImages = 3;
	DirectX::ScratchImage mipImages_[kMaxImages];
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_[kMaxImages];
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_[kMaxImages];
	Microsoft::WRL::ComPtr<ID3D12Resource> textureResource_[kMaxImages];
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource_[kMaxImages];
	// Depth
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc_;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilResource_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap_;

	// objデータ
	static const int32_t kMaxObjModelData = 2;
	ModelData* modelData_;
};
