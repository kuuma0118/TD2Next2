#pragma once
#include "./Blossom Engine/Math/MatrixCalculate.h"
#include "./MapChip.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class MapChipManager
{
public:
	MapChipManager();
	~MapChipManager();
	void Initialize();
	void Update();
	void Draw();
	void FallNextStage();

	void LoadMapData(int fileNum);
	void SetNextMapData();

public:

	// モデル //
	Model* model_ = nullptr;
	std::vector < std::vector < std::vector < MapChip*>>> mapChip;

	// マップ
	std::vector < std::vector < std::vector<int32_t>>>map_;

	// マップのcsvを取得する
	std::vector <std::stringstream> mapData;
	std::vector <std::vector < std::vector <int32_t>>> data_;

	// 取得するデータのz進行度
	int32_t dataZ_ = 0;

};
