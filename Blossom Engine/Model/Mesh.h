#pragma once
#include "../Blossom Engine/Common/Common.h"
#include "../Blossom Engine/Math/MatrixCalculate.h"
#include <vector>

/// <summary>
/// メッシュ
/// </summary>
class Mesh {
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
	/// メッシュの初期化
	/// </summary>
	/// <param name="vertices">頂点データ</param>
	void Initialize(const std::vector<VertexData>& vertices);

	/// <summary>
	/// グラフィックスコマンドのセット
	/// </summary>
	void SetGraphicsCommand();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	//VertexBuffer
	ComPtr<ID3D12Resource> vertexBuffer_ = nullptr;
	//VertexBufferView
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
	//頂点データ
	std::vector<VertexData> vertices_{};

};