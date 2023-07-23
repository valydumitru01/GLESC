#pragma once
#include <fstream>
#include <sstream>
class FileManager {
public:
    static std::string readFile(const std::string &path);
    static void writeFile(const std::string &path, const std::string &content);
private:
};
