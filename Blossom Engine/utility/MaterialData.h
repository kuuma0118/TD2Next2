#pragma once
#include <string>
#include <fstream>
#include <sstream>

struct MaterialData {
	std::string textureFilePath;
};

MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);