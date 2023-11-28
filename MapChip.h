#pragma once
#include "./Blossom Engine/Math/MatrixCalculate.h"
#include "./Blossom Engine/Model/Model.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class MapChip
{
public:
	MapChip();
	~MapChip();
	void Initialize();
	void Update();
	void Draw();

	void LoadMapData(int fileNum);

	void SetNextMapData();

public:

	// モデル //
	Model* model_ = nullptr;
	std::vector < std::vector < Model*>> mapChip;

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

	// ステージ
	std::vector < std::vector<int32_t>>stageData_ = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	};
	// マップのcsvを取得する
	std::vector <std::stringstream> mapData;
	std::vector <std::vector < std::vector <int32_t>>> data_;

};
