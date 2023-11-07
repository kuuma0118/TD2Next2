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
	stage_ = new Stage();
	stage_->Initialize();
	stage_->textureNum = STAGETEXTURE;
	pos_ = { 0,0,30 };
}

void GameScene::Update() {

	/*ImGui::Begin("GameScene Debug");
	ImGui::SliderInt("loadStageLevel", &loadStageNum_, 0, 7);
	ImGui::End();

	map_->Update();*/

}

void GameScene::Draw() {
	ObjManager::GetInstance()->GetObjModelData()[stage];
	//map_->Draw();
	stage_->Draw();
	//sprite_->Draw(pos_, UVCHEKER);
}

void GameScene::Finalize() {
	delete sprite_;
	delete sphere_;
	delete stage_;
}