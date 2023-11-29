#include "Enemy.h"
#include <iostream>
#include <algorithm> 
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include "MoveEasing.h"
#include "MapChip.h"

Enemy::Enemy() { }

Enemy::~Enemy() {
	delete upsidetank_;
	delete downsidetank_;

	for (int i = 0; i < path_.size(); ++i) {
		delete path_[i];
	}
}

void Enemy::Initialize(std::vector < std::vector<int32_t>> map, std::vector<std::vector<MapChip*>> mapchip) {

	pMap_ = map;

	for (int y = 0; y < map.size(); ++y) {
		std::vector<Model*> line;
		for (int x = 0; x < map[y].size(); ++x) {
			line.push_back(mapchip[y][x]->model_);
		}
		pMapchip_.push_back(line);
	}

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
	upsidetank_ = new UpsideTank;
	upsidetank_->Initialize();
	upsidetank_->textureNum = UPSIDEENEMYTANK;
	upsidetank_->transform.translate = { 0.0f,0.0f,-2.0f };

	downsidetank_ = new DownsideTank;
	downsidetank_->Initialize();
	downsidetank_->textureNum = DOWNSIDEENEMYTANK;
	downsidetank_->transform.translate = { 0.0f,0.0f,-2.0f };

	now = { 6,4,0,0,0,nullptr };
	prev_ = now;
	next_ = now;

	// 初期位置を設定
	upsidetank_->transform.translate = pMapchip_[now.y][now.x]->transform.translate;
	upsidetank_->transform.translate.z = -1.0f;
	downsidetank_->transform = upsidetank_->transform;

	// AIのタイプ(動き方や一部パラメータに影響する)
	type_ = AI_TYPE::NOMAL;
	// 生存フラグ(tureなら生存)
	isActive_ = true;
	// クールタイム(最速で一秒ごとに一発)
	shotCoolTime_ = 0;


	// AIタイプごとにパラメータを設定


}

void Enemy::Update(const Node& nearestNode) {

	// isActive == false であれば早期リターンする
	if (isActive_ == false) { return; }

	// 探索待ち時間を減少
	if (searchTime_ > 0) { --searchTime_; }
	


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
		if (moveT == 0.0f) { LoadAI(now, nearestNode); }
		moveT += (1.0f / 90.0f);
		if (moveT > 1.0f) { moveT = 1.0f; }
	}

	// 線形補間を行い、ターゲットまでの距離を詰める
	// 線形補間で取得した座標を代入
	downsidetank_->transform.translate.x = MoveEasing::Vec3::EaseNomal(
		{ pMapchip_[prev_.y][prev_.x]->transform.translate.x,pMapchip_[prev_.y][prev_.x]->transform.translate.y,1.0f },
		{ pMapchip_[next_.y][next_.x]->transform.translate.x,pMapchip_[next_.y][next_.x]->transform.translate.y,1.0f },
		moveT).x;

	downsidetank_->transform.translate.y = MoveEasing::Vec3::EaseNomal(
		{ pMapchip_[prev_.y][prev_.x]->transform.translate.x,pMapchip_[prev_.y][prev_.x]->transform.translate.y,1.0f },
		{ pMapchip_[next_.y][next_.x]->transform.translate.x,pMapchip_[next_.y][next_.x]->transform.translate.y,1.0f },
		moveT).y;
	upsidetank_->transform.translate = downsidetank_->transform.translate;


}

void Enemy::Draw() {

	// 仮のエネミー
	upsidetank_->Draw();
	downsidetank_->Draw();

}

// マップの境界・障害物チェック
bool Enemy::GetIsValid(int32_t x, int32_t y) {

	/////////////////////////////////////////////
	/// マップの境界チェックや障害物のチェックなどを行う
	/// 実際のアプリケーションに合わせて実装
	/////////////////////////////////////////////

	// マップの境界チェック
	if (x < 0 || x >= pMap_[0].size() || y < 0 || y >= pMap_.size()) {
		return false;
	}

	// マップの障害物チェック
	if (pMap_[y][x] == 1) {
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

	// オープンリストがから出ない場合
	while (!openSet.empty()) {

		// オープンリストから最小評価値のノードを取り出す
		Node* current = *openSet.begin();
		// オープンリスト内の取り出したノードを削除
		openSet.erase(openSet.begin());
		// クローズドリストに取り出したノードを入れる
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

void Enemy::SetAngle(const Transform& player) {

	//////////////////////////////////
	/// 砲台をプレイヤーに向ける
	//////////////////////////////////

	// 角度を設定
	Vector3 vel(
		player.translate.x - upsidetank_->transform.translate.x,
		player.translate.y - upsidetank_->transform.translate.y,
		0);

	// 回転
	upsidetank_->transform.rotate.z = -atan2(vel.x, vel.y);
	
}