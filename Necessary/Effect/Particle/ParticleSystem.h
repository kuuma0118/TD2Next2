#pragma once
#include "../Manager/TextureManager.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"
#include "BuildEmitter.h"

class ParticleSystem {
private:
	//エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	//パーティクルの最大数
	const uint32_t kMaxInstance = 10000;

	//GPUに送る構造体
	struct ParticleForGPU {
		Matrix4x4 world;
		Vector4 color;
	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// エミッターの追加
	/// </summary>
	/// <param name="particleEmitter"></param>
	void AddParticleEmitter(ParticleEmitter* particleEmitter) { particleEmitters_.push_back(std::unique_ptr<ParticleEmitter>(particleEmitter)); };

	/// <summary>
	/// GPUハンドルを取得
	/// </summary>
	/// <returns></returns>
	const uint32_t& GetSrvIndex() const { return srvIndex_; };

	/// <summary>
	/// インスタンス数を取得
	/// </summary>
	/// <returns></returns>
	const uint32_t& GetNumInstance() const { return numInstance_; };

	/// <summary>
	/// エミッターを取得
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	ParticleEmitter* GetParticleEmitter(const std::string& name);

	/// <summary>
	/// エミッターのリストを取得
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	std::list<ParticleEmitter*> GetParticleEmitters(const std::string& name);

private:
	/// <summary>
	/// Instancing用のリソースの作成
	/// </summary>
	void CreateInstancingResource();

	/// <summary>
	/// パーティクルのデータをGPUに転送
	/// </summary>
	void UpdateInstancingResource();

private:
	//Instancing用のWorldTransform
	ComPtr<ID3D12Resource> instancingResource_ = nullptr;
	//Instancing用のSRVの番号
	uint32_t srvIndex_ = 0;
	//エミッターのリスト
	std::list<std::unique_ptr<ParticleEmitter>> particleEmitters_{};
	//インスタンス数
	uint32_t numInstance_ = 0;

};

