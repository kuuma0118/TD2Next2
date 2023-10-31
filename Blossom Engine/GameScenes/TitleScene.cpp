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
}

void TitleScene::Update() {

}

void TitleScene::Draw() {
	block_->Draw();
}

void TitleScene::Finalize() {
	delete sprite_;
	delete sphere_;
	delete block_;
}