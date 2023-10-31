#include "GameManager.h"
#include "../Blossom Engine/String/String.h"
#include "../Blossom Engine/utility/GlobalVariables.h"
//#include "../../Class/Map/MapManager.h"

GameManager::GameManager() {
	// 各シーンの配列
	sceneArr_[TITLE_SCENE] = new TitleScene();
	sceneArr_[GAME_SCENE] = new GameScene();
	//sceneArr_[GAMECLEAR_SCENE] = new GameClear();
	//sceneArr_[GAMEOVER_SCENE] = new GameOver();
}

void GameManager::Initialize() {

	const char kWindowTitle[] = "CG2_CLASS";
	// タイトルバーの変換
	auto&& titleString = ConvertString(kWindowTitle);

	// windowの初期化
	winApp_ = WinApp::GetInstance();
	winApp_->Initialize(titleString.c_str(), 1280, 720);

	// DirectXの初期化
	directXCommon_ = DirectXCommon::GetInstance();
	directXCommon_->Initialize(winApp_->GetHwnd());

	// 入力(キーボードとゲームパッド)0
	input_ = Input::GetInstance();
	input_->Initialize();

	// Audioの初期化
	audio_ = Audio::GetInstance();

	// objManagerの初期化。今はobjファイルの読み込みだけしている
	objManager_ = ObjManager::GetInstance();
	objManager_->Initialize();

	// Textureの初期化
	textureManager_ = TextureManager::GetInstance();
	textureManager_->TextureManager::GetInstance()->Initialize();

	// エンジンの初期化
	myEngine_ = new BlossomEngine();
	myEngine_->Initialize();

	// ライトの設定
	light_ = Light::GetInstance();
	light_->Initialize(DirectXCommon::GetInstance()->GetDevice());

	// デバッグカメラの初期化
	debugCamera_ = DebugCamera::GetInstance();
	debugCamera_->Initialize();

	// カメラの初期化
	camera_ = Camera::GetInstance();
	camera_->Initialize();

	// ImGuiの初期化
	imGuiManager_ = new ImGuiManager();
	imGuiManager_->Initialize(winApp_->GetHwnd());

	// ブローバル変数の読み込み
	GlobalVariables::GetInstance()->LoadFiles();

	//// マップマネージャーの初期化
	MapManager* mapManager = MapManager::GetInstance();
	mapManager->Initialize();
	mapManager->SetCurrentMap(0);

	//初期シーンの設定
	sceneNum_ = TITLE_SCENE;
	// シーンごとの初期化
	sceneArr_[sceneNum_]->Initialize();
}

void GameManager::Run() {
	// 初期化
	Initialize();

	MSG msg{};
	// ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		// Windowにメッセージが来ていたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// 描画前の処理
			BeginFrame();

			// シーンチェック
			preSceneNum_ = sceneNum_;
			sceneNum_ = sceneArr_[sceneNum_]->GetSceneNum();

			//シーン変更チェック
			if (sceneNum_ != preSceneNum_) {
				sceneArr_[sceneNum_]->Initialize();
				sceneArr_[preSceneNum_]->Finalize();
			}

			///
			/// 更新処理
			/// 
			sceneArr_[sceneNum_]->Update();

			// ImGuiのパラメータを入れている
			ImGuiAdjustParameter();

			///
			/// 描画処理
			/// 
			sceneArr_[sceneNum_]->Draw();

			// 描画後の処理
			EndFrame();
		}
	}
	// 解放処理
	Finalize();
}

void GameManager::Finalize() {
	sceneArr_[sceneNum_]->Finalize();
	for (int i = 0; i < 2; i++) {
		delete sceneArr_[i];
	}
	// ImGui
	imGuiManager_->Release();
	delete imGuiManager_;
	delete myEngine_;
	textureManager_->Release();
	directXCommon_->Release();
	CloseWindow(winApp_->GetHwnd());
	xAudio2_.Reset();
	audio_->SoundUnload(&soundData1_);
	// Textureのゲーム終了処理
	textureManager_->ComUninit();
}

void GameManager::BeginFrame() {
	input_->Update();
	myEngine_->BeginFrame();

	// ImGui
	imGuiManager_->PreDraw();

	// デバッグカメラ
	debugCamera_->Update();
	// カメラの設定
	camera_->SettingCamera();

	// グローバル変数の更新
	GlobalVariables::GetInstance()->Update();
}

void GameManager::EndFrame() {
	// ImGui
	imGuiManager_->PostDraw();

	myEngine_->EndFrame();
}

void GameManager::ImGuiAdjustParameter() {
	ImGui::Begin("CommonSettings");
	if (ImGui::BeginTabBar("CommonTabBar"))
	{
		// カメラのImGui
		if (ImGui::BeginTabItem("Camera")) {
			camera_->Camera::GetInstance()->DrawDebugParameter();
			ImGui::EndTabItem();
		}
		// ライトのImGui
		if (ImGui::BeginTabItem("Half Lambert")) {
			light_->ImGuiAdjustParameter();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}