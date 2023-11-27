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
	mapChip_ = new MapChip;
	mapChip_->Initialize();
	mapChip_->LoadMapData(2);
	mapChip_->SetNextMapData();
}

void TitleScene::Update() {
	if(input_->TriggerKey(DIK_SPACE)){
		sceneNum = GAME_SCENE;
	}
	mapChip_->Update();
}

void TitleScene::Draw() {
	//block_->Draw();
	mapChip_->Draw();
}

void TitleScene::Finalize() {
	delete sprite_;
	delete sphere_;
	delete block_;
}