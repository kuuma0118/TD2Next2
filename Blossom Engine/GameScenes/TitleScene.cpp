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
	upsidetank_ = new UpsideTank();
	upsidetank_->Initialize();
	upsidetank_->textureNum = UPSIDETANK;
	downsidetank_ = new DownsideTank();
	downsidetank_->Initialize();
	downsidetank_->textureNum = DOWNSIDETANK;
	pos_ = { 0,0,30 };
	debugcamera_ = new DebugCamera();
}

void TitleScene::Update() {
	if (input_->PressKey(DIK_W)) {
		debugcamera_->translation_.z += 3.00f;
	}
	if (input_->TriggerKey(DIK_SPACE)) {
		sceneNum = GAME_SCENE;
	}
}

void TitleScene::Draw() {
	//block_->Draw();
	upsidetank_->Draw();
	downsidetank_->Draw();
}

void TitleScene::Finalize() {
	delete sprite_;
	delete sphere_;
	delete block_;
	delete upsidetank_;
	delete downsidetank_;
	delete debugcamera_;
}