#pragma once
#include "./Blossom Engine/Math/MatrixCalculate.h"
#include "./Blossom Engine/Model/Model.h"
#include "Necessary/Models/Block.h"

#include "../Necessary/Models/UpsideTank.h"
#include "../Necessary/Models/DownsideTank.h"

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

class MapChip;

class Enemy
{
public:	// ** メンバ関数 ** //

	Enemy();
	~Enemy();

	void Initialize(std::vector < std::vector<int32_t>> map, std::vector<std::vector<MapChip*>> mapchip);
	void Update(const Node& playerPos);
	void Draw();
	std::vector<Node*>GetAStar(const Node& start, const Node& end);
	void LoadAI(const Node& enemyPos, const Node& playerPos);
	void ResetRoute(const Node& enemyPos, const Node& playerPos);
	void DeleteRoute();
	bool GetIsValid(int32_t x, int32_t y);
	int32_t GetManhattanDistance(const Node& a, const Node& b);

	void SetAngle(const Transform& player);

	// ゲッタ
	bool GetSearchTimeZero() { 
		// 探索待ち時間が0の場合、最大値に戻す
		if (searchTime_ == 0) {
			searchTime_ = kSearchTimeMax_;
			return true;
		}
		
		return false;
	}
	bool GetIsActive() { return isActive_; }

	// セッタ


	// 現在地
	Node now = { 3,4,0,0,0,nullptr };

private:// ** メンバ変数 ** //

	//　外部変数のポインタ //

	std::vector < std::vector<int32_t>> pMap_;
	Model* pMapchip_[12][12];

	// 座標 //

	// 敵本体 トランスフォーム
	Transform transform_;
	// 敵視界　トランスフォーム
	Transform visionTransform_;
	Vector3 visionVertex[3];
	// 敵砲台　トランスフォーム
	Transform cannonTransform_;

	// モデル //
	UpsideTank* upsidetank_;
	DownsideTank* downsidetank_;

	// テクスチャ
	

	// パラメータ //

	// AIのタイプ(動き方や一部パラメータに影響する)
	AI_TYPE type_;

	// 生存フラグ(tureなら生存)
	bool isActive_;

	// 経路探索クールタイム(仮で一定フレームごとに追跡を行う)
	const int32_t kSearchTimeMax_ = 330;
	int32_t searchTime_ = kSearchTimeMax_;

	// 攻撃クールタイム(最速で一秒ごとに一発)
	int32_t shotCoolTime_;
	const int32_t kMaxShotCoolTime_ = 60;
	
	// 初期地点
	Node prev_ = now;
	// ターゲットの位置
	Node next_ = now;

	// moveTimer
	float moveT = 0.0f;
	// 経路を保存
	std::vector<Node*>path_;
};

