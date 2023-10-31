#pragma once
#include "Map.h"
#include <string>

/// <summary>
/// マップの情報を持つクラス
/// </summary>
class MapManager {
public: // メンバ関数
	static MapManager* GetInstance();

	void Initialize();	// 初期化

	// 現在のマップを設定する
	void SetCurrentMap(int level) { currentMap_ = &map_[level]; }
	// 現在のマップのデータを受け取る
	Map* GetCurrentMap() { return currentMap_; }

private: // メンバ定数
	// マップデータを示したファイルパス
	const char* filePath_ = "../Resources/Const/MapData.csv";
	const static int kMapChipMaxSize_ = 8;	// マップデータの数

private: // メンバ変数
	
	// 全マップデータ
	Map map_[kMapChipMaxSize_];
	// 現在のマップ
	Map* currentMap_ = nullptr;

private: // プライベートな関数
	MapManager() = default;
	~MapManager() = default;
	MapManager(const MapManager&) = delete;
	const MapManager& operator=(const MapManager&) = delete;


	// ファイルから全マップのデータを読み込む関数
	void LoadMapData();

	// string分割関数
	std::vector<std::string> split(std::string& input, char delimiter);
};