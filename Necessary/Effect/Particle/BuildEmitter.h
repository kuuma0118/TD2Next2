#pragma once
#include "ParticleEmitter.h"

class EmitterBuilder {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EmitterBuilder();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EmitterBuilder();

	/// <summary>
	/// エミッターの名前を設定
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	EmitterBuilder& SetEmitterName(const std::string& name);

	/// <summary>
	/// パーティクルの種類を設定
	/// </summary>
	/// <param name="particleType"></param>
	/// <returns></returns>
	EmitterBuilder& SetParticleType(ParticleEmitter::ParticleType particleType);

	/// <summary>
	/// パーティクルの位置を設定
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	EmitterBuilder& SetTranslation(const Vector3& translation);

	/// <summary>
	/// 発生範囲を設定
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	EmitterBuilder& SetArea(const Vector3& min, const Vector3& max);

	/// <summary>
	/// パーティクルの角度を設定
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	EmitterBuilder& SetRotation(const Vector3& min, const Vector3& max);

	/// <summary>
	/// パーティクルのスケールを設定
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	EmitterBuilder& SetScale(const Vector3& min, const Vector3& max);

	/// <summary>
	/// パーティクルの方位角を設定
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	EmitterBuilder& SetAzimuth(float min, float max);

	/// <summary>
	/// パーティクルの仰角を設定
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	EmitterBuilder& SetElevation(float min, float max);

	/// <summary>
	/// パーティクルの初速度を設定
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	EmitterBuilder& SetVelocity(const Vector3& min, const Vector3& max);

	/// <summary>
	/// パーティクルの色を設定
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	EmitterBuilder& SetColor(const Vector4& min, const Vector4& max);

	/// <summary>
	/// パーティクルの寿命を設定
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	EmitterBuilder& SetLifeTime(float min, float max);

	/// <summary>
	/// 一度に発生する数
	/// </summary>
	/// <param name="count"></param>
	/// <returns></returns>
	EmitterBuilder& SetCount(uint32_t count);

	/// <summary>
	/// 発生頻度
	/// </summary>
	/// <param name="frequency"></param>
	/// <returns></returns>
	EmitterBuilder& SetFrequency(float frequency);

	/// <summary>
	/// エミッターの寿命を設定
	/// </summary>
	/// <param name="frequency"></param>
	/// <returns></returns>
	EmitterBuilder& SetDeleteTime(float deleteTime);

	/// <summary>
	/// エミッターを作成
	/// </summary>
	/// <returns></returns>
	ParticleEmitter* Build();

private:
	//エミッター
	ParticleEmitter* particleEmitter_ = nullptr;

};

