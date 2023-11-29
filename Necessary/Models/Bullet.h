#pragma once
#include <d3d12.h>
#include "../ImGui/ImGuiManager.h"
#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Blossom Engine/utility/GlobalVariables.h"
#include "../Blossom Engine/components/camera/Camera.h"
#include "../Manager/ObjManager.h"
#include "../Blossom Engine/Math/Matrix4x4.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"
#include "../Manager/TextureManager.h"
#include "../Blossom Engine/Common/Common.h"
#include "../Blossom Engine/utility/Collision/Collider.h"
class Bullet :
	public Collider
{
public: // メンバ関数

	ModelData GetModelData() { return modelData_; }

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(const Microsoft::WRL::ComPtr<ID3D12Device>& device, size_t sizeInBytes);

	void CreateVertexResource();

	void CreateVertexBufferView();

	void CreateMaterialResource();

	void CreateWvpResource();

	void Initialize();	// 初期化
	void Update();	// 更新

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="textureNum">textureManagerで作ったenum型の番号</param>
	void Draw();	// 描画

	void SetVelotity(Vector3 velotity) { velotity_ = velotity; }
	Vector3 GetWorldPosition()override;


public:
	// SRT
	Transform transform;
	Vector3 velotity_;
	float speed;
	float angle;
	float rotationAngle;
	float rotateAmount;
	float trueangle;
	float x = transform.translate.x;
	float y = transform.translate.y;
	bool isBulletDeth;
	float time;
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
	ModelData modelData_;
	// ワールドトランスフォーム
	//WorldTransform worldTransform_;

};


