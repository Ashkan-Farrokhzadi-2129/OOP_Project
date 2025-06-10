#include "SchematicManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

SchematicManager::SchematicManager(const std::string& directory) : directory(directory) {
    loadSchematics();
}

void SchematicManager::loadSchematics() {
    schematicFiles.clear();
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            schematicFiles.push_back(entry.path().filename().string());
        }
    }
}

std::vector<std::string> SchematicManager::listSchematics() const {
    return schematicFiles;
}

int SchematicManager::getSchematicCount() const {
    return static_cast<int>(schematicFiles.size());
}

std::string SchematicManager::getSchematicContent(int index) const {
    if (index < 0 || index >= schematicFiles.size()) return "";
    std::ifstream file(directory + "/" + schematicFiles[index]);
    if (!file) return "";
    std::string line, content;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    return content;
}