#pragma once
#include "Enemy.h"
#include <list>

// 前方宣言 (プレイヤー)
class DownsideTank;

class EnemyManager
{
public:	// メンバ関数

	EnemyManager();
	~EnemyManager();

	void Initialize(DownsideTank* player);
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

	// 仮マップチップ
	Model* mapChip[12][12];

	// 仮マップ
	std::vector < std::vector<int32_t>>map ={
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,1,0,0,1,0,1,0,1},
	{1,0,1,0,1,0,0,1,0,1,0,1},
	{1,0,1,0,1,0,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,0,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,0,1,1,1,1,0,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},
	};



};

