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

	WorldTransform& GetWeaponWorldTransform() { return weaponWorldTransform_; }

	bool GetIsCharge() { return IsCharge_; }

	bool GetIsAttack() { return IsAttack_; }

	bool GetIsHit() { return IsHit_; };

	bool GetIsCoolDown() {
		return IsCoolDown_;
	};

	int GetHP() { return Hp_; };

	void DrawSprite();

	void DrawParticle(const ViewProjection& viewProjection);

	void StartAnimation();

	void GetBossIsDead(bool IsDeadAnimation) { IsDeadAnimation_ = IsDeadAnimation; };

private:
	Input* input_ = nullptr;

	XINPUT_STATE joyState_;

	std::unique_ptr<Model> weaponModelDummy_ = nullptr;

	std::unique_ptr<Model> weaponModel_ = nullptr;
	std::unique_ptr<Model> weaponRodModel_ = nullptr;
	std::unique_ptr<Model> involvedMissile_ = nullptr;

	WorldTransform weaponWorldTransform_;
	WorldTransform involvedMissileWorldTransform_;

	uint32_t textureHandle_ = 0u;

	uint32_t soundHandle_[4] = {};

	//武器の横移動スピード
	float weaponMoveSpeed_ = 0.05f;

	//チャージ時のスピード
	float chargeSpeed_ = 0.05f;

	//攻撃時のスピード
	float attackSpeed_[4] = { 0.03f ,0.085f ,0.15f , 0.2f };

	//クールダウン中のスピード
	float coolDownSpeed_ = 0.4f;

	//チャージ時のカウント
	int chargeCount_ = 0;

	//キーを押しているときのカウント
	int pushCount_ = 0;

	//クールダウン中のタイマー
	int coolDownTimer_ = 30;

	bool IsNormal_ = true;
	bool IsCharge_ = false;
	bool IsAttack_ = false;
	bool IsCoolDown_ = false;

	bool IsHit_ = false;

	//体力
	static const  int MaxHp_ = 3;
	int Hp_;

	//無敵時間
	bool invincibleFlag_ = false;
	int invincibleTimer_ = 0;

	//攻撃時のダメージ
	float attackDamage_[4] = { 1.0f,2.0f,3.0f,4.0f };

	//ミサイルを巻き込んでいるか
	bool isInvolvedMissile_ = false;
	int involvedCount_ = 0;
	float missileDamage = 7.0f;
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

