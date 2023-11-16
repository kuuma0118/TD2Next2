#include "Bullet.h"
#include <stdio.h>
#include <math.h>
#include <cmath>

// コンストラクタ
Bullet::Bullet(Vector3 initialTranslate, float initialSpeed) : translate(initialTranslate), speed(initialSpeed), angle(0.0f) {}

// 弾を更新するメソッド
void Bullet::update() {
    translate.x += speed * std::cos(angle);
    translate.y += speed * std::sin(angle);

    // 角度を変更（1度ずつ回転）
    angle += 0.0174533; // 1度をラジアンに変換
}

// 弾の位置を取得するメソッド
Vector3 Bullet::getPosition() const {
    return translate;
}