#pragma once
#include <stdint.h>
#include "CollisionConfig.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"

class Collider {
public:
	/// 衝突時に呼ばれる関数
	virtual void OnCollision(uint32_t collisionAttribute, float damage) {};

	/// ワールド座標を取得
	virtual Vector3 GetWorldPosition() = 0;

	/// 半径を取得
	float GetRadius() { return radius_; };

	/// 半径を設定
	void SetRadius(float radius) { radius_ = radius; };

	/// <summary>
	/// AABBのサイズを取得
	/// </summary>
	/// <returns></returns>
	AABB GetAABB() { return aabb_; };

	/// <summary>
	/// AABBのサイズを設定
	/// </summary>
	/// <param name="aabb"></param>
	void SetAABB(AABB& aabb) { aabb_ = aabb; };

	/// <summary>
	/// 衝突属性(自分)を取得
	/// </summary>
	/// <returns></returns>
	uint32_t GetCollisionAttribute() { return collisionAttribute_; };

	/// <summary>
	/// 衝突属性(自分)を設定
	/// </summary>
	/// <param name="collisionAttribute"></param>
	void SetCollisionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; };

	/// <summary>
	/// 衝突属性(相手)を取得
	/// </summary>
	/// <returns></returns>
	uint32_t GetCollisionMask() { return collisionMask_; };

	/// <summary>
	/// 衝突属性(相手)を設定
	/// </summary>
	/// <param name="collisionMask"></param>
	void SetCollisionMask(uint32_t collisionMask) { collisionMask_ = collisionMask; };

	/// <summary>
	/// 形状を取得
	/// </summary>
	/// <returns></returns>
	uint32_t GetCollisionPrimitive() { return collisionPrimitive_; };

	/// <summary>
	/// 形状を設定
	/// </summary>
	/// <param name="collisionPrimitive"></param>
	void SetCollisionPrimitive(uint32_t collisionPrimitive) { collisionPrimitive_ = collisionPrimitive; };

	/// <summary>
	/// ダメージを取得
	/// </summary>
	/// <returns></returns>
	float GetDamage() { return damage_; };

	/// <summary>
	/// ダメージを設定
	/// </summary>
	/// <param name="damage"></param>
	void SetDamage(float damage) { damage_ = damage; };

private:
	//衝突半径
	float radius_ = 1.0f;
	//AABB
	AABB aabb_{ {-1.0f,-1.0f,-1.0f},{1.0f,1.0f,1.0f} };
	//衝突属性(自分)
	uint32_t collisionAttribute_ = 0xffffffff;
	//衝突マスク(相手)
	uint32_t collisionMask_ = 0xffffffff;
	//形状(デフォルトは球に設定)
	uint32_t collisionPrimitive_ = kCollisionPrimitiveSphere;
	//ダメージ
	float damage_ = 1.0f;
};