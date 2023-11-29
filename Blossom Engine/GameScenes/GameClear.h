#include "../Blossom Engine/GameScenes/IScene.h"
#include "../Necessary/Map/MapManager.h"
#include "../Blossom Engine/components/camera/DebugCamera.h"
#include "../Blossom Engine/Sprite/Sprite.h"
#include "../Blossom Engine/components/Input/Input.h"
#include "../EnemyManager.h"
#pragma once
class GameClear : public IScene
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
	int textureNum_;
	Input* input_;
	Vector3 pos_;

};