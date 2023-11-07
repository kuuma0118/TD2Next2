#include "ParticleEmitter.h"
#include <numbers>

void ParticleEmitter::Update() {
	//パーティクルを生成
	const float kDeltaTime = 1.0f / 60.0f;
	frequencyTime_ += kDeltaTime;
	if (popFrequency_ <= frequencyTime_) {
		for (uint32_t index = 0; index < popCount_; ++index) {
			ParticleEmitter::Pop();
		}
		frequencyTime_ -= popFrequency_;
	}

	//パーティクルの更新
	for (std::list<std::unique_ptr<BaseParticle>>::iterator particleIterator = particles_.begin(); particleIterator != particles_.end(); ++particleIterator) {
		particleIterator->get()->Update();
	}

	//エミッターの死亡フラグを立てる
	deleteTimer_ += kDeltaTime;
	if (deleteTimer_ > deleteTime_) {
		isDead_ = true;
	}
}


void ParticleEmitter::Pop() {
	//座標
	Vector3 translation = {
		popTranslation_.x + Random::GetRandomFloat(popArea_.min.x,popArea_.max.x),
		popTranslation_.y + Random::GetRandomFloat(popArea_.min.y,popArea_.max.y),
		popTranslation_.z + Random::GetRandomFloat(popArea_.min.z,popArea_.max.z)
	};

	//回転
	Vector3 rotation = {
		Random::GetRandomFloat(popRotation_.min.x,popRotation_.max.x),
		Random::GetRandomFloat(popRotation_.min.y,popRotation_.max.y),
		Random::GetRandomFloat(popRotation_.min.z,popRotation_.max.z)
	};

	//スケール
	Vector3 scale = {
		Random::GetRandomFloat(popScale_.min.x,popScale_.max.x),
		Random::GetRandomFloat(popScale_.min.y,popScale_.max.y),
		Random::GetRandomFloat(popScale_.min.z,popScale_.max.z)
	};

	//方位角
	float azimuth = { Random::GetRandomFloat(popAzimuth.min,popAzimuth.max) };
	float azimuthRadian = azimuth * float(std::numbers::pi / 180.0f);

	//仰角
	float elevation = { Random::GetRandomFloat(popElevation.min,popElevation.max) };
	float elevationRadian = elevation * float(std::numbers::pi / 180.0f);

	//速度
	Vector3 velocity = {
		Random::GetRandomFloat(popVelocity_.min.x,popVelocity_.max.x) * std::cos(elevationRadian) * std::cos(azimuthRadian),
		Random::GetRandomFloat(popVelocity_.min.y,popVelocity_.max.y) * std::cos(elevationRadian) * std::sin(azimuthRadian),
		Random::GetRandomFloat(popVelocity_.min.z,popVelocity_.max.z) * std::sin(elevationRadian)
	};

	//色
	Vector4 color = {
		Random::GetRandomFloat(popColor_.min.x,popColor_.max.x),
		Random::GetRandomFloat(popColor_.min.y,popColor_.max.y),
		Random::GetRandomFloat(popColor_.min.z,popColor_.max.z),
		Random::GetRandomFloat(popColor_.min.w,popColor_.max.w)
	};

	//寿命
	float lifeTime = Random::GetRandomFloat(popLifeTime_.min, popLifeTime_.max);

	//パーティクルの生成
	BaseParticle* particle = nullptr;
	switch (particleType_) {
	case ParticleType::kNormal:
		particle = new BaseParticle();
		particle->Initialize(translation, rotation, scale, velocity, color, lifeTime);
		break;
	}
	//パーティクルをリストに追加
	particles_.push_back(std::unique_ptr<BaseParticle>(particle));
}