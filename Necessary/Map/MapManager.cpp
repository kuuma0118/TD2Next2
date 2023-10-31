#include "MapManager.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

MapManager* MapManager::GetInstance() {
	static MapManager instance;
	return &instance;
}


void MapManager::Initialize() {
	for (int i = 0; i < kMapChipMaxSize_; i++) {
		map_[i].ClearMapChip();	// 全マップチップ初期化
	}

	// マップをCSVから読み込み
	LoadMapData();

	// マップ初期化
	for (int i = 0; i < kMapChipMaxSize_; i++) {
		map_[i].Initialize();	// 全マップ初期化
	}
}

void MapManager::LoadMapData() {
	ifstream stageifs("../Resources/Const/MapData.csv");
	string line;

	int stageLevel = 0;		// ステージのレベル
	int x{0}, y{0}, z{0};	// マップチップ
	bool getQuota = false;	// ノルマは読み込み済みか

	while (getline(stageifs, line)) {
		// "---"の場合次のステージへ
		if (line == "---") {
			stageLevel++;
			x = 0;
			y = 0;
			z = 0;
			getQuota = false;
			continue;
		}

		// ','で一列の情報を区切る
		vector<string> strvec = split(line, ',');
		
		// まずはノルマを読み込む
		if (!getQuota) {
			map_->SetQuota(std::stoi(strvec.at(0)), std::stoi(strvec.at(1)), std::stoi(strvec.at(2)));
			getQuota = true;
			continue;
		}

		// X軸、Y軸のループ
		for (int j = 0; j < strvec.size(); j++) {
			if (strvec.at(j)[0] == '|')	{	// |ならばY軸を1段UP
				y++;
				x = 0;
			}
			else {
				map_[stageLevel].SetMapChip({ (float)x,(float)y,(float)z }, static_cast<BlockTypeID>(std::stoi(strvec.at(j))));
				x++;
			}
		}
		z++; // 1列読み終わったらZ軸をずらす
		y = 0;
		x = 0;
	}

	// 最後にZ軸を反転させる
	for (int i = 0; i < kMapChipMaxSize_; i++) {
		map_[i].ReverseZ();	// 全マップチップ初期化
	}
}

vector<string> MapManager::split(string& input, char delimiter) {
	istringstream stream(input);
	string field;
	vector<string> result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}