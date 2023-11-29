#include "TitleScene.h"

void TitleScene::Initialize() {
	sprite_ = new Sprite();
	sprite_->Initialize();
	textureNum_ = TITLE;
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
	pos_ = { 0,0,2000};
}

void TitleScene::Update() {
	sprite_->ImGuiAdjustParameter();
	if (input_->TriggerKey(DIK_SPACE)) {
		sceneNum = GAME_SCENE;
	}
}

void TitleScene::Draw() {
	sprite_->Draw(pos_,textureNum_);
	upsidetank_->Draw();
	downsidetank_->Draw();
}

void TitleScene::Finalize() {
	delete sprite_;
	delete block_;
	delete upsidetank_;
	delete downsidetank_;
}