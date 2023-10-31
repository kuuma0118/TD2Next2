#pragma once
#include <d3d12.h>
#include "../ImGui/ImGuiManager.h"
#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Blossom Engine/utility/GlobalVariables.h"
#include "../components/camera/Camera.h"
#include "../Manager/ObjManager.h"
#include "../Blossom Engine/Math/Matrix4x4.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"
#include "../Manager/TextureManager.h"
#include "../Common/Common.h"

class Model {
public: // メンバ関数
	ModelData GetModelData() { return modelDate_; }

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(const Microsoft::WRL::ComPtr<ID3D12Device>& device, size_t sizeInBytes);

	void CreateVertexResource();

	void CreateVertexBufferView();

	void CreateMaterialResource();

	void CreateWvpResource();

	void Initialize();	// 初期化
	//void Update();	// 更新

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="textureNum">textureManagerで作ったenum型の番号</param>
	void Draw();	// 描画

public:
	// SRT
	Transform transform;

	// テクスチャナンバー
	int textureNum;

private: // メンバ変数
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
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;
	Matrix4x4 worldViewProjectionMatrix_;

	// モデルのポインタ
	ModelData modelDate_;
	// ワールドトランスフォーム
	//WorldTransform worldTransform_;
};