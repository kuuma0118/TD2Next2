#pragma once
#include "./Blossom Engine/Math/MatrixCalculate.h"
#include "./Blossom Engine/Model/Model.h"

class MapChip
{
public:
	MapChip();
	~MapChip();
	void Initialize();
	void Update();
	void Draw();

private:

	// モデル //
	Model* model_ = nullptr;
	Model* mapChip[10][10];

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


};

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
	for (int32_t y = 0; y < map.size(); ++y) {
		for (int32_t x = 0; x < map[0].size(); ++x) {

			mapChip[y][x] = new Model;
			mapChip[y][x]->Initialize();
			mapChip[y][x]->transform.scale = { 0.5f,0.5f,0.5f };
			mapChip[y][x]->transform.translate.x = ((float)x * 1) - (map.size() * 0.5f);
			mapChip[y][x]->transform.translate.y = ((float)y * -1) + (map.size() * 0.5f);

			// Map[y][x]が1である場合
			// マップにブロックを配置
			if (map[y][x] == 1) {
				mapChip[y][x]->textureNum = TextureName::STAGETEXTURE;
				mapChip[y][x]->transform.translate.z -= 1;
			}

		}
	}

}

void MapChip::Update() {

}

void MapChip::Draw() {

	// マップチップを配置
	for (int32_t y = 0; y < map.size(); ++y) {
		for (int32_t x = 0; x < map[0].size(); ++x) {
			mapChip[y][x]->Draw();
		}
	}

}
