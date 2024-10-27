#include "ConfigurationManager.h"
#include <iostream>

json ConfigurationManager::config;

void ConfigurationManager::initializeTheJson() {

    if (config.empty()) {
        try {
            std::ifstream jsonFile("Config.json");
            if (!jsonFile.is_open())
                throw std::runtime_error("File not found");

            jsonFile >> config;
            jsonFile.close();
        }
        catch (const std::exception& e) {
            throw std::logic_error("Configuration file is not available: " + std::string(e.what()));
        }
    }
}

std::string ConfigurationManager::getTileKindName(int kindTile) {

    initializeTheJson();
    for (auto& tile : config["Tiles"].items()) {
        if (tile.value() == kindTile) {
            return tile.key();
        }
    }
    return "";
}

int* ConfigurationManager::getSizeFromConfig(int kind) {

    initializeTheJson();
    int* sizes = new int[2];
    if (kind < 7) {
        sizes[0] = config["Sizes"]["Tile"][0];
        sizes[1] = config["Sizes"]["Tile"][1];
    }
    else {
        sizes[0] = config["Sizes"][getTileKindName(kind)][0];
        sizes[1] = config["Sizes"][getTileKindName(kind)][1];
    }
    return sizes;
}

int ConfigurationManager::getMaxResouceAmount(int kind) {

    initializeTheJson();
    if (kind == 7 || kind == 8) {
        return config["Capacities"][getTileKindName(kind)][4];
    }
    return getStartResouceAmount(kind);
}

int ConfigurationManager::getStartResouceAmount(int kind) {

    initializeTheJson();
    if (kind < 3 || kind == 9)
        return 0;
    return config["StartingResources"][getTileKindName(kind)];
}

int ConfigurationManager::getMaxCapacity(int kindTile, int kindResourceIndex) {

    initializeTheJson();
    return config["Capacities"][getTileKindName(kindTile)][kindResourceIndex];
}

int ConfigurationManager::convertResourceToIndex(std::string kindTile) {

    initializeTheJson();
    for (int i = 0; i < config["ResourceTypes"].size(); i++) {
        if (config["ResourceTypes"][i] == kindTile)
            return i;
    }
}

