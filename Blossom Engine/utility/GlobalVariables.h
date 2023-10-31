#pragma once
#include "../Blossom Engine/Math/Vector2.h"
#include "../Blossom Engine/Math/Vector3.h"
#include "../Blossom Engine/Math/Vector4.h"
#include <variant>
#include <map>
#include <string>

class GlobalVariables {
public:
	static GlobalVariables* GetInstance();

	bool GetIsSave() { return isSave_; }

	// 値の取得(int)
	int32_t GetIntValue(const std::string& groupName, const std::string& key);
	// 値の取得(float)
	float GetFloatValue(const std::string& groupName, const std::string& key);
	// 値の取得(Vector2)
	Vector2 GetVector2Value(const std::string& groupName, const std::string& key);
	// 値の取得(Vector3)
	Vector3 GetVector3Value(const std::string& groupName, const std::string& key);
	// 値の取得(Vector4)
	Vector4 GetVector4Value(const std::string& groupName, const std::string& key);

	// 値のセット(int)
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);
	// 値のセット(float)
	void SetValue(const std::string& groupName, const std::string& key, float value);
	// 値のセット(Vector2)
	void SetValue(const std::string& groupName, const std::string& key, Vector2& value);
	// 値のセット(Vector3)
	void SetValue(const std::string& groupName, const std::string& key, Vector3& value);
	// 値のセット(Vector4)
	void SetValue(const std::string& groupName, const std::string& key, Vector4& value);

	// 項目の追加(int)
	void AddItem(const std::string& groupName, const std::string& key, int32_t value);
	// 項目の追加(float)
	void AddItem(const std::string& groupName, const std::string& key, float value);
	// 項目の追加(Vector2)
	void AddItem(const std::string& groupName, const std::string& key, Vector2& value);
	// 項目の追加(Vector3)
	void AddItem(const std::string& groupName, const std::string& key, Vector3& value);
	// 項目の追加(Vector4)
	void AddItem(const std::string& groupName, const std::string& key, Vector4& value);

	/// <summary>
	/// グループの生成
	/// </summary>
	/// <param name="groupName">グループ名</param>
	void CreateGroup(const std::string& groupName);

	/// <summary>
	/// ファイルに書き出し
	/// </summary>
	/// <param name="groupName"></param>
	void SaveFile(const std::string& groupName);

	/// <summary>
	/// ファイルから読み込む
	/// </summary>
	void LoadFile(const std::string& groupName);

	/// <summary>
	/// ディレクトリの全ファイル読み込み
	/// </summary>
	void LoadFiles();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

private:
	GlobalVariables() = default;
	~GlobalVariables() = default;
	GlobalVariables(const GlobalVariables& obj) = delete;
	GlobalVariables& operator=(const GlobalVariables& obj) = delete;

public:
	// 項目
	struct Item {
		// 項目の値
		std::variant<int32_t, float, Vector2, Vector3, Vector4> value;
	};
	// グループ
	struct Group {
		std::map<std::string, Item> items;
	};
	// 全データ
	std::map<std::string, Group> datas_;

	// グローバル変数の保存先ファイルパス
	const std::string kDirectoryPath = "resources/GlobalVariables/";

	bool isSave_;
};