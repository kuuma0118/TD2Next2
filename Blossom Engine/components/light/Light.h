#pragma once
#include "../Blossom Engine/Math/MatrixCalculate.h"
#include <d3d12.h>
#include <wrl.h>

class Light
{
public:
	static Light* GetInstance();

	Microsoft::WRL::ComPtr<ID3D12Resource> GetDirectionalLightResource() { return directionalLightResource_.Get(); }
	void SetDirectionalLightResource(const Microsoft::WRL::ComPtr<ID3D12Resource>& directionalLightResource) { directionalLightResource_ = directionalLightResource.Get(); }

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(const Microsoft::WRL::ComPtr<ID3D12Device>& device, size_t sizeInBytes);

	void CreateDirectionalResource(const Microsoft::WRL::ComPtr<ID3D12Device>& device);

	~Light();

	void Initialize(const Microsoft::WRL::ComPtr<ID3D12Device>& device);

	void ImGuiAdjustParameter();

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource_;
	DirectionalLight* directionalLightData_;
};

