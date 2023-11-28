#pragma once
#include "IScene.h"
#include "../Blossom Engine/Sprite/Sprite.h"
#include "../Blossom Engine/Sphere/Sphere.h"
#include "../Blossom Engine/components/Input/Input.h"
#include "../Necessary/Models/UpsideTank.h"
#include "../Necessary/Models/DownsideTank.h"
#include "../Necessary/Models/Block.h"
#include "../Blossom Engine/components/camera/DebugCamera.h"
class GameManager;

class TitleScene : public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize()override;
private:
	DebugCamera* debugcamera_;
	Sprite* sprite_;
	Sphere* sphere_;
	int textureNum_;
	Input* input_;
	Vector3 pos_;
	Block* block_;
	DownsideTank* downsidetank_;
	UpsideTank* upsidetank_;
};