#pragma once
#include "../Blossom Engine/Math/Matrix4x4.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"
#include <d3d12.h>
#include "../Manager/TextureManager.h"
#include "../Common/Common.h"
#include "../components/camera/Camera.h"

class Sphere
{
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(const Microsoft::WRL::ComPtr<ID3D12Device>& device, size_t sizeInBytes);

	void CreateVertexResource();

	void CreateVertexBufferView();

	void CreateMaterialResource();

	void CreateWvpResource();

	~Sphere();

	void Initialize();

	void Draw();

	void Release();


	void ImGuiAdjustParameter();

public:
	// Material
	Material* materialData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	Transform uvTransform_;
	Matrix4x4 uvTransformMatrix_;
	// Vertex
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;
	VertexData* vertexData_;
	// カメラ
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationMatrixResource_;
	TransformationMatrix* transformationMatrixData_;
	Transform transform_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;
	Matrix4x4 worldViewProjectionMatrix_;
	//分割数
	const uint32_t kSubdivision = 16;
	// 頂点数
	uint32_t vertexIndex = kSubdivision * kSubdivision * 6;

	// Sphereの画像切り替え
	bool useMonsterBall_ = true;
};