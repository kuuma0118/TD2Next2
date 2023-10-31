#pragma once

// Scene
#include "../Blossom Engine/GameScenes/IScene.h"
#include "../Blossom Engine/GameScenes/TitleScene.h"
#include "../Blossom Engine/GameScenes/GameScene.h"


// Manager
#include "ObjManager.h"
#include "../Manager/PipelineManager.h"

// Base
#include "../Blossom Engine/WinApp/WinApp.h"
#include "../Blossom Engine/Common/Common.h"

// components
#include "../Blossom Engine/components/light/Light.h"
#include "../Blossom Engine/components/camera/Camera.h"
#include "../Blossom Engine/components/camera/DebugCamera.h"
#include "../Blossom Engine/components/Input/Input.h"
#include "../Blossom Engine/components/Audio/Audio.h"

class GameManager
{
public:
	///
	/// Default Method
	/// 
	// コンストラクタ
	GameManager();

	// デストラクタ
	//~GameManager();

	// 初期化
	void Initialize();

	// 更新処理
	//void Update();

	// 解放処理
	void Finalize();

	///
	/// user method
	///
	// ループ処理
	void Run();

	// 描画前の処理
	void BeginFrame();

	// 描画後の処理
	void EndFrame();

	// ImGuiのパラメータを入れる
	void ImGuiAdjustParameter();

private:
	// base
	WinApp* winApp_;
	DirectXCommon* directXCommon_;
	BlossomEngine* myEngine_;

	// components
	Camera* camera_;
	DebugCamera* debugCamera_;
	Light* light_;
	ObjManager* objManager_;
	TextureManager* textureManager_;
	ImGuiManager* imGuiManager_;
	Input* input_;
	Audio* audio_;
	Microsoft::WRL::ComPtr<IXAudio2> xAudio2_;
	IXAudio2MasteringVoice* masterVoice_;
	SoundData soundData1_;

	// scene
	IScene* sceneArr_[4];
	int sceneNum_;
	int preSceneNum_;
};

