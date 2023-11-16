#pragma once
#include "Blossom Engine/Math/Vector3.h"
#include <stdio.h>
#include <math.h>

#include "Blossom Engine/Math/Vector3.h"

// 弾のクラスの宣言
class Bullet {
public:
    // コンストラクタ
    Bullet(Vector3 initialTranslate, float initialSpeed);

    // 弾を更新するメソッド
    void update();

    // 弾の位置を取得するメソッド
    Vector3 getPosition() const;

private:
    Vector3 translate;
    float speed;
    float angle; // 回転角度
};