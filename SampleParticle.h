#pragma once
#include "Blossom Engine/Model/Model.h"
#include "Blossom Engine/Math/MatrixCalculate.h"
#include "Blossom Engine/Math/WorldTransform.h"
#include "ImGui/ImGuiManager.h"
#include "Blossom Engine/utility/Collision/Collider.h"
#include "Blossom Engine/components/Input/Input.h"
#include "Blossom Engine/Model/ParticleModel.h"
#include "Necessary/Effect/Particle/ParticleSystem.h"
#include "Necessary/UI/UI.h"

class Sample : public Collider
{
public:

	~Sample();

	static int InvincibleTime;

	void Initialize();

	void Update();

	void Draw(const ViewProjection viewProjection);

	void ApplyGlobalVariables();

	void OnCollision(uint32_t collisionAttribute, float damage);

	int GetInvolvedMissileCount() { return involvedCount_; };

	Vector3 GetWorldPosition() override;


	void ModelMotion();

	WorldTransform& GetsampleWorldTransform() { return sampleWorldTransform_; }

	bool GetIsHit() { return IsHit_; };

	int GetHP() { return Hp_; };

	void DrawSprite();

	void DrawParticle(const ViewProjection& viewProjection);

	void StartAnimation();

	void GetBossIsDead(bool IsDeadAnimation) { IsDeadAnimation_ = IsDeadAnimation; };

private:
	Input* input_ = nullptr;

	XINPUT_STATE joyState_;

	WorldTransform sampleWorldTransform_;
	WorldTransform involvedMissileWorldTransform_;

	uint32_t textureHandle_ = 0u;

	//キーを押しているときのカウント
	int pushCount_ = 0;

	//クールダウン中のタイマー
	int coolDownTimer_ = 30;

	bool IsHit_ = false;

	//体力
	static const  int MaxHp_ = 3;
	int Hp_;

	//無敵時間
	bool invincibleFlag_ = false;
	int invincibleTimer_ = 0;

	//ミサイルを巻き込んでいるか
	bool isInvolvedMissile_ = false;
	int involvedCount_ = 0;

	Vector4 missileColor_[5]{
		{1.0f,1.0f,1.0f,1.0f},
		{1.0f,0.5f,0.5f,1.0f},
		{1.0f,0.0f,0.0f,1.0f},
		{0.5f,0.0f,0.0f,1.0f},
		{0.0f,0.0f,0.0f,1.0f},
	};

	//ダメージ赤のスプライト
	std::unique_ptr<Sprite> redSprite_;
	//ダメージ赤のテクスチャ
	uint32_t  redTextureHandle_ = 0;

	bool damageRed = false;

	//モデルとモーション
	enum {
		Stay,
		Charge,
		Attack,
	};

	int  motionMode_;

	WorldTransform weaponMotionWorldTransform_;
	WorldTransform weaponRodMotionWorldTransform_;

	struct weaponMotionStruct {
		Vector3 translation_; /*weaponWorldTransform_.translation_を基準としたLocal座標*/
		Vector3 rotation_;/*weaponWorldTransform_.rotation_を基準としたLocal回転*/
		Vector3 scale_;/*weaponWorldTransform_.scale_を基準としたLocalスケール*/
		Vector4 color_;/*色やんね*/

		Vector3 normalTransration_;//そもそものサイズ
		Vector3 normalScale_;		//そもそもの位置
	};


	float chargeRotateSpeed_;
	float attackRotateSpeed_[4];

	float playerPosY = -3.3f;

	weaponMotionStruct weaponMotion_;
	weaponMotionStruct weaponRodMotion_;

	//UI
	UIStruct heartUI_[MaxHp_];

	//パーティクル
	std::unique_ptr<ParticleModel> particleModel_ = nullptr;
	std::unique_ptr<ParticleSystem> particleSystem_ = nullptr;

	bool animationFlag_ = true;

	bool IsDeadAnimation_ = false;

};

