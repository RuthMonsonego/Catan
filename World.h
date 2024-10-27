#pragma once

#include <vector>
#include <string>
#include "Tile.h"

class World {
private:
    int countCities;
    int countVillages;
    int countRoads;
    int selectedCoordinateX;
    int selectedCoordinateY;

    std::vector<std::vector<std::string>> transposeMatrix(const std::vector<std::vector<std::string>>& matrix);

    World(std::vector<std::vector<std::string>> mat);

public:
    std::vector<std::vector<Tile>> world;

    static World& createInstance(std::vector<std::vector<std::string>> mat);
    static World& getInstance();

    World(const World&) = delete;
    World& operator=(const World&) = delete;

    int getCountCities();
    int getCountVillages();
    int getCountRoads();
    int getSelectedCoordinateX();
    int getSelectedCoordinateY();
    void addCity();
    void addVillage();
    void addRoad();
    void buildSettlementFromStart(int coordinateX, int coordinateY, int kind);
    void manufactorVehicle(int coordinateX, int coordinateY, int kind);
    void selectCoordinate(int x, int y);
    void finishBuildingFromInput(int coordinateX, int coordinateY, int kind);
    void buildSettlementFromInput(int coordinateX, int coordinateY, int kind);
    void rain(int amount);
};
