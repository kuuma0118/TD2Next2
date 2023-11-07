#pragma once
#include "../Blossom Engine/Math/MatrixCalculate.h"

class BaseParticle {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="translation"></param>
	/// <param name="rotation"></param>
	/// <param name="scale"></param>
	/// <param name="velocity"></param>
	/// <param name="color"></param>
	/// <param name="lifeTime"></param>
	virtual void Initialize(const Vector3& translation, const Vector3& rotation, const Vector3& scale, const Vector3& velocity, const Vector4& color, float lifeTime);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <returns></returns>
	virtual const Vector3& GetTranslation() { return translation_; };

	/// <summary>
	/// 角度
	/// </summary>
	/// <returns></returns>
	virtual const Vector3& GetRotation() { return rotation_; };

	/// <summary>
	/// スケール
	/// </summary>
	/// <returns></returns>
	virtual const Vector3& GetScale() { return scale_; };

	/// <summary>
	/// 色を取得
	/// </summary>
	/// <returns></returns>
	virtual const Vector4& GetColor() { return color_; };

	/// <summary>
	/// 死亡フラグを取得
	/// </summary>
	/// <returns></returns>
	virtual const bool IsDead() { return isDead_; };

protected:
	//座標
	Vector3 translation_{};
	//回転
	Vector3 rotation_{};
	//スケール
	Vector3 scale_{};
	//速度
	Vector3 velocity_{};
	//色
	Vector4 color_{};
	//寿命
	float lifeTime_ = 0.0f;
	//経過時間
	float currentTime_ = 0.0f;
	//死亡フラグ
	bool isDead_ = false;
	//アルファ値
	float alpha_ = 0.0f;

};