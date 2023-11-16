#include "SampleParticle.h"
#include <Math.h>
#include "Blossom Engine/Math/MatrixCalculate.h"6/.

//実体定義
int Sample::InvincibleTime = 60;

Sample::~Sample()
{
	for (int i = 0; i < MaxHp_; i++) {
		delete heartUI_[i].sprite_;
	}
}

void Sample::Initialize()
{

	input_ = Input::GetInstance();

	ModelMotion();



}

void Sample::Update()
{

	XINPUT_STATE  joyState_;
	Vector3 move = { 0, 0, 0 };

	if (!Input::GetInstance()->GetJoystickState(0, joyState_))
	{
		return;
	}

	ModelMotion();

	//パーティクルの更新
	particleSystem_->Update();

	Sample::ApplyGlobalVariables();

}

void Sample::Draw(const ViewProjection view)
{

}

void Sample::DrawParticle(const ViewProjection& viewProjection) {
	//パーティクルの描画
	particleModel_->Draw(particleSystem_.get(), viewProjection);
}

void Sample::ApplyGlobalVariables()
{

}

void Sample::OnCollision(uint32_t collisionAttribute, float damage)
{
	
}

Vector3 Sample::GetWorldPosition()
{
	Vector3 pos;
	pos.x = weaponWorldTransform_.matWorld_.m[3][0];
	pos.y = weaponWorldTransform_.matWorld_.m[3][1];
	pos.z = weaponWorldTransform_.matWorld_.m[3][2];
	return pos;
}

void Sample::ModelMotion()
{

}

void Sample::DrawSprite()
{

}

void Sample::StartAnimation()
{

}

