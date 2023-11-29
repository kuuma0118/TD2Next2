#pragma once
#include "IScene.h"
#include "../Blossom Engine/Sprite/Sprite.h"
#include "../Blossom Engine/Sphere/Sphere.h"
#include "../Blossom Engine/components/Input/Input.h"
#include "../Necessary/Models/UpsideTank.h"
#include "../Necessary/Models/DownsideTank.h"
#include "../Necessary/Models/Block.h"
class GameManager;

class TitleScene : public IScene
{
public:

	//トランジションの時間
	static const int kTransitionTime = 120;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize()override;
private:
	Sprite* sprite_;
	Sphere* sphere_;
	int textureNum_;
	Input* input_;
	Vector3 pos_;
	Block* block_;
	DownsideTank* downsidetank_;
	UpsideTank* upsidetank_;

	//トランジション用のスプライト
	std::unique_ptr<Sprite> transitionSprite_ = nullptr;
	//トランジションのテクスチャ
	uint32_t transitionTextureHandle_ = 0;
	//トランジションの色
	Vector4 transitionColor_ = { 0.0f,0.0f,0.0f,1.0f };
	//トランジションのフラグ
	bool isTransition_ = false;
	bool isTransitionEnd_ = false;
	//トランジションのタイマー
	float transitionTimer_ = 0;
};