#include "engine/subsystems/ingame-debug/StatsManager.h"
using namespace GLESC;
std::unordered_map<std::string, std::string> StatsManager::getStats() {
    std::unordered_map<std::string, std::string> result;
    for (auto& source : sources) {
        result[source.first] = source.second();
    }
    return result;
}

std::map<std::string, std::function<std::string()>> StatsManager::sources = {};