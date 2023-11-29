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

public:

    Model* model_;

};

