#include "TitleScene.h"

void TitleScene::Initialize() {
	sprite_ = new Sprite();
	sprite_->Initialize();
	sphere_ = new Sphere();
	sphere_->Initialize();
	textureNum_ = UVCHEKER;
	input_ = Input::GetInstance();
	block_ = new Block();
	block_->Initialize();
	block_->textureNum = BLOCK;
	pos_ = { 0,0,30 };

	enemy_ = new Enemy;
	enemy_->Initialize();
}

void TitleScene::Update() {

	if (input_->TriggerKey(DIK_1)) {
		enemy_->Update();
	}
	
}

void TitleScene::Draw() {
	//block_->Draw();
	enemy_->Draw();
}

void TitleScene::Finalize() {
	delete sprite_;
	delete sphere_;
	delete block_;
	delete enemy_;
}