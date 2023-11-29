#pragma once
#include <stdint.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include "../Manager/TextureManager.h"
#include <wrl.h>


class DirectXCommon
{
public:

	static DirectXCommon* GetInstance();

	~DirectXCommon();

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);

	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);

	// Getter
	Microsoft::WRL::ComPtr<ID3D12Device> GetDevice() { return this->device_.Get(); }
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandList() { return this->commandList_.Get(); }
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetSrvDescriptorHeap() { return this->srvDescriptorHeap_.Get(); }
	D3D12_RENDER_TARGET_VIEW_DESC GetRtvDesc() { return rtvDesc_; }
	DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc() { return swapChainDesc_; }

	// 使用するアダプタを決定する
	void GetAdapter();

	// D3D12Deviceの生成
	void CreateD3D12Device();

	// エラーや警告が起きると止まる
	void StopError();

	// コマンドキューの生成
	void CreateComandQueue();

	// コマンドリストの生成
	void CreateComandList();

	// SwapChainの生成
	void CreateSwapChain(HWND hwnd);

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);

	// DescriptorHeapの生成
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(const Microsoft::WRL::ComPtr<ID3D12Device>& device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	// 二つのswapChainResoucesを取得
	void GetSwapChainResources();

	// RTVを作る
	void CreateRTV();

	// メインループ前の初期化
	void Initialize(HWND hwnd);

	// 描画前の処理
	void PreDraw(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& dsvDescriptorHeap);

	// 描画後の処理
	void PostDraw();

	// 解放処理とリソースチェック
	void Release();

	/// <summary>
    /// ディスクリプタヒープを設定
    /// </summary>
	void SetGraphicsDescriptorHeap();

	/// <summary>
	/// ディスクリプタテーブルを設定
	/// </summary>
	/// <param name="rootParameterIndex">ルートパラメータの番号</param>
	/// <param name="textureHandle">テクスチャ番号</param>
	void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t textureHandle);

	/// <summary>
	/// デバイスの取得
	/// </summary>
	/// <returns></returns>
	ID3D12Device* GetDevice() const { return device_.Get(); };

private:
	/// <summary>
	/// DXGIデバイスの作成
	/// </summary>
	void CreateDXGIDevice();

	/// <summary>
	/// コマンド関連の作成
	/// </summary>
	void CreateCommand();

	/// <summary>
	/// スワップチェーンの作成
	/// </summary>
	void CreateSwapChain();

	/// <summary>
	/// レンダーターゲットビューの作成
	/// </summary>
	void CreateRenderTargetView();

	/// <summary>
	/// DepthStencilViewの作成
	/// </summary>
	void CreateDepthStencilView();

	/// <summary>
	/// フェンスの作成
	/// </summary>
	void CreateFence();

	/// <summary>
	/// DepthStencilTextureの作成
	/// </summary>
	/// <param name="width">幅</param>
	/// <param name="height">高さ</param>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateDepthStencilTextureResource(int32_t width, int32_t height);

	/// <summary>
	/// FPS固定初期化
	/// </summary>
	void InitializeFixFPS();

	/// <summary>
	/// FPS固定更新
	/// </summary>
	void UpdateFixFPS();


private:
	UINT backBufferIndex_;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter_;
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue_;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_;
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap_;
	Microsoft::WRL::ComPtr<ID3D12Resource> swapChainResources_[2];
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2];
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_;
	uint64_t fenceValue_;
	HANDLE fenceEvent_;
	D3D12_RESOURCE_BARRIER barrier_;


	//記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference_{};
};