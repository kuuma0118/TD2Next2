#include "GameScene.h"
#include "../Manager/GameManager.h"

void GameScene::Initialize() {
	camera_ = DebugCamera::GetInstance();
	camera_->Initialize();
	camera_->SetRotationCenterPosition();

	sceneNum = GAME_SCENE;

	map_ = MapManager::GetInstance()->GetCurrentMap();
}

void GameScene::Update() {

	ImGui::Begin("GameScene Debug");
	ImGui::SliderInt("loadStageLevel", &loadStageNum_, 0, 7);
	ImGui::End();

	map_->Update();

}


void GameScene::Draw() {
	map_->Draw();
}

void GameScene::Finalize() {

}