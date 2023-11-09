#include "GameScene.h"
#include "../Manager/GameManager.h"

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
	upsidetank_->textureNum = UVCHEKER;
	downsidetank_ = new DownsideTank();
	downsidetank_->Initialize();
	downsidetank_->textureNum = UVCHEKER;
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
		upsidetank_->transform.rotate.z += 0.02f;
	}
	if (input_->PressKey(DIK_E)) {
		upsidetank_->transform.rotate.z -= 0.02f;
	}
}

void GameScene::Draw() {
	//map_->Draw();
	stage_->Draw();
	upsidetank_->Draw();
	downsidetank_->Draw();
	//sprite_->Draw(pos_, UVCHEKER);
}

void GameScene::Finalize() {
	delete sprite_;
	delete sphere_;
	delete stage_;
	delete upsidetank_;
	delete downsidetank_;
}