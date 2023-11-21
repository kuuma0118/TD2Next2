#include "TitleScene.h"

void TitleScene::Initialize() {

	input_ = Input::GetInstance();
	block_ = new Block();
	block_->Initialize();
	block_->textureNum = BLOCK;
	pos_ = { 0,0,30 };
};

void TitleScene::Update() {

};

void TitleScene::Draw() {
	block_->Draw();

#pragma region パーティクルの描画

	//パーティクルモデルの描画
	ParticleModel::PreDraw();

	sample_->DrawParticle(viewProjection_);

	ParticleModel::PostDraw();

#pragma endregion
};

void TitleScene::Finalize() {

	delete sphere_;
	delete block_;
};
