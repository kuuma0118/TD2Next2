#pragma once
#include "../Blossom Engine/Math/Vector3.h"
#include "../Blossom Engine/Math/Matrix4x4.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"

class DebugCamera
{
public:
	static DebugCamera* GetInstance();

	void Initialize();

	void Update();

	void SetRotationCenterPosition();

	// 回転のオフセット
	Vector3 offset_;
	// 中心からの回転
	Vector3 offsetRotation_;

	// カメラの回転角を求める関数
	Vector3 GetCameraRotation() { return rotation_; }

	Matrix4x4 GetViewMatrix() { return viewMatrix_; }

private: // メンバ定数
	const float kCameraTurnSpeed = 0.07f;
	const float kCameraZoomSpeed = 0.5f;

private: // メンバ変数
	// 回転中心座標
	Vector3 rotationCenterPosition_;

	// x,y,z軸周りのローカル回転角
	Vector3 rotation_;
	// 累積回転行列
	Matrix4x4 matRot_;

	// ローカル座標
	Vector3 translation_;
	// ワールド座標
	Matrix4x4 worldTransform_;
	// ビュー行列
	Matrix4x4 viewMatrix_;
	// 射影行列
	Matrix4x4 orthographicMatrix_;

private: // プライベートな関数
	// コントローラーでの操作
	void InputController();
	// キーボードでの操作
	void InputKeyboard();
};

