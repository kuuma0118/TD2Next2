#pragma once

#include "IScene.h"
#include "../Necessary/Map/MapManager.h"
#include "../Blossom Engine/components/camera/DebugCamera.h"
#include "../Blossom Engine/Sprite/Sprite.h"
#include "../Blossom Engine/Sphere/Sphere.h"
#include "../Blossom Engine/components/Input/Input.h"
#include "../Necessary/Models/stage.h"
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
};