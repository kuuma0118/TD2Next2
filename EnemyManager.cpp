#include "EnemyManager.h"
#include "Necessary/Models/DownsideTank.h"

// コンストラクタ
EnemyManager::EnemyManager() {}

// デストラクタ
EnemyManager::~EnemyManager() {
	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			delete mapChip[y][x];
		}
	}

	// イテレータを使用して要素を削除する
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
}

// 初期化処理
void EnemyManager::Initialize(DownsideTank* player) {
	// プレイヤーのポインタを取得
	player_ = player;

	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			mapChip[y][x] = new Model;
			mapChip[y][x]->Initialize();
			mapChip[y][x]->transform.scale = { 0.5f,0.5f ,0.5f };
			mapChip[y][x]->transform.translate.x = ((float)x * 1) - (map.size() * 0.5f);
			mapChip[y][x]->transform.translate.y = ((float)y * -1) + (map.size() * 0.5f);

			// マップにブロックが配置状態の場合
			if (map[y][x] == 1) {
				mapChip[y][x]->textureNum = TextureName::STAGETEXTURE;
				mapChip[y][x]->transform.translate.z -= 1;
			}
		}
	}

}

// 更新処理
void EnemyManager::Update() {

	///////////////////////////////////////////
	/// プレイヤーの座標をマップチップの番地に変換
	///////////////////////////////////////////

	double minDistance =
		std::sqrt(std::pow(player_->transform.translate.x - nearestNode_.x, 2) +
			std::pow(player_->transform.translate.y - nearestNode_.y, 2));

	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			if (map[y][x] == 0) {
				double distance = std::sqrt(
					std::pow(player_->transform.translate.x - mapChip[y][x]->transform.translate.x, 2) +
					std::pow(player_->transform.translate.y - mapChip[y][x]->transform.translate.y, 2));
				mapChip[y][x]->textureNum = TextureName::UVCHEKER;

				if (distance < minDistance) {
					minDistance = distance;
					nearestNode_ = Node(x, y, 0, 0, 0, nullptr);
				}
			}
		}
	}
	// プレイヤーが居る地点のマップチップのテクスチャを切り替えてわかりやすくする
	mapChip[nearestNode_.y][nearestNode_.x]->textureNum = TextureName::BLOCK;


	// イテレータを使用して要素を削除する
	for (Enemy* enemy : enemies_) {
		// 更新処理を行う
		enemy->Update(nearestNode_);

		if (!enemy->GetIsActive()) {
			delete enemy;
		}
	}
}

// 描画処理
void EnemyManager::Draw() {
	// 仮のマップチップ
	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			mapChip[y][x]->Draw();
		}
	}

	//　描画を行う
	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}
}

// エネミーの追加
void EnemyManager::AddEnemy() {
	// 生成した敵を初期化
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(map, mapChip);
	// リストに追加
	enemies_.push_back(newEnemy);
}

// エネミーの削除
void EnemyManager::DeleteEnemy() {
	// リストにテキが登録されている場合のみ
	if (!enemies_.empty()) {
		// リストの先頭にいる敵を削除
		enemies_.erase(enemies_.begin());
	}
}
