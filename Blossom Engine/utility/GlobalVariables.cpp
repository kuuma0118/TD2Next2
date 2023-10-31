#include "GlobalVariables.h"
#include "../ImGui/ImGuiManager.h"
#include <fstream>
#include "../externals/nlohmann/json.hpp"

GlobalVariables* GlobalVariables::GetInstance() {
	static GlobalVariables instance;

	return &instance;
}

#pragma region Get

int32_t GlobalVariables::GetIntValue(const std::string& groupName, const std::string& key) {
	// 指定したグループが存在するかをassertで確認
	assert(datas_.find(groupName) != datas_.end());

	// 指定したグループの参照を取得
	Group& group = datas_[groupName];

	// 指定したキーが存在するかをassertで確認
	assert(group.items.find(key) != group.items.end());

	// 指定したグループから指定したキーの値を取得して返す
	return std::get<int32_t>(group.items[key].value);
}

float GlobalVariables::GetFloatValue(const std::string& groupName, const std::string& key) {
	// 指定したグループが存在するかをassertで確認
	assert(datas_.find(groupName) != datas_.end());

	// 指定したグループの参照を取得
	Group& group = datas_[groupName];

	// 指定したキーが存在するかをassertで確認
	assert(group.items.find(key) != group.items.end());

	// 指定したグループから指定したキーの値を取得して返す
	return std::get<float>(group.items[key].value);
}

Vector2 GlobalVariables::GetVector2Value(const std::string& groupName, const std::string& key) {
	// 指定したグループが存在するかをassertで確認
	assert(datas_.find(groupName) != datas_.end());

	// 指定したグループの参照を取得
	Group& group = datas_[groupName];

	// 指定したキーが存在するかをassertで確認
	assert(group.items.find(key) != group.items.end());

	return std::get<Vector2>(group.items[key].value);
}

Vector3 GlobalVariables::GetVector3Value(const std::string& groupName, const std::string& key) {
	// 指定したグループが存在するかをassertで確認
	assert(datas_.find(groupName) != datas_.end());

	// 指定したグループの参照を取得
	Group& group = datas_[groupName];

	// 指定したキーが存在するかをassertで確認
	assert(group.items.find(key) != group.items.end());

	return std::get<Vector3>(group.items[key].value);
}

Vector4 GlobalVariables::GetVector4Value(const std::string& groupName, const std::string& key) {
	// 指定したグループが存在するかをassertで確認
	assert(datas_.find(groupName) != datas_.end());

	// 指定したグループの参照を取得
	Group& group = datas_[groupName];

	// 指定したキーが存在するかをassertで確認
	assert(group.items.find(key) != group.items.end());

	return std::get<Vector4>(group.items[key].value);
}

#pragma endregion

#pragma region Set

void GlobalVariables::SetValue(
	const std::string& groupName, const std::string& key, int32_t value) {
	// グループの参照を取得
	Group& group = datas_[groupName];
	// 新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	// 設定した項目をstd::mapに追加
	group.items[key] = newItem;
}

void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, float value) {
	// グループの参照を取得
	Group& group = datas_[groupName];
	// 新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	// 設定した項目をstd::mapに追加
	group.items[key] = newItem;
}

void GlobalVariables::SetValue(
	const std::string& groupName, const std::string& key, Vector2& value) {
	// グループの参照を取得
	Group& group = datas_[groupName];
	// 新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	// 設定した項目をstd::mapに追加
	group.items[key] = newItem;
}

void GlobalVariables::SetValue(
	const std::string& groupName, const std::string& key, Vector3& value) {
	// グループの参照を取得
	Group& group = datas_[groupName];
	// 新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	// 設定した項目をstd::mapに追加
	group.items[key] = newItem;
}

void GlobalVariables::SetValue(
	const std::string& groupName, const std::string& key, Vector4& value) {
	// グループの参照を取得
	Group& group = datas_[groupName];
	// 新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	// 設定した項目をstd::mapに追加
	group.items[key] = newItem;
}

#pragma endregion

#pragma region 追加

void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, int32_t value) {
	// 指定したグループの参照を取得
	Group& group = datas_[groupName];
	// 項目が未登録なら
	if (group.items.find(key) == group.items.end()) {
		SetValue(groupName, key, value);
	}
}

void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, float value) {
	// 指定したグループの参照を取得
	Group& group = datas_[groupName];
	// 項目が未登録なら
	if (group.items.find(key) == group.items.end()) {
		SetValue(groupName, key, value);
	}
}

void GlobalVariables::AddItem(
	const std::string& groupName, const std::string& key, Vector2& value) {
	// 指定したグループの参照を取得
	Group& group = datas_[groupName];
	// 項目が未登録なら
	if (group.items.find(key) == group.items.end()) {
		SetValue(groupName, key, value);
	}
}

void GlobalVariables::AddItem(
	const std::string& groupName, const std::string& key, Vector3& value) {
	// 指定したグループの参照を取得
	Group& group = datas_[groupName];
	// 項目が未登録なら
	if (group.items.find(key) == group.items.end()) {
		SetValue(groupName, key, value);
	}
}

void GlobalVariables::AddItem(
	const std::string& groupName, const std::string& key, Vector4& value) {
	// 指定したグループの参照を取得
	Group& group = datas_[groupName];
	// 項目が未登録なら
	if (group.items.find(key) == group.items.end()) {
		SetValue(groupName, key, value);
	}
}

#pragma endregion

void GlobalVariables::CreateGroup(const std::string& groupName) {
	// 指定名のオブジェクトがなければ追加する
	datas_[groupName];
}

void GlobalVariables::SaveFile(const std::string& groupName) {
	// グループを検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);

	// 未登録チェック
	assert(itGroup != datas_.end());

	nlohmann::json root;
	root = nlohmann::json::object();

	// jsonオブジェクトの登録
	root[groupName] = nlohmann::json::object();
	// 各項目について
	for (std::map<std::string, Item>::iterator itItem = itGroup->second.items.begin();
		itItem != itGroup->second.items.end(); ++itItem) {
		// 項目名を取得
		const std::string& itemName = itItem->first;
		// 項目の参照を取得
		Item& item = itItem->second;

		// int32_tの値を保持している場合
		if (std::holds_alternative<int32_t>(item.value)) {
			// int32_tの値の登録
			root[groupName][itemName] = std::get<int32_t>(item.value);
		} // floatの値を保持している場合
		else if (std::holds_alternative<float>(item.value)) {
			// floatの値の登録
			root[groupName][itemName] = std::get<float>(item.value);
		} // Vector2の値を保持している場合
		if (std::holds_alternative<Vector2>(item.value)) {
			// Vector2の値の登録
			Vector2 value = std::get<Vector2>(item.value);
			root[groupName][itemName] = nlohmann::json::array({ value.x, value.y });
		} // Vector3の値を保持している場合
		if (std::holds_alternative<Vector3>(item.value)) {
			// Vector3の値の登録
			Vector3 value = std::get<Vector3>(item.value);
			root[groupName][itemName] = nlohmann::json::array({ value.x, value.y, value.z });
		}// Vector4の値を保持している場合
		if (std::holds_alternative<Vector4>(item.value)) {
			// Vector4の値の登録
			Vector4 value = std::get<Vector4>(item.value);
			root[groupName][itemName] = nlohmann::json::array({ value.x, value.y, value.z, value.w });
		}
	}
	// ディレクトリがなければ作成する
	std::filesystem::path dir(kDirectoryPath);
	if (!std::filesystem::exists(kDirectoryPath)) {
		std::filesystem::create_directory(kDirectoryPath);
	}

	// 書き込むJSONファイルのフルパスを合成する
	std::string filePath = kDirectoryPath + groupName + ".json";
	// 書き込み用ファイルストリーム
	std::ofstream ofs{};
	// ファイルを書き込みように開く
	ofs.open(filePath);

	// ファイルオープン失敗？
	if (ofs.fail()) {
		std::string message = "Failed open data file for write.";
		MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		assert(0);
		return;
	}
	// ファイルにjson文字列を書き込む(インデント幅4)
	ofs << std::setw(4) << root << std::endl;
	// ファイルを閉じる
	ofs.close();
}

void GlobalVariables::LoadFile(const std::string& groupName) {
	// 読み込むJSONファイルのフルパスを合成する
	std::string filePath = kDirectoryPath + groupName + ".json";
	// 読み込み用ファイルストリーム
	std::ifstream ifs;
	// ファイルを読み込み用に開く
	ifs.open(filePath);

	// ファイルオープン失敗?
	if (ifs.fail()) {
		std::string message = "Failed open data file for write.";
		MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		assert(0);
		return;
	}

	nlohmann::json root;

	// json文字列からjsonのデータ構造に展開
	ifs >> root;
	// ファイルを閉じる
	ifs.close();

	// グループを検索
	nlohmann::json::iterator itGroup = root.find(groupName);

	// 未登録チェック
	assert(itGroup != root.end());
	// 各アイテムについて
	for (nlohmann::json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {
		// アイテム名を取得
		const std::string& itemName = itItem.key();

		// int32_tの値を保持している場合
		if (itItem->is_number_integer()) {
			// int型の値を登録
			int32_t value = itItem->get<int32_t>();
			SetValue(groupName, itemName, value);
		} // floatの値を保持している場合
		else if (itItem->is_number_float()) {
			// double型の値を登録
			double value = itItem->get<double>();
			SetValue(groupName, itemName, static_cast<float>(value));
		} // 要素数2の配列の場合
		else if (itItem->is_array() && itItem->size() == 2) {
			// float型の値を登録
			Vector2 value = { itItem->at(0), itItem->at(1) };
			SetValue(groupName, itemName, value);
		}// 要素数3の配列の場合
		else if (itItem->is_array() && itItem->size() == 3) {
			// float型の値を登録
			Vector3 value = { itItem->at(0), itItem->at(1), itItem->at(2) };
			SetValue(groupName, itemName, value);
		}// 要素数4の配列の場合
		else if (itItem->is_array() && itItem->size() == 4) {
			// float型の値を登録
			Vector4 value = { itItem->at(0), itItem->at(1), itItem->at(2), itItem->at(3) };
			SetValue(groupName, itemName, value);
		}
	}
}

void GlobalVariables::LoadFiles() {
	// ディレクトリがなければスキップする
	std::filesystem::path dir(kDirectoryPath);
	if (!std::filesystem::exists(kDirectoryPath)) {
		return;
	}

	std::filesystem::directory_iterator dir_it(kDirectoryPath);
	for (const std::filesystem::directory_entry& entry : dir_it) {
		// ファイルパスを取得
		const std::filesystem::path& filePath = entry.path();

		// ファイル拡張子を取得
		std::string extension = filePath.extension().string();
		// .jsonファイル以外はスキップ
		if (extension.compare(".json") != 0) {
			continue;
		}
		// ファイル読み込み
		LoadFile(filePath.stem().string());
	}
}

void GlobalVariables::Update() {
	if (!ImGui::Begin("Global Variables", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		return;
	}
	if (!ImGui::BeginMenuBar())
		return;

	for (std::map<std::string, Group>::iterator itGroup = datas_.begin(); itGroup != datas_.end();
		++itGroup) {
		// グループ名を取得
		const std::string& groupName = itGroup->first;
		// グループの参照を取得
		Group& group = itGroup->second;

		if (!ImGui::BeginMenu(groupName.c_str()))
			continue;

		// 各項目について
		for (std::map<std::string, Item>::iterator itItem = group.items.begin();
			itItem != group.items.end(); ++itItem) {
			// 各項目を取得
			const std::string& itemName = itItem->first;
			// 項目の参照を取得
			Item& item = itItem->second;
			// int32_tの値を保持している場合
			if (std::holds_alternative<int32_t>(item.value)) {
				int32_t* ptr = std::get_if<int32_t>(&item.value);
				ImGui::SliderInt(itemName.c_str(), ptr, 0, 100);
			} // floatの値を保持している場合
			else if (std::holds_alternative<float>(item.value)) {
				float* ptr = std::get_if<float>(&item.value);
				ImGui::SliderFloat(itemName.c_str(), ptr, 0, 100);
			} // Vector2の値を保持している場合
			else if (std::holds_alternative<Vector2>(item.value)) {
				Vector2* ptr = std::get_if<Vector2>(&item.value);
				ImGui::SliderFloat2(itemName.c_str(), reinterpret_cast<float*>(ptr), -10.0f, 10.0f);
			}// Vector3の値を保持している場合
			else if (std::holds_alternative<Vector3>(item.value)) {
				Vector3* ptr = std::get_if<Vector3>(&item.value);
				ImGui::SliderFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr), -10.0f, 10.0f);
			}// Vector4の値を保持している場合
			else if (std::holds_alternative<Vector4>(item.value)) {
				Vector4* ptr = std::get_if<Vector4>(&item.value);
				ImGui::ColorEdit4(itemName.c_str(), reinterpret_cast<float*>(ptr));
			}
		}

		// 改行
		ImGui::Text("\n");

		if (ImGui::Button("Save")) {
			SaveFile(groupName);
			std::string message = std::format("{}.json saved.", groupName);
			MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
			isSave_ = true;
		}
		if (isSave_) {
			isSave_ = false;
		}
		ImGui::EndMenu();
	}


	ImGui::EndMenuBar();
	ImGui::End();
}