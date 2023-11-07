#include "ParticleBase.h"

void BaseParticle::Initialize(const Vector3& translation, const Vector3& rotation, const Vector3& scale, const Vector3& velocity, const Vector4& color, float lifeTime) {
	//座標の初期化
	translation_ = translation;
	//角度の初期化
	rotation_ = rotation;
	//スケール
	scale_ = scale;
	//速度
	velocity_ = velocity;
	//色
	color_ = color;
	//寿命
	lifeTime_ = lifeTime;
	//アルファ値の初期化
	alpha_ = color_.w;
}

void BaseParticle::Update() {
	//移動処理
	translation_ = V3Add(translation_, velocity_);
	//寿命を減らす
	const float kDeltaTime = 1.0f / 60.0f;
	currentTime_ += kDeltaTime;
	color_.w = alpha_ - (currentTime_ / lifeTime_);
	//寿命が生存時間を上回ったら消す
	if (lifeTime_ < currentTime_) {
		isDead_ = true;
	}
}