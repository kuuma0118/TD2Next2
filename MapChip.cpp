#include "MapChip.h"

MapChip::MapChip() {
	
}

MapChip::~MapChip() {
	delete model_;
}

void MapChip::Init() {
	model_ = new Model;
	
	/// コライダー

	//衝突半径
	SetRadius(1.0f);
	//AABB
	AABB newAABB = { { -0.9f,-0.9f,-0.9f }, { 0.9f,0.9f,0.9f } };
	SetAABB(newAABB);
	//衝突属性(自分)
	SetCollisionAttribute(kCollisionAttributeEnemy);
	//衝突マスク(相手)
	SetCollisionMask(kCollisionMaskEnemy);
	//形状(デフォルトは球に設定)
	SetCollisionPrimitive(kCollisionPrimitiveAABB);
	//ダメージ
	SetDamage(0.0f);

}

void MapChip::Updata() {

}

Vector3 MapChip::GetWorldPosition(){
	return model_->transform.translate;
}
