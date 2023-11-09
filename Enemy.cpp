#include "Enemy.h"
#include <iostream>
#include <vector>
#include <set>
#include <cmath>


Enemy::Enemy() {

}

Enemy::~Enemy() {

}

void Enemy::Initialize() {

	// 敵本体 トランスフォーム
	transform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, { 0.0f, 0.0f, 0.0f } };
	// 敵視界　トランスフォーム
	visionTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, { 0.0f, 0.0f, 0.0f } };
	visionVertex[0] = {visionTransform_.translate.x,visionTransform_.translate.y,visionTransform_.translate.z };
	visionVertex[1] = {visionTransform_.translate.x,visionTransform_.translate.y,visionTransform_.translate.z };
	visionVertex[2] = {visionTransform_.translate.x,visionTransform_.translate.y,visionTransform_.translate.z };
	// 敵砲台　トランスフォーム
	cannonTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, { 0.0f, 0.0f, 0.0f } };
	// モデル //
	model_ = new Model;
	model_->Initialize();
	model_->textureNum = BLOCK;
	model_->transform.translate = { 0.0f,2.0f,0.0f };

	for (int x = 0; x < map.size(); ++x) {
		for (int y = 0; y < map[0].size(); ++y) {
			mapChip[x][y] = new Model;
			mapChip[x][y]->Initialize();
			mapChip[x][y]->transform.translate.x = (float)x * 2;
			mapChip[x][y]->transform.translate.z = (float)y * 2;
		}
	}

	// AIのタイプ(動き方や一部パラメータに影響する)
	type_ = AI_TYPE::NOMAL;
	// 生存フラグ(tureなら生存)
	isActive = true;
	// クールタイム(最速で一秒ごとに一発)
	shotCoolTime_ = 0;


	// AIタイプごとにパラメータを設定


}

void Enemy::Update() {

	// isActive == false であれば早期リターンする
	if (isActive == false) { return; }

	// プレイヤーの座標を取得
	// プレイヤーに最も近いマップチップを取得?

	// 経路探索をする
	// A*アルゴリズムを用いて最短経路を探索する

	// 開始ノードと終了ノードを設定
	// マップ変更時・障害物消滅時・一定時間経過後に行う?
	Node start = { 0, 0, 0, 0, 0, nullptr };
	Node end = { 4, 4, 0, 0, 0, nullptr };

}

void Enemy::Draw() {
	
	// 仮のマップチップ
	for (int x = 0; x < map.size(); ++x) {
		for (int y = 0; y < map[0].size(); ++y) {
			mapChip[x][y]->Draw();
		}
	}

	// 仮のエネミー
	model_->Draw();

}


bool Enemy::IsValid(int32_t x, int32_t y) {
	// マップの境界チェックや障害物のチェックなどを行う
	// 実際のアプリケーションに合わせて実装

	// マップの境界チェック
	if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size()) {
		return false;
	}

	// マップの障害物チェック
	if (map[x][y] == 1) {
		return false;// 障害物がある場合は移動できない
	}

	return true;// 移動可能な場合
}

int Enemy::ManhattanDistance(const Node& a, const Node& b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

std::vector<Node> Enemy::AStar(const Node& start, const Node& end) {
	std::set<Node> openSet;
	std::vector<Node> closeSet;

	openSet.insert(start);

	while (!openSet.empty())
	{
		Node current = *openSet.begin();// オープンリストから最小評価値のノードを選択
		openSet.erase(openSet.begin());

		if (current.x == end.x && current.y == end.y) {
			// 終了ノードに到達した場合、経路を復元して返す
			std::vector<Node>path;
			while (current.parent != nullptr)
			{
				path.push_back(current);
				current = *current.parent;
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		// current　の隣接ノードを取得し、評価値を計算
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (dx == 0 && dy == 0) {
					continue; // current ノード自体をスキップ	
				}

				int  newX = current.x + dx;
				int  newY = current.y + dy;
				
				if (IsValid(newX, newY)) {
					// neighbor のノード評価値を計算
					Node neighbor = { 
						newX,newY,
						current.g + 1,// g: current.g + 1
						ManhattanDistance({newX,newY},end),//  h: 終了ノードまでのManhattan距離
						0,
						&current
					};
				
					// そして neighbor をオープンリストに追加
					openSet.insert(neighbor);
				}

			}
		}

		closeSet.push_back(current);
	}

	// ゴールに到達できなかった場合は空の経路を返す
	return std::vector<Node>();
}