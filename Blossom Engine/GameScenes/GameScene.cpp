#include "GameScene.h"
#include "../Manager/GameManager.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"

void GameScene::Initialize() {
	/*camera_ = DebugCamera::GetInstance();
	camera_->Initialize();
	camera_->SetRotationCenterPosition();
	map_ = MapManager::GetInstance()->GetCurrentMap();*/
	sprite_ = new Sprite();
	sprite_->Initialize();
	sphere_ = new Sphere();
	sphere_->Initialize();
	textureNum_ = UVCHEKER;
	input_ = Input::GetInstance();
	//stage
	stage_ = new Stage();
	stage_->Initialize();
	stage_->textureNum = STAGETEXTURE;
	//tank
	upsidetank_ = new UpsideTank();
	upsidetank_->Initialize();
	upsidetank_->textureNum = UPSIDETANK;
	downsidetank_ = new DownsideTank();
	downsidetank_->Initialize();
	downsidetank_->textureNum = DOWNSIDETANK;
	

	pos_ = { 0,0,30 };
	bool isWKeyPressed = false;
}

void GameScene::Update() {
	/*ImGui::Begin("GameScene Debug");
	ImGui::SliderInt("loadStageLevel", &loadStageNum_, 0, 7);
	ImGui::End();
	map_->Update();*/
	if (input_->PressKey(DIK_W)) {
		downsidetank_->transform.translate.y += 0.02f;
		downsidetank_->transform.rotate.z = 0.00f;
		upsidetank_->transform.translate.y += 0.02f;
		if (input_->PressKey(DIK_A)) {
			downsidetank_->transform.rotate.z = 0.77f;
		}
		if (input_->PressKey(DIK_D)) {
			downsidetank_->transform.rotate.z = -0.77f;

		}
	}
	if (input_->PressKey(DIK_S)) {
		downsidetank_->transform.translate.y -= 0.02f;
		downsidetank_->transform.rotate.z = 3.15f;
		upsidetank_->transform.translate.y -= 0.02f;
		if (input_->PressKey(DIK_A)) {
			downsidetank_->transform.rotate.z = 2.37f;

		}
		if (input_->PressKey(DIK_D)) {
			downsidetank_->transform.rotate.z = -2.37f;

		}
	}
	if (input_->PressKey(DIK_A)) {
		downsidetank_->transform.translate.x -= 0.02f;
		downsidetank_->transform.rotate.z = 1.55f;
		upsidetank_->transform.translate.x -= 0.02f;
		if (input_->PressKey(DIK_W)) {
			downsidetank_->transform.rotate.z = 0.77f;

		}
		if (input_->PressKey(DIK_S)) {
			downsidetank_->transform.rotate.z = 2.37f;

		}
	}
	if (input_->PressKey(DIK_D)) {

		downsidetank_->transform.translate.x += 0.02f;
		downsidetank_->transform.rotate.z = -1.55f;
		upsidetank_->transform.translate.x += 0.02f;
		if (input_->PressKey(DIK_W)) {
			downsidetank_->transform.rotate.z = -0.77f;
		}
		if (input_->PressKey(DIK_S)) {
			downsidetank_->transform.rotate.z = -2.37f;
		}
	}
	if (input_->PressKey(DIK_Q)) {
		upsidetank_->transform.rotate.z += 0.017425f;
	}
	if (input_->PressKey(DIK_E)) {
		upsidetank_->transform.rotate.z -= 0.017425f;
	}

	// プレイヤーの弾の生成処理
	if (input_->PressKey(DIK_SPACE) == 0 && input_->ReleaseKey(DIK_SPACE) != 0) {
		Bullet* newBullet = new Bullet;
		newBullet->Initialize();
		newBullet->textureNum = UVCHEKER;
		newBullet->transform.translate.x = downsidetank_->transform.translate.x;
		newBullet->transform.translate.y = downsidetank_->transform.translate.y;
		newBullet->isBulletDeth = false;// 死亡しているか

		// 弾の速度・角度の設定
		const float kBulletSpeed = 0.1f;
		Vector3 vel(0, kBulletSpeed, 0);

		// 速度ベクトルを自機の向きに合わせて回転
		vel = TransformNormal(vel, MakeAffineMatrix(downsidetank_->transform.scale,
			upsidetank_->transform.rotate, downsidetank_->transform.translate));
		newBullet->transform.rotate.z = -atan2(vel.x, vel.y);
		newBullet->SetVelotity(vel);	
		
		// 弾の登録
		playerBullets_.push_back(newBullet);

	}

	// プレイヤーの弾(複数)の更新処理
	for (Bullet* bullet : playerBullets_)
	{
		// 更新処理
		bullet->Update();
		//　時間を加算
		bullet->time += bullet->speed;

		// 弾が発射されてから一定時間立つと消滅する
		if (bullet->time >= 10.0f) {
			bullet->isBulletDeth = true;
			bullet->time = 0.0f;
		}
	}

}


void GameScene::Draw() {
	//map_->Draw();
	stage_->Draw();
	upsidetank_->Draw();
	downsidetank_->Draw();
	// プレイヤーの弾(複数)の描画処理
	for (Bullet* bullet : playerBullets_)
	{
		if (bullet->isBulletDeth == false) {
			bullet->Draw();
		}
	}

	//sprite_->Draw(pos_, UVCHEKER);
}

void GameScene::Finalize() {
	delete sprite_;
	delete sphere_;
	delete stage_;
	delete upsidetank_;
	for (Bullet* bullet : playerBullets_) {
		delete bullet;
	}
	delete downsidetank_;
}