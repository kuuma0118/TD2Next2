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
	float x, y;	// ノードの座標
	float g;		// 開始ノードからの実際のコスト
	float h;		// 終了ノードまでのManhattan距離
	float f;		// g + h　の合計評価値
	Node* parent;	// 親ノードへのポインタ

	bool operator<(const Node& other) const {
		return f < other.f;
	}
};

class DownsideTank;

class Enemy
{
public:	// ** メンバ関数 ** //

	Enemy();
	~Enemy();

	void Initialize(DownsideTank* player);
	void Update();
	void Draw();

	std::vector<Node>AStar(const Node& start, const Node& end);

	bool IsValid(float x, float y);
	float ManhattanDistance(const Node& a, const Node& b);

	// ゲッタ


	// セッタ


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
	Model* mapChip[5][5];

	// テクスチャ
	

	// パラメータ //

	// AIのタイプ(動き方や一部パラメータに影響する)
	AI_TYPE type_;

	// 生存フラグ(tureなら生存)
	bool isActive;

	// クールタイム(最速で一秒ごとに一発)
	int32_t shotCoolTime_;
	const int32_t kMaxShotCoolTime_ = 60;

	// 仮マップ
	std::vector < std::vector<int32_t>>map = {
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,0,0,1,0},
	{0,1,0,0,0},
	{0,0,0,0,0}
	};

	// 初期地点
	Node start = { 0, 0, 0, 0, 0, nullptr };
	// ターゲットの位置
	Node end = { 4, 4, 0, 0, 0, nullptr };
	// 現在地
	Node now = { 0,0,0,0,0,nullptr };
	// moveTimer
	float moveT = 0.0f;
};

