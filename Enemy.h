#pragma once
#include "./Blossom Engine/Math/MatrixCalculate.h"
#include "./Blossom Engine/Model/Model.h"
#include "Necessary/Models/Block.h"

enum class AI_TYPE {
	NOMAL,
	RAPID,

};

// ノード構造体
struct Node {
	int32_t x, y;	// ノードの座標
	int32_t g;		// 開始ノードからの実際のコスト
	int32_t h;		// 終了ノードまでのManhattan距離
	int32_t f;		// g + h　の合計評価値
	Node* parent;	// 親ノードへのポインタ

	bool operator<(const Node& other) const {
		return f < other.f;
	}

	Node operator=(const Node& other) {
		return Node{
			x = other.x,
			y = other.y,
			g = other.g,
			h = other.h,
			f = other.f,
			parent = other.parent
		};
	}

	bool operator==(const Node& other) const {
		return{
			x == other.x &&
			y == other.y &&
			g == other.g &&
			h == other.h &&
			f == other.f &&
			parent == other.parent
		};
	}
};

class DownsideTank;

class Enemy
{
public:	// ** メンバ関数 ** //

	Enemy();
	~Enemy();

	void Initialize(DownsideTank* player);
	void Update(const Node& playerPos);
	void Draw();

	std::vector<Node*>AStar(const Node& start, const Node& end);
	void EnemyAI(const Node& enemyPos, const Node& playerPos);

	bool IsValid(int32_t x, int32_t y);
	int32_t ManhattanDistance(const Node& a, const Node& b);
	int32_t ManhattanDistanceWithDiagonal(const Node& a, const Node& b);

	// ゲッタ
	bool GetSearchTimeZero() { 
		// 探索待ち時間が0の場合、最大値に戻す
		if (searchTime_ == 0) {
			searchTime_ = kSearchTimeMax_;
			return true;
		}
		
		return false;
	}

	// セッタ


	// 現在地
	Node now = { 3,4,0,0,0,nullptr };

private:// ** メンバ変数 ** //

	// プレイヤーのポインタを取得
	DownsideTank* player_;

	// 座標 //

	// 敵本体 トランスフォーム
	Transform transform_;
	// 敵視界　トランスフォーム
	Transform visionTransform_;
	Vector3 visionVertex[3];
	// 敵砲台　トランスフォーム
	Transform cannonTransform_;

	// モデル //
	Model* model_ = nullptr;
	Model* mapChip[10][10];

	// テクスチャ
	

	// パラメータ //

	// AIのタイプ(動き方や一部パラメータに影響する)
	AI_TYPE type_;

	// 生存フラグ(tureなら生存)
	bool isActive;

	// 経路探索クールタイム(仮で一定フレームごとに追跡を行う)
	const int32_t kSearchTimeMax_ = 480;
	int32_t searchTime_ = kSearchTimeMax_;

	// 攻撃クールタイム(最速で一秒ごとに一発)
	int32_t shotCoolTime_;
	const int32_t kMaxShotCoolTime_ = 60;

	// 仮マップ
	std::vector < std::vector<int32_t>>map = {
	{0,0,0,0,0,0,0,1,1,1},
	{0,1,1,1,0,0,0,0,0,0},
	{0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,0},
	{0,0,1,1,0,0,0,0,0,0},
	{0,0,1,0,0,1,1,1,0,0},
	{0,0,1,0,0,1,0,0,0,0},
	{0,0,1,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	};
	
	// 初期地点
	Node prev_ = now;
	// ターゲットの位置
	Node next_ = now;
	
	// moveTimer
	float moveT = 0.0f;
	// 経路を保存
	std::vector<Node*>path_;
};

