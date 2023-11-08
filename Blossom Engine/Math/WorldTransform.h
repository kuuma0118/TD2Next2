#pragma once
#include "MatrixCalculate.h"

/// <summary>
/// ワールドトランスフォーム
/// </summary>
struct WorldTransform {

	/// <summary>
	/// 行列の計算
	/// </summary>
	void UpdateMatrix();

	//スケール
	Vector3 scale_ = { 1.0f,1.0f,1.0f };
	//角度
	Vector3 rotation_ = { 0.0f,0.0f,0.0f };
	//座標
	Vector3 translation_ = { 0.0f,0.0f,0.0f };
	//ワールド行列
	Matrix4x4 matWorld_{};
	//親となるワールド変換へのポインタ
	const WorldTransform* parent_ = nullptr;

};