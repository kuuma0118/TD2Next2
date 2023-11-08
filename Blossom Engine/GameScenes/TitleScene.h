#pragma once
#include "IScene.h"
#include "../Blossom Engine/Sprite/Sprite.h"
#include "../Blossom Engine/Sphere/Sphere.h"
#include "../Blossom Engine/components/Input/Input.h"
#include "../Necessary/Models/Block.h"
#include "../Blossom Engine/Math/ViewProjection.h"

class GameManager;

class TitleScene : public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize()override;
private:
	//カメラ
	ViewProjection viewProjection_{};
	//テクスチャ
	uint32_t textureHandle_ = 0;
	//TextureManager
	TextureManager* textureManager_ = nullptr;

	Sprite* sprite_;
	Sphere* sphere_;
	int textureNum_;
	Input* input_;
	Vector3 pos_;
	Block* block_;
};