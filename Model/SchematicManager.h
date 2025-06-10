//
// Created by asus on 6/10/2025.
//

#ifndef SCHEMATICMANAGER_H
#define SCHEMATICMANAGER_H



#include <vector>
#include <string>

class SchematicManager {
public:
    SchematicManager(const std::string& directory);
    std::vector<std::string> listSchematics() const;
    std::string getSchematicContent(int index) const;
    int getSchematicCount() const;
private:
    std::vector<std::string> schematicFiles;
    std::string directory;
    void loadSchematics();
};



#endif //SCHEMATICMANAGER_H
