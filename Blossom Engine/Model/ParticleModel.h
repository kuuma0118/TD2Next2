#pragma once
#include "../Manager/TextureManager.h"
#include "../Necessary/Effect/Particle/ParticleSystem.h"
#include "../Blossom Engine/Math/ViewProjection.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"
#include <dxcapi.h>
#include <fstream>
#include <list>
#include <string>
#include <sstream>
#pragma comment(lib,"dxcompiler.lib")

class ParticleModel {
private:
	//エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	/// <summary>
	/// 頂点データ
	/// </summary>
	struct VertexData {
		Vector4 position;
		Vector2 texcoord;
		Vector3 normal;
	};

	/// <summary>
	/// マテリアルデータ構造体
	/// </summary>
	struct MaterialData {
		std::string textureFilePath;
	};

	/// <summary>
	/// モデルデータ構造体
	/// </summary>
	struct ModelData {
		std::vector<VertexData> vertices;
		MaterialData material;
		std::string name;
	};

	/// <summary>
	/// マテリアルの構造体
	/// </summary>
	struct ConstBuffDataMaterial {
		Vector4 color{};
		Matrix4x4 uvTransform{};
	};

	/// <summary>
	/// GPUに送るパーティクルの構造体
	/// </summary>
	struct ParticleForGPU {
		Matrix4x4 world;
		Vector4 color;
	};

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// 静的メンバ変数の解放
	/// </summary>
	static void Release();

	/// <summary>
	/// 描画前処理
	/// </summary>
	static void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// パーティクルモデルの作成
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="filename"></param>
	/// <param name="kNumInstance"></param>
	/// <param name="emitterData"></param>
	/// <returns></returns>
	static ParticleModel* CreateFromOBJ(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="particleSystem"></param>
	/// <param name="viewProjection"></param>
	void Draw(const ParticleSystem* particleSystem, const ViewProjection& viewProjection);

	/// <summary>
	/// 描画(テクスチャ差し替え)
	/// </summary>
	/// <param name="particleSystem"></param>
	/// <param name="viewProjection"></param>
	void Draw(const ParticleSystem* particleSystem, const ViewProjection& viewProjection, uint32_t textureHandle);

private:
	/// <summary>
	/// DXCの初期化
	/// </summary>
	static void InitializeDXC();

	/// <summary>
	/// シェーダーをコンパイルする
	/// </summary>
	/// <param name="filePath">Compilerするshaderのファイルパス</param>
	/// <param name="profile">Compilerで使用するProfile</param>
	/// <returns>実行用のバイナリ</returns>
	static ComPtr<IDxcBlob> CompileShader(
		const std::wstring& filePath,
		const wchar_t* profile);

	/// <summary>
	/// PSOの作成
	/// </summary>
	static void CreatePipelineStateObject();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="kNumInstance"></param>
	void Initialize(const ModelData& modelData);

	/// <summary>
	/// 頂点データの作成
	/// </summary>
	void CreateVertexResource();

	/// <summary>
	/// マテリアルリソース用の作成
	/// </summary>
	void CreateMaterialResource();

	/// <summary>
	/// Objファイルの読み込み
	/// </summary>
	/// <param name="directoryPath">ディレクトリ名</param>
	/// <param name="filename">ファイル名</param>
	/// <returns></returns>
	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// mtlファイルの読み込み
	/// </summary>
	/// <param name="directoryPath">ディレクトリ名</param>
	/// <param name="filename">ファイル名</param>
	/// <returns></returns>
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

private:
	//デバイス
	static ID3D12Device* sDevice_;
	//コマンドリスト
	static ID3D12GraphicsCommandList* sCommandList_;
	//DXC
	static ComPtr<IDxcUtils> sDxcUtils_;
	static ComPtr<IDxcCompiler3> sDxcCompiler_;
	static ComPtr<IDxcIncludeHandler> sIncludeHandler_;
	//RootSignature
	static ComPtr<ID3D12RootSignature> sRootSignature_;
	//PipelineStateObject
	static ComPtr<ID3D12PipelineState> sGraphicsPipelineState_;
	//モデルデータ
	static std::list<ModelData> modelDatas_;
	//頂点データ
	std::vector<VertexData> vertices_{};
	//頂点バッファ
	ComPtr<ID3D12Resource> vertexResource_ = nullptr;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
	//マテリアル用のリソース
	ComPtr<ID3D12Resource> materialResource_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
};

