#pragma once
#include "IScene.h"
#include "../Blossom Engine/Sphere/Sphere.h"
#include "../Blossom Engine/components/Input/Input.h"
#include "../Necessary/Models/Block.h"
#include "../Blossom Engine/Math/ViewProjection.h"
#include "../Necessary/UI/UI.h"

#include "../SampleParticle.h"

#include <memory>
#include "../components/camera/DebugCamera.h"
#include "../utility/Collision/CollisionManager.h"

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
	//DebugCamera
	DebugCamera* debugCamera_ = nullptr;
		//DebugCameraの切り替え
	bool isDebugCameraActive_ = false;

	XINPUT_STATE joyState_;

	//衝突マネージャー
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;
	//Particle 
	std::unique_ptr<Sample> sample_ = nullptr;

	Sphere* sphere_;
	int textureNum_;
	Input* input_;
	Vector3 pos_;
	Block* block_;

	//パーティクル
	std::unique_ptr<ParticleModel> particleModel_ = nullptr;
	std::unique_ptr<ParticleSystem> particleSystem_ = nullptr;
};