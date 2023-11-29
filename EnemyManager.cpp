#include "EnemyManager.h"
#include "Necessary/Models/DownsideTank.h"

// コンストラクタ
EnemyManager::EnemyManager() {}

// デストラクタ
EnemyManager::~EnemyManager() {

	// イテレータを使用して要素を削除する
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
}

// 初期化処理
void EnemyManager::Initialize(DownsideTank* player, MapChip* mapChip) {
	// プレイヤーのポインタを取得
	player_ = player;
	// マップチップのポインタを取得
	mapChip_ = mapChip;
}

// 更新処理
void EnemyManager::Update() {

	///////////////////////////////////////////
	/// プレイヤーの座標をマップチップの番地に変換
	///////////////////////////////////////////

	double minDistance =
		std::sqrt(std::pow(player_->transform.translate.x - nearestNode_.x, 2) +
			std::pow(player_->transform.translate.y - nearestNode_.y, 2));

	if (!mapChip_->map_.empty()) {

		for (int y = 0; y < mapChip_->map_[0].size(); ++y) {
			for (int x = 0; x < mapChip_->map_[0][y].size(); ++x) {

				if (mapChip_->map_[0][y][x] == 0) {
					double distance = std::sqrt(
						std::pow(player_->transform.translate.x - mapChip_->mapChip[0][y][x]->transform.translate.x, 2) +
						std::pow(player_->transform.translate.y - mapChip_->mapChip[0][y][x]->transform.translate.y, 2));
					mapChip_->mapChip[0][y][x]->textureNum = TextureName::STAGETEXTURE;

					if (distance < minDistance) {
						minDistance = distance;
						nearestNode_ = Node(x, y, 0, 0, 0, nullptr);
					}
				}
				else if (mapChip_->map_[0][y][x] == 1) {
					mapChip_->mapChip[0][y][x]->textureNum = TextureName::UPSIDETANK;
				}
			}
		}

		// プレイヤーが居る地点のマップチップのテクスチャを切り替えてわかりやすくする
		mapChip_->mapChip[0][nearestNode_.y][nearestNode_.x]->textureNum = TextureName::BLOCK;
	}


	for (Enemy* enemy : enemies_) {
		// 更新処理を行う
		enemy->Update(nearestNode_);
		enemy->SetAngle(player_->transform);

		// イテレータを使用して要素を削除する
		if (!enemy->GetIsActive()) {
			delete enemy;
		}
	}
}

// 描画処理
void EnemyManager::Draw() {

	//　描画を行う
	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}
}

// エネミーの追加
void EnemyManager::AddEnemy() {
	// 生成した敵を初期化
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(mapChip_->map_[0], mapChip_->mapChip[0]);
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
