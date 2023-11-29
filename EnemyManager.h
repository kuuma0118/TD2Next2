#pragma once
#include "Enemy.h"
#include <list>
#include "../MapChipManager.h"

// 前方宣言 (プレイヤー)
class DownsideTank;

class EnemyManager
{
public:	// メンバ関数

	EnemyManager();
	~EnemyManager();

	void Initialize(DownsideTank* player, MapChipManager* mapChip);
	void Update();
	void Draw();
	void AddEnemy();
	void DeleteEnemy();


private: // メンバ変数

	// エネミーのリスト
	std::list<Enemy*> enemies_;
	// プレイヤーのポインタを取得
	DownsideTank* player_;
	// プレイヤーの最近地点のノード
	Node nearestNode_ = { 0,0,0,0,0,nullptr };
	// マップチップ
	MapChipManager* mapChipManager_;
};

