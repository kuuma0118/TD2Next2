#include "GameClear.h"
#include "../Manager/GameManager.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"

void GameClear::Initialize() {
	/*camera_ = DebugCamera::GetInstance();
	camera_->Initialize();
	camera_->SetRotationCenterPosition();
	map_ = MapManager::GetInstance()->GetCurrentMap();*/
	sprite_ = new Sprite();
	sprite_->Initialize();
	textureNum_ = GAMECLEAR;
	pos_ = { 0,0,2000 };
	bool isWKeyPressed = false;
}

void GameClear::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {
		sceneNum = TITLE_SCENE;
	}
}

void GameClear::Draw() {
	//map_->Draw();
	sprite_->Draw(pos_, textureNum_);
}

void GameClear::Finalize() {
	delete sprite_;
}