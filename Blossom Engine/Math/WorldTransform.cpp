#include "WorldTransform.h"

void WorldTransform::UpdateMatrix() {

	//ワールド行列を計算
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);


	//親がいれば行列を掛ける
	if (parent_) {
		matWorld_ = Multiply(matWorld_, parent_->matWorld_);
	}
}