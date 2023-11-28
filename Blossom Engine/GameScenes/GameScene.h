#pragma once

#include "IScene.h"
#include "../Necessary/Map/MapManager.h"
#include "../Blossom Engine/components/camera/DebugCamera.h"
#include "../Blossom Engine/Sprite/Sprite.h"
#include "../Blossom Engine/Sphere/Sphere.h"
#include "../Blossom Engine/components/Input/Input.h"
#include "../Necessary/Models/stage.h"
#include "../Necessary/Models/UpsideTank.h"
#include "../Necessary/Models/DownsideTank.h"
#include "../Enemy.h"
#include "../MapChip.h"

class GameManager;

class GameScene : public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize()override;
	
private:
	//// カメラのポインタ
	//DebugCamera* camera_ = nullptr;

	////// マップデータ
	//Map* map_ = nullptr;

	// デバッグ用の変数
	int loadStageNum_ = 0;	// 読み込むステージの番号
	Sprite* sprite_;
	Sphere* sphere_;
	int textureNum_;
	Input* input_;
	Vector3 pos_;
	Stage* stage_;
	UpsideTank* upsidetank_;
	DownsideTank* downsidetank_;
	Enemy* enemy_ = nullptr;

	int32_t pX = 6;
	int32_t pY = 2;

	// マップチップ
	MapChip* mapChip_;
};