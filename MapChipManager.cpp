#include "MapChipManager.h"


MapChipManager::MapChipManager()
{
}

MapChipManager::~MapChipManager()
{
	for (int32_t z = 0; z < mapChip.size(); ++z) {
		for (int32_t y = 0; y < mapChip[z].size(); ++y) {
			for (int32_t x = 0; x < mapChip[z][y].size(); ++x) {
				delete mapChip[z][y][x];
			}
		}
	}
}

void MapChipManager::Initialize() {

	// マップチップを初期化
	for (int32_t z = 0; z < map_.size(); ++z) {
		for (int32_t y = 0; y < map_[z].size(); ++y) {
			std::vector<MapChip*>newMapChipLine;
			for (int32_t x = 0; x < map_[z][y].size(); ++x) {
				MapChip* newMapChip = new MapChip;
				newMapChip->Init();
				newMapChip->model_->Initialize();
				//newMapChip->model_->transform.scale = { 0.5f,0.5f,0.5f };
				newMapChip->model_->transform.translate.x = ((float)x * 1) - (map_[z][y].size());
				newMapChip->model_->transform.translate.y = ((float)y * -1) + (map_[y].size());
				newMapChip->model_->textureNum = TextureName::STAGETEXTURE;

				// Map[y][x]が1である場合
				// マップにブロックを配置
				if (map_[z][y][x] == 1) {
					newMapChip->model_->textureNum = TextureName::UPSIDETANK;
					newMapChip->model_->transform.translate.z -= 1;
				}

				if (map_[z][y][x] == -1) {
					newMapChip->model_->textureNum = TextureName::UPSIDETANK;
					newMapChip->model_->transform.translate.z -= 1;
				}
				newMapChipLine.push_back(newMapChip);
			}
			mapChip[0].push_back(newMapChipLine);
		}
	}

}

void MapChipManager::Update() {

	// マップチップを配置
	for (int32_t z = 1; z < map_.size(); ++z) {
		for (int32_t y = 0; y < map_[z].size(); ++y) {
			for (int32_t x = 0; x < map_[z][y].size(); ++x) {
				// 自分のマスにブロックが存在し、1つ下の階層の同じマスが空白の場合、
				// 一個下にブロックを移動させる
				if (map_[z][y][x] == 1 && map_[z - 1][y][x] == 0) {
					map_[z][y][x] = 0;
					map_[z - 1][y][x] = 1;
					mapChip[z][y][x]->model_->transform.translate.z += 1;
				}
			}
		}
	}
}

void MapChipManager::Draw() {

	// マップチップを配置
	for (int32_t z = 0; z < map_.size(); ++z) {
		for (int32_t y = 0; y < map_[z].size(); ++y) {
			for (int32_t x = 0; x < map_[z][y].size(); ++x) {
				mapChip[z][y][x]->model_->Draw();
			}
		}
	}
}

void MapChipManager::LoadMapData(int fileNum) {

	int index = 0;

	while (index < fileNum)
	{
		// ファイルの基本名と拡張子を指定
		std::string baseName = "./CSV/Mapchip - ";
		std::string extension = ".csv";

		std::stringstream ss;
		ss << baseName << index << extension;

		// ファイルを開く
		std::ifstream file;
		file.open(ss.str());
		assert(file.is_open());

		std::stringstream fileData;
		fileData << file.rdbuf();

		// ファイルの内容を文字列ストリームコピー
		mapData.push_back(std::move(fileData));

		// ファイルを閉じる
		file.close();

		//　indexを加算
		++index;
	}

}

void MapChipManager::SetNextMapData() {

	int index = 0;

	while (index < mapData.size())
	{
		// 一行分の文字列を入れる変数
		std::string line;
		// 1マップ分の数値を保存する
		std::vector<std::vector<int32_t>> oneMapData;

		//　コマンド実行ループ
		while (getline(mapData[index], line)) {
			// 各行のデータを格納するベクトル
			std::vector<int> row;
			// 一行分の文字列をストリームに変換
			std::stringstream ss(line);
			std::string cell;

			// ステージの端まで代入する
			while (getline(ss, cell, ',')) {
				int value = std::atoi(cell.c_str());
				row.push_back(value);
			}
			oneMapData.push_back(row);
		}

		data_.push_back(oneMapData);
		++index;
	}

}

void MapChipManager::FallNextStage() {

	if (dataZ_ < data_.size()) {

		// マップにデータの値を加算
		std::vector <std::vector <int32_t>>newValueMatrix;

		for (int32_t y = 0; y < data_[dataZ_].size(); ++y) {
			std::vector<int32_t> newValueLine;

			for (int32_t x = 0; x < data_[dataZ_][y].size(); ++x) {
				int32_t newValue = data_[dataZ_][y][x];
				newValueLine.push_back(newValue);
			}
			newValueMatrix.push_back(newValueLine);
		}
		map_.push_back(newValueMatrix);

		// マップチップを初期化
			// 行列の範囲
		std::vector<std::vector<MapChip*>> newMapChipArea;

		for (int32_t y = 0; y < map_[dataZ_].size(); ++y) {
			// 一行の範囲
			std::vector<MapChip*>newMapChipLine;

			for (int32_t x = 0; x < map_[dataZ_][y].size(); ++x) {
				// 一マスの範囲
				MapChip* newMapChip = new MapChip;
				newMapChip->Init();
				newMapChip->model_->Initialize();
				//newMapChip->model_->transform.scale = { 0.5f,0.5f,0.5f };
				newMapChip->model_->transform.translate.x = ((float)x * 2) - (map_[dataZ_][y].size() );
				newMapChip->model_->transform.translate.y = ((float)y * -2) + (map_[dataZ_].size()  );
				newMapChip->model_->textureNum = TextureName::STAGETEXTURE;

				// Map[y][x]が1である場合
				// マップにブロックを配置
				if (map_[dataZ_][y][x] == 1) {
					newMapChip->model_->textureNum = TextureName::UPSIDETANK;
					newMapChip->model_->transform.translate.z -= (dataZ_ + 1);
				}

				if (map_[dataZ_][y][x] == -1) {
					newMapChip->model_->textureNum = TextureName::UPSIDETANK;
					newMapChip->model_->transform.translate.z -= 1;
				}
				newMapChipLine.push_back(newMapChip);
			}

			newMapChipArea.push_back(newMapChipLine);
		}

		mapChip.push_back(newMapChipArea);

		++dataZ_;
	}


}