#pragma once
#include "../Blossom Engine/Math/Vector3.h"
#include "../Models/Block.h"

// *** マップID *** //
// 0 ... 無し（空気）
// 99 ... 壁（動かせない、消滅しない）
// 100 ... プレイヤー開始地点
// -1 ... マップ領域外

// 1～98 ... ブロック（同じ番号のブロックは結合する）
enum class BlockTypeID : int {
	Air = 0,
	Wall = 99,
	StartPosition = 100,
	OutOfArea = -1,
};

class Map {
public: // メンバ関数
	void Initialize();	// 初期化
	void Update();	// 更新
	void Draw();	// 描画
	
	// クリアか判定する
	bool CheckClear();

	// マップIDをクリア
	void ClearMapChip();
	// 指定した座標にマップIDをセットする
	void SetMapChip(Vector3 position, BlockTypeID id);
	// 最後にZ軸を反転させる用
	void ReverseZ();
	// 指定した座標のマップIDをゲットする
	BlockTypeID GetMapChip(Vector3 position) { return mapChip_[(int)position.x][(int)position.y][(int)position.z]; }

	// マップのノルマをセットする
	void SetQuota(int quota1, int quota2, int quota3) { 
		quota[0] = quota1;
		quota[1] = quota2;
		quota[2] = quota3;
	}

	// マップのサイズを受け取る
	size_t GetXSize() { return mapChip_.size(); }
	size_t GetYSize() { return (GetXSize() > 0) ? mapChip_[0].size() : 0; }
	size_t GetZSize() { return (GetXSize() > 0 && GetYSize() > 0) ? mapChip_[0][0].size() : 0; }

	// マップの中心座標を受け取る
	Vector3 GetMapCenterPosition();

private: // メンバ定数
	float kBlockSize_ = 2.0f;	// ブロック一つのサイズ
	float kBlockScale_ = 1.0f;	// ブロックの共通スケール

private: // メンバ変数

	// マップチップ（読み取り専用）
	std::vector<std::vector<std::vector<BlockTypeID>>> mapChip_;

	// 描画用のブロックのデータ
	std::vector<Block*> groundBlocks_;
	// 描画用のブロックのデータ
	std::vector<Block*> blocks_;

	// マップのノルマ
	int quota[3];

private: // プライベートな関数
	// xyzからワールド座標を求める
	Vector3 GetWorldPosition(int x, int y, int z);
	// 地面の描画要のブロックを追加する
	void AddGroundBlock();
};