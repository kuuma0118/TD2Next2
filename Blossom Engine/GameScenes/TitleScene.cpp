#include "TitleScene.h"


void TitleScene::Initialize() {

	//TextureManagerのインスタンスを取得
	textureManager_ = TextureManager::GetInstance();
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera();
	//衝突マネージャーの生成
	collisionManager_ = std::make_unique<CollisionManager>();
	input_ = Input::GetInstance();
	block_ = new Block();
	block_->Initialize();
	block_->textureNum = BLOCK;
	pos_ = { 0,0,30 };

	sample_ = std::make_unique<Sample>();

	sample_->Initialize();

	viewProjection_.UpdateMatrix();
};

void TitleScene::Update() {
	sample_->Update();
	//デバッグカメラの更新
	debugCamera_->Update();
	//デバッグカメラの切り替え
	if (input_->TriggerKey(DIK_1)) {
		if (isDebugCameraActive_ == false) {
			isDebugCameraActive_ = true;
		}
		else {
			isDebugCameraActive_ = false;
		}
	}
	viewProjection_.UpdateMatrix();
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
