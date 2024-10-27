#pragma once

#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

class ConfigurationManager {
private:
    static json config;

public:
    static std::string getTileKindName(int kindTile);
    static int convertResourceToIndex(std::string kindTile);
    static int* getSizeFromConfig(int kind);
    static int getStartResouceAmount(int kind);
    static int getMaxResouceAmount(int kind);
    static void initializeTheJson();
    static int getMaxCapacity(int kindTile, int kindResourceIndex);
};
