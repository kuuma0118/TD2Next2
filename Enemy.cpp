#include "Enemy.h"
#include <iostream>
#include <algorithm> 
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include "MoveEasing.h"
#include "Necessary/Models/DownsideTank.h"

Enemy::Enemy() { }

Enemy::~Enemy() {
	delete model_;

	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			delete mapChip[y][x];
		}
	}

	for (int i = 0; i < path_.size(); ++i) {
		delete path_[i];
	}
}

void Enemy::Initialize(DownsideTank* player) {

	// プレイヤーのポインタを取得
	player_ = player;

	// 敵本体 トランスフォーム
	transform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, { 0.0f, 0.0f, 0.0f } };
	// 敵視界　トランスフォーム
	visionTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, { 0.0f, 0.0f, 0.0f } };
	visionVertex[0] = { visionTransform_.translate.x,visionTransform_.translate.y,visionTransform_.translate.z };
	visionVertex[1] = { visionTransform_.translate.x,visionTransform_.translate.y,visionTransform_.translate.z };
	visionVertex[2] = { visionTransform_.translate.x,visionTransform_.translate.y,visionTransform_.translate.z };
	// 敵砲台　トランスフォーム
	cannonTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, { 0.0f, 0.0f, 0.0f } };
	// モデル //
	model_ = new Model;
	model_->Initialize();
	model_->textureNum = BLOCK;
	model_->transform.translate = { 0.0f,0.0f,-2.0f };

	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			mapChip[y][x] = new Model;
			mapChip[y][x]->Initialize();
			mapChip[y][x]->transform.scale = { 0.5f,0.5f ,0.5f };
			mapChip[y][x]->transform.translate.x = ((float)x * 1) - (map.size()*0.5f);
			mapChip[y][x]->transform.translate.y = ((float)y * -1) + (map.size()*0.5f);


			// マップにブロックが配置状態の場合
			if (map[y][x] == 1) {
				mapChip[y][x]->textureNum = TextureName::STAGETEXTURE;
				mapChip[y][x]->transform.translate.z -= 1;
			}
		}
	}

	// 初期位置を設定
	model_->transform.scale = { 0.5f,0.5f ,0.5f };
	model_->transform.translate = mapChip[now.x][now.y]->transform.translate;
	model_->transform.translate.z = -1.0f;

	// AIのタイプ(動き方や一部パラメータに影響する)
	type_ = AI_TYPE::NOMAL;
	// 生存フラグ(tureなら生存)
	isActive = true;
	// クールタイム(最速で一秒ごとに一発)
	shotCoolTime_ = 0;


	// AIタイプごとにパラメータを設定


}

void Enemy::Update(const Node& playerPos) {

	// isActive == false であれば早期リターンする
	if (isActive == false) { return; }

	// 探索待ち時間を減少
	if (searchTime_ > 0) { --searchTime_; }
	

	///////////////////////////////////////////
	/// プレイヤーの座標をマップチップの番地に変換
	///////////////////////////////////////////

	double minDistance = 
		std::sqrt(std::pow(player_->transform.translate.x - nearestGrid.x, 2) +
		std::pow(player_->transform.translate.y - nearestGrid.y, 2));

	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			if (map[y][x] == 0) {
				double distance = std::sqrt(
					std::pow(player_->transform.translate.x - mapChip[y][x]->transform.translate.x, 2) +
					std::pow(player_->transform.translate.y - mapChip[y][x]->transform.translate.y, 2));
				mapChip[y][x]->textureNum = TextureName::UVCHEKER;

				if (distance < minDistance) {
					minDistance = distance;
					nearestGrid = Node(x, y, 0, 0, 0, nullptr);
				}
			}
		}
	}
	// プレイヤーが居る地点のマップチップのテクスチャを切り替えてわかりやすくする
	mapChip[nearestGrid.y][nearestGrid.x]->textureNum = TextureName::BLOCK;

	///////////////////////////////////////
	/// 追従を行う
	///////////////////////////////////////

	// 迂回をし過ぎぬよう、定期的に計算済みの経路をリセットする
	if (searchTime_ == 0) {
		if (moveT == 1.0f) {
			now = next_;
			prev_ = next_;
			DeleteRoute();
			searchTime_ = kSearchTimeMax_;
			moveT = 0.0f;
		}
	}

	// 線形補間が終了したら座標を修正し、次の目的地を設定
	if (moveT == 1.0f) {
		now = next_;
		prev_ = next_;
		moveT = 0.0f;
	}
	// 線形補間用の数値を加算
	if (moveT < 1.0f) {
		if (moveT == 0.0f) { LoadAI(now, nearestGrid); }
		moveT += (1.0f / 85.0f);
		if (moveT > 1.0f) { moveT = 1.0f; }
	}

	// 線形補間を行い、ターゲットまでの距離を詰める
	// 線形補間で取得した座標を代入
	model_->transform.translate.x = MoveEasing::Vec3::EaseNomal(
		{ mapChip[prev_.y][prev_.x]->transform.translate.x,mapChip[prev_.y][prev_.x]->transform.translate.y,1.0f },
		{ mapChip[next_.y][next_.x]->transform.translate.x,mapChip[next_.y][next_.x]->transform.translate.y,1.0f },
		moveT).x;

	model_->transform.translate.y = MoveEasing::Vec3::EaseNomal(
		{ mapChip[prev_.y][prev_.x]->transform.translate.x,mapChip[prev_.y][prev_.x]->transform.translate.y,1.0f },
		{ mapChip[next_.y][next_.x]->transform.translate.x,mapChip[next_.y][next_.x]->transform.translate.y,1.0f },
		moveT).y;

}

void Enemy::Draw() {

	// 仮のマップチップ
	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			mapChip[y][x]->Draw();
		}
	}

	// 仮のエネミー
	model_->Draw();

}

// マップの境界・障害物チェック
bool Enemy::GetIsValid(int32_t x, int32_t y) {

	/////////////////////////////////////////////
	/// マップの境界チェックや障害物のチェックなどを行う
	/// 実際のアプリケーションに合わせて実装
	/////////////////////////////////////////////

	// マップの境界チェック
	if (x < 0 || x >= map[0].size() || y < 0 || y >= map.size()) {
		return false;
	}

	// マップの障害物チェック
	if (map[y][x] == 1) {
		return false;// 障害物がある場合は移動できない
	}

	return true;// 移動可能な場合
}

// マンハッタン距離を計算する
int32_t Enemy::GetManhattanDistance(const Node& a, const Node& b) {
	return abs(b.x - a.x) + abs(b.y - a.y);
}

// 斜め移動可能なマンハッタン距離の計算
int32_t manhattanDistanceWithDiagonal(const Node& a, const Node& b) {
	if (std::abs(b.x - a.x) >= std::abs(b.y - a.y)) {
		return std::abs(b.x - a.x);
	}
	return std::abs(b.y - a.y);
}

// AStarアルゴリズム(斜め移動なし)
std::vector<Node*> Enemy::GetAStar(const Node& start, const Node& end) {
	std::set<Node*> openSet{};
	std::vector<Node*> closedSet{};

	openSet.insert(new Node(start));

	while (!openSet.empty()) {
		Node* current = *openSet.begin();
		openSet.erase(openSet.begin());
		closedSet.push_back(current);

		if (current->x == end.x && current->y == end.y) {
			std::reverse(closedSet.begin(), closedSet.end());
			while (current->parent != nullptr) {
				path_.push_back(current);
				current = current->parent;

				if (current->parent == current) {
					break;
				}
			}
			std::reverse(path_.begin(), path_.end());
			return path_;
		}

		for (int32_t dy = -1; dy <= 1; ++dy) {
			for (int32_t dx = -1; dx <= 1; ++dx) {
				// 現在のマスは除外する
				if (dx == 0 && dy == 0) {
					continue;
				}
				// 斜め移動をしない
				if ((dx == -1 && dy == -1) || (dx == 1 && dy == -1) ||
					(dx == -1 && dy == 1) || (dx == 1 && dy == 1)) {
					continue;
				}

				// 隣接した点の計算
				int32_t newX = current->x + dx;
				int32_t newY = current->y + dy;

				// 進行可能な場合のみ
				if (GetIsValid(newX, newY)) {
					if (std::find_if(closedSet.begin(), closedSet.end(), [newX, newY](const Node* node) {
						return node->x == newX && node->y == newY;
						}) == closedSet.end()) {

						Node* newNode = new Node{
							newX, newY,
							current->g + 1,
							GetManhattanDistance({ newX, newY, 0, 0, 0, nullptr }, { end.x, end.y, 0, 0, 0, nullptr }),
							0,
							nullptr
						};

						newNode->f = newNode->g + newNode->h;

						if (!closedSet.empty()) {
							Node* lastClosedNode = closedSet.back();
							newNode->parent = lastClosedNode;
						}

						if (std::find_if(openSet.begin(), openSet.end(), [newX, newY](const Node* node) {
							return node->x == newX && node->y == newY;
							}) != openSet.end()) {
							auto it = std::find_if(openSet.begin(), openSet.end(), [newX, newY](const Node* node) {
								return node->x == newX && node->y == newY;
								});

							if (newNode->f < (*it)->f) {
								openSet.erase(it);
								openSet.insert(newNode);
							}
						}
						else {
							openSet.insert(newNode);
						}
					}
				}
			}
		}
	}

	return std::vector<Node*>();
}

// EnemyのAI(計算)
void Enemy::LoadAI(const Node& enemyPos, const Node& playerPos) {

	// 経路がまだ計算されていない場合や、経路が空の場合は新たに計算を行う
	if (path_.empty()) {
		Node start = { enemyPos.x, enemyPos.y, 0, 0, 0, nullptr };
		Node end = { playerPos.x, playerPos.y, 0, 0, 0, nullptr };
		path_ = GetAStar(start, end);
	}

	// 経路が存在する場合
	if (!path_.empty()) {

		// 最初のノードが敵の次の移動先
		Node* nextMove = path_.front();

		// 次に移動するマスを設定
		next_.x = nextMove->x;
		next_.y = nextMove->y;

		// 経路から最初のノードを削除
		path_.erase(path_.begin());
	}

}

// Enemyの計算済みの経路をリセットし再計算する
void Enemy::ResetRoute(const Node& enemyPos, const Node& playerPos) {
	
	// 計算済みの経路が存在する場合、消去する
	while (!path_.empty()) {
		// 経路から最初のノードを削除
		path_.erase(path_.begin());
	}

	// 経路削除後に再計算を行う
	LoadAI(enemyPos, playerPos);
}

// Enemyの計算済みの経路を削除する
void Enemy::DeleteRoute() {

	// 計算済みの経路が存在する場合、消去する
	while (!path_.empty()) {
		// 経路から最初のノードを削除
		path_.erase(path_.begin());
	}

}