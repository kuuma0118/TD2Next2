#include "MapChip.h"


MapChip::MapChip()
{
}

MapChip::~MapChip()
{
	for (int32_t y = 0; y < map.size(); ++y) {
		for (int32_t x = 0; x < map[0].size(); ++x) {
			delete mapChip[y][x];
		}
	}
}

void MapChip::Initialize() {

	// マップチップを初期化
	for (int32_t y = 0; y < data_[0].size(); ++y) {
		std::vector<Model*>newMapChipLine;
		for (int32_t x = 0; x < data_[0][y].size(); ++x) {
			Model* newMapChip;
			newMapChip = new Model;
			newMapChip->Initialize();
			newMapChip->transform.scale = { 0.5f,0.5f,0.5f };
			newMapChip->transform.translate.x = ((float)x * 1) - (data_[0][y].size() * 0.5f);
			newMapChip->transform.translate.y = ((float)y * -1) + (data_[0].size() * 0.5f);
			newMapChip->textureNum = TextureName::STAGETEXTURE;

			// Map[y][x]が1である場合
			// マップにブロックを配置
			if (data_[0][y][x] == 1) {
				newMapChip->textureNum = TextureName::UPSIDETANK;
				newMapChip->transform.translate.z -= 1;
			}
			newMapChipLine.push_back(newMapChip);
		}
		mapChip.push_back(newMapChipLine);
	}

}

void MapChip::Update() {

	ImGui::Begin("MapChip");
	for (int y = 0; y < data_[0].size(); ++y) {
		for (int x = 0; x < data_[0][y].size(); ++x) {
			// 	ImGui::SameLine()　を用いて同じ行で表示する
			ImGui::SameLine();
			ImGui::Text("%d ", data_[0][y][x]);
			ImGui::SameLine();
			// 改行する
			ImGui::NewLine();
		}
		// 改行する
		ImGui::NewLine();
	}
	ImGui::End();

}

void MapChip::Draw() {

	// マップチップを配置
	for (int32_t y = 0; y < data_[0].size(); ++y) {
		for (int32_t x = 0; x < data_[0][y].size(); ++x) {
			mapChip[y][x]->Draw();
		}
	}

}

void MapChip::LoadMapData(int fileNum) {

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

void MapChip::SetNextMapData() {

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

	for (size_t z = 0; z < data_.size(); z++)
	{
		// マップチップを初期化
		for (int32_t y = 0; y < data_[0].size(); ++y) {
			std::vector<Model*>newMapChipLine;
			for (int32_t x = 0; x < data_[0][y].size(); ++x) {
				Model* newMapChip;
				newMapChip = new Model;
				newMapChip->Initialize();
				newMapChip->transform.scale = { 0.5f,0.5f,0.5f };
				newMapChip->transform.translate.x = ((float)x * 1) - (data_[0][y].size() * 0.5f);
				newMapChip->transform.translate.y = ((float)y * -1) + (data_[0].size() * 0.5f);
				newMapChip->textureNum = TextureName::STAGETEXTURE;

				// Map[y][x]が1である場合
				// マップにブロックを配置
				if (data_[0][y][x] == 1) {
					newMapChip->textureNum = TextureName::UPSIDETANK;
					newMapChip->transform.translate.z -= 1;
				}
				newMapChipLine.push_back(newMapChip);
			}
			mapChip.push_back(newMapChipLine);
		}
	}

}