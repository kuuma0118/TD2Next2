#include "WorldTransform.h"

//void WorldTransform::Initialize() {
//	//CBVの作成
//	constBuff_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(ConstBuffDataWorldTransform));
//}

WorldTransform::WorldTransform() {
	//CBVの作成
	constBuff_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(ConstBuffDataWorldTransform));
}

WorldTransform::~WorldTransform() {

}

void WorldTransform::TransferMatrix() {

	//Resourceに書き込む
	ConstBuffDataWorldTransform* worldTransformData = nullptr;
	constBuff_->Map(0, nullptr, reinterpret_cast<void**>(&worldTransformData));
	worldTransformData->world = matWorld_;
	constBuff_->Unmap(0, nullptr);
}

void WorldTransform::UpdateMatrix() {

	//ワールド行列を計算
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	//親がいれば行列を掛ける
	if (parent_) {
		matWorld_ = Multiply(matWorld_, parent_->matWorld_);
	}

	//ワールド行列を転送する
	WorldTransform::TransferMatrix();
}