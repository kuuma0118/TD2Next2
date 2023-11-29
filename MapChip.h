#pragma once
#include "./Blossom Engine/utility/Collision/Collider.h"
#include "./Blossom Engine/Model/Model.h"
class MapChip :
    public Collider
{
public:

    MapChip();
    ~MapChip();
    void Init();
    void Updata();
    void Draw();
    Vector3 GetWorldPosition()override;

	/// <summary>
	/// 衝突時に呼ばれる関数
	/// </summary>
	void OnCollision(uint32_t collisionAttribute, float damage) override{
	};

public:

    // モデル
    Model* model_;
};

