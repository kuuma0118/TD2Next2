#include "GameOver.h"
#include "../Manager/GameManager.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"

void GameOver::Initialize() {
	/*camera_ = DebugCamera::GetInstance();
	camera_->Initialize();
	camera_->SetRotationCenterPosition();
	map_ = MapManager::GetInstance()->GetCurrentMap();*/
	sprite_ = new Sprite();
	sprite_->Initialize();
	textureNum_ = GAMEOVER;
	pos_ = { 0,0,30 };
	bool isWKeyPressed = false;
}

void GameOver::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {
		sceneNum = TITLE_SCENE;
	}
}

void GameOver::Draw() {
	//map_->Draw();
	sprite_->Draw(pos_, textureNum_);
}

void GameOver::Finalize() {
	delete sprite_;
}