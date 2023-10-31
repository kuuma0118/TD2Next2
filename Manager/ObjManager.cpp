#include "ObjManager.h"
#include <cassert>

ObjManager* ObjManager::GetInstance() {
	static ObjManager instance;

	return &instance;
}

void ObjManager::Initialize() {
	LoadObjFiles();
}

void ObjManager::LoadObjFiles() {
	modelData_[block] = LoadObjFile("Resources/block", "block.obj");
	modelData_[player] = LoadObjFile("Resources/player", "player.obj");
	//modelData_[MULTIMESH] = LoadObjFile("resources", "multiMesh.obj");
	//modelData_[MULTIMATERIAL] = LoadObjFile("resources", "multiMaterial.obj");
	//modelData_[BUNNY] = LoadObjFile("resources", "bunny.obj");
}

ModelData ObjManager::LoadObjFile(const std::string& directoryPath, const std::string& filename) {
	ModelData modelData;
	std::vector<Vector4> positions;
	std::vector<Vector3> normals;
	std::vector<Vector2> texcoords;
	std::string line;
	// ファイルを開く
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());

	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;
		// 頂点情報を読む
		if (identifier == "v") {
			Vector4 position;
			s >> position.x >> position.y >> position.z;
			position.z *= -1.0f;
			position.w = 1.0f;
			positions.push_back(position);
		}
		else if (identifier == "vt") {
			Vector2 texcoord{};
			s >> texcoord.x >> texcoord.y;
			texcoord.y = 1.0f - texcoord.y;
			texcoords.push_back(texcoord);
		}
		else if (identifier == "vn") {
			Vector3 normal;
			s >> normal.x >> normal.y >> normal.z;
			normal.z *= -1.0f;
			normals.push_back(normal);
		}
		else if (identifier == "f") {
			VertexData triangle[3];
			for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
				std::string vertexDefinition;
				s >> vertexDefinition;
				// 頂点要素へのIndexを取得
				std::istringstream v(vertexDefinition);
				uint32_t elementIndices[3];
				for (int32_t element = 0; element < 3; ++element) {
					std::string index;
					// /区切りで読んでいく
					std::getline(v, index, '/');
					elementIndices[element] = std::stoi(index);
				}
				// 要素へのIndexから、実際の値を取得して、頂点を構築する
				Vector4 position = positions[elementIndices[0] - 1];
				Vector2 texcoord = texcoords[elementIndices[1] - 1];
				Vector3 normal = normals[elementIndices[2] - 1];
				VertexData vertex = { position, texcoord, normal };
				modelData.verticles.push_back(vertex);
				triangle[faceVertex] = { position,texcoord,normal };
			}
			modelData.verticles.push_back(triangle[2]);
			modelData.verticles.push_back(triangle[1]);
			modelData.verticles.push_back(triangle[0]);
		}
		else if (identifier == "mtllib") {
			// materilTemplateLibraryファイルの名前を取得
			std::string materialFilename;
			s >> materialFilename;
			// 基本的にobjファイルと同一階層にmtlは存在させるので、ディレクトリ名とファイル名を渡す
			modelData.material = LoadMaterialTemplateFile(directoryPath, materialFilename);
		}
	}

	return modelData;
}