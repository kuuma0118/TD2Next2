#include "CollisionManager.h"

void CollisionManager::ClearColliderList() {
	//コライダーリストをクリア
	colliders_.clear();
}

void CollisionManager::SetColliderList(Collider* collider) {
	//コライダーリストに登録
	colliders_.push_back(collider);
}

void CollisionManager::CheckAllCollisions() {
	//リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		//イテレータAからコライダーAを取得する
		Collider* colliderA = *itrA;
		//イテレータBはイテレータAの次の要素から回す(重複判定を回避)
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			//イテレータBからコライダーBを取得する
			Collider* colliderB = *itrB;
			//ベアの当たり判定
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {
	//衝突フィルタリング
	if ((colliderA->GetCollisionAttribute() & colliderB->GetCollisionMask()) == 0 ||
		(colliderB->GetCollisionAttribute() & colliderA->GetCollisionMask()) == 0) {
		return;
	}

	//球と球の判定
	if (((colliderA->GetCollisionPrimitive() & kCollisionPrimitiveSphere) != 0 && (colliderB->GetCollisionPrimitive() & kCollisionPrimitiveSphere) != 0) ||
		((colliderB->GetCollisionPrimitive() & kCollisionPrimitiveSphere) != 0 && (colliderA->GetCollisionPrimitive() & kCollisionPrimitiveSphere) != 0)) {
		//コライダーAのワールド座標を取得
		Vector3 posA = colliderA->GetWorldPosition();
		//コライダーBのワールド座標を取得
		Vector3 posB = colliderB->GetWorldPosition();
		//コライダーAとコライダーBの距離を計算
		float distance = Length(V3Sub(posA, posB));
		//球と球の交差判定
		if (distance <= colliderA->GetRadius() + colliderB->GetRadius()) {
			//コライダーAの衝突時コールバックを呼び出す
			colliderA->OnCollision(colliderB->GetCollisionAttribute(), colliderB->GetDamage());
			//コライダーBの衝突時コールバックを呼び出す
			colliderB->OnCollision(colliderA->GetCollisionAttribute(), colliderA->GetDamage());
		}
	}

	//AABBとAABBの判定
	if (((colliderA->GetCollisionPrimitive() & kCollisionPrimitiveAABB) != 0 && (colliderB->GetCollisionPrimitive() & kCollisionPrimitiveAABB) != 0) ||
		((colliderB->GetCollisionPrimitive() & kCollisionPrimitiveAABB) != 0 && (colliderA->GetCollisionPrimitive() & kCollisionPrimitiveAABB) != 0)) {
		//コライダーAのワールド座標を取得
		Vector3 posA = colliderA->GetWorldPosition();
		//コライダーBのワールド座標を取得
		Vector3 posB = colliderB->GetWorldPosition();
		//コライダーAのAABBを取得
		AABB aabbA = colliderA->GetAABB();
		//コライダーBのAABBを取得
		AABB aabbB = colliderB->GetAABB();
		if (posA.x + aabbA.min.x <= posB.x + aabbB.max.x && posA.x + aabbA.max.x >= posB.x + aabbB.min.x &&
			posA.y + aabbA.min.y <= posB.y + aabbB.max.y && posA.y + aabbA.max.y >= posB.y + aabbB.min.y &&
			posA.z + aabbA.min.z <= posB.z + aabbB.max.z && posA.z + aabbA.max.z >= posB.z + aabbB.min.z) {
			//コライダーAの衝突時コールバックを呼び出す
			colliderA->OnCollision(colliderB->GetCollisionAttribute(), colliderB->GetDamage());
			//コライダーBの衝突時コールバックを呼び出す
			colliderB->OnCollision(colliderA->GetCollisionAttribute(), colliderA->GetDamage());
		}
	}

	//球とAABBの判定
	if (((colliderA->GetCollisionPrimitive() & kCollisionPrimitiveSphere) != 0 && (colliderB->GetCollisionPrimitive() & kCollisionPrimitiveAABB) != 0) ||
		((colliderA->GetCollisionPrimitive() & kCollisionPrimitiveAABB) != 0 && (colliderB->GetCollisionPrimitive() & kCollisionPrimitiveSphere) != 0)) {
		//コライダーAのワールド座標を取得
		Vector3 posA = colliderA->GetWorldPosition();
		//コライダーBのワールド座標を取得
		Vector3 posB = colliderB->GetWorldPosition();
		//コライダーAのAABBを取得
		AABB aabbA = colliderA->GetAABB();
		//コライダーBのAABBを取得
		AABB aabbB = colliderB->GetAABB();

		//コライダーAがSphereの場合
		if (colliderA->GetCollisionPrimitive() & kCollisionPrimitiveSphere) {
			//最近接点を求める
			Vector3 closestPoint{
				std::clamp(posA.x,posB.x + aabbB.min.x,posB.x + aabbB.max.x),
				std::clamp(posA.y,posB.y + aabbB.min.y,posB.y + aabbB.max.y),
				std::clamp(posA.z,posB.z + aabbB.min.z,posB.z + aabbB.max.z) };
			//最近接点と球の中心との距離を求める
			float distance = Length(V3Sub(closestPoint, posA));
			//距離が半径よりも小さければ衝突
			if (distance <= colliderA->GetRadius()) {
				//コライダーAの衝突時コールバックを呼び出す
				colliderA->OnCollision(colliderB->GetCollisionAttribute(), colliderB->GetDamage());
				//コライダーBの衝突時コールバックを呼び出す
				colliderB->OnCollision(colliderA->GetCollisionAttribute(), colliderA->GetDamage());
			}
		}
		else if (colliderB->GetCollisionPrimitive() & kCollisionPrimitiveSphere) {
			//最近接点を求める
			Vector3 closestPoint{
				std::clamp(posB.x,posA.x + aabbA.min.x,posA.x + aabbA.max.x),
				std::clamp(posB.y,posA.y + aabbA.min.y,posA.y + aabbA.max.y),
				std::clamp(posB.z,posA.z + aabbA.min.z,posA.z + aabbA.max.z) };
			//最近接点と球の中心との距離を求める
			float distance = Length(V3Sub(closestPoint, posB));
			//距離が半径よりも小さければ衝突
			if (distance <= colliderB->GetRadius()) {
				//コライダーAの衝突時コールバックを呼び出す
				colliderA->OnCollision(colliderB->GetCollisionAttribute(), colliderB->GetDamage());
				//コライダーBの衝突時コールバックを呼び出す
				colliderB->OnCollision(colliderA->GetCollisionAttribute(), colliderA->GetDamage());
			}
		}
	}
}