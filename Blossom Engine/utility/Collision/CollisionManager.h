#pragma once
#include "Collider.h"
#include <algorithm>
#include <list>

class CollisionManager {
public:
	/// <summary>
	/// コライダーリストをクリアする
	/// </summary>
	void ClearColliderList();

	/// <summary>
	/// コライダーリストに登録
	/// </summary>
	/// <param name="collider"></param>
	void SetColliderList(Collider* collider);

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

private:
	/// <summary>
	/// コライダー2つの衝突判定と応答
	/// </summary>
	/// <param name="colliderA"></param>
	/// <param name="colliderB"></param>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

private:
	//コライダーリスト
	std::list<Collider*> colliders_{};
};