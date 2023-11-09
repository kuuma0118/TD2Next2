#pragma once
#include <cstdint>

////プレイヤー陣営
//const uint32_t kCollisionAttributePlayer       = 0b00001;
//const uint32_t kCollisionAttributePlayerBullet = 0b00010;
//const uint32_t kCollisionAttributeEnemy        = 0b00100;
//const uint32_t kCollisionAttributeEnemyBullet  = 0b01000;
//
//
//const uint32_t kCollisionMaskPlayer            = 0b11110;
//const uint32_t kCollisionMaskPlayerBullet      = 0b10100;
//const uint32_t kCollisionMaskEnemy             = 0b11011;
//const uint32_t kCollisionMaskEnemyBullet       = 0b10001;

const uint32_t kCollisionAttributePlayer = 0b0001;
const uint32_t kCollisionAttributeEnemy = 0b0010;
const uint32_t kCollisionAttributeMissile = 0b0100;
const uint32_t kCollisionAttributeLaser = 0b1000;

const uint32_t kCollisionMaskPlayer = 0b1110;
const uint32_t kCollisionMaskEnemy = 0b0001;
const uint32_t kCollisionMaskMissile = 0b0001;
const uint32_t kCollisionMaskLaser = 0b0001;

//形状
const uint32_t kCollisionPrimitiveSphere = 0b1;
const uint32_t kCollisionPrimitiveAABB = 0b1 << 1;