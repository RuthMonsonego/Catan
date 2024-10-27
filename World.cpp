#include "World.h"
#include "Resource.h"
#include "ConfigurationManager.h"
#include "SettlementPoints.h"
#include <iostream>
#include <memory>

using namespace std;

static World* instance = nullptr;

void PlaceTheNewSettlement(shared_ptr<SettlementPoints> newSettlement, int coordinateX, int coordinateY) {

	World& world = World::getInstance();
	int* sizes = ConfigurationManager::getSizeFromConfig(newSettlement.get()->getKindResourceCode());
	for (int i = 0; i < sizes[0] / 5; i++)
		for (int j = 0; j < sizes[1] / 5; j++)
			world.world[coordinateX + i][coordinateY + j].setResource(newSettlement);
}

void PlaceTheNewVehicle(shared_ptr<MovingCarryingItem> newVehicle, int coordinateX, int coordinateY) {

	World& world = World::getInstance();
	int* sizes = ConfigurationManager::getSizeFromConfig(newVehicle.get()->getKindCode());
	for (int i = 0; i < sizes[0]; i++)
		for (int j = 0; j < sizes[1]; j++)
			world.world[(coordinateX + i) / 5][(coordinateY + j) / 5].coordinates[(coordinateX + i) % 5][(coordinateY + j) % 5].setTerrestrialItem(newVehicle);
}

void AddInfrastructure(int kind) {
	switch (kind)
	{
	case 7:
		World::getInstance().addVillage();
		break;
	case 8:
		World::getInstance().addCity();
		break;
	case 9:
		World::getInstance().addRoad();
		break;
	default:
		break;
	}
}

vector<vector<string>> World::transposeMatrix(const vector<vector<string>>& matrix) {
	int rows = matrix.size();
	int cols = matrix[0].size();
	vector<vector<string>> transposed(cols, vector<string>(rows));
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			transposed[j][i] = matrix[i][j];
		}
	}
	return transposed;
}

World::World(vector<vector<string>> mat) : countCities(0), countVillages(0), countRoads(0) {
	vector<vector<string>> matForBuildingWorld = transposeMatrix(mat);
	for (const vector<string> inner_vec : matForBuildingWorld) {
		vector<Tile> newLine;
		for (const string& kind : inner_vec) {
			shared_ptr<Resource> sharedResource = make_shared<Resource>(stoi(kind));
			Tile t(sharedResource);
			newLine.emplace_back(t);
		}
		world.emplace_back(newLine);
	}
}

World& World::createInstance(vector<vector<string>> mat) {
	if (!instance) {
		instance = new World(mat);
	}
	return *instance;
}

World& World::getInstance() {
	return *instance;
}

int World::getCountCities() {
	return countCities;
}

int World::getCountVillages() {
	return countVillages;
}

int World::getCountRoads() {
	return countRoads;
}

int World::getSelectedCoordinateX() {
	return selectedCoordinateX;
}

int World::getSelectedCoordinateY() {
	return selectedCoordinateY;
}

void World::addCity() {
	countCities++;
}

void World::addVillage() {
	countVillages++;
}

void World::addRoad() {
	countRoads++;
}

void World::buildSettlementFromInput(int coordinateX, int coordinateY, int kind) {

	//take the resource
	//check if there is access to road in at least 2 points
	int* sizes = ConfigurationManager::getSizeFromConfig(kind);
	sizes[0] /= 5;
	sizes[1] /= 5;
	bool adjacentsToRoad = false;
	for (int i = coordinateY; i < coordinateY + sizes[1] && !adjacentsToRoad; i++) {
		if (coordinateX - 1 >= 0 && world[coordinateX - 1][i].getResource().get()->getKindResourceCode() == 9)
			adjacentsToRoad = true;
		if (coordinateX + sizes[0] < world.size() && world[coordinateX + sizes[0]][i].getResource().get()->getKindResourceCode() == 9)
			adjacentsToRoad = true;
	}
	for (int i = coordinateX; i < coordinateX + sizes[0] && !adjacentsToRoad; i++) {
		if (coordinateY - 1 >= 0 && world[i][coordinateY - 1].getResource().get()->getKindResourceCode() == 9)
			adjacentsToRoad = true;
		if (coordinateY + sizes[1] < world[i].size() && world[i][coordinateY + sizes[1]].getResource().get()->getKindResourceCode() == 9)
			adjacentsToRoad = true;
	}
	if (adjacentsToRoad) {
		//create the settlement
		shared_ptr<SettlementPoints> newSettlement = make_shared<SettlementPoints>(kind, false);
		//place the settlement
		PlaceTheNewSettlement(newSettlement, coordinateX, coordinateY);
	}
}

void World::finishBuildingFromInput(int coordinateX, int coordinateY, int kind) {
	if (world[coordinateX][coordinateY].getResource().get()->getKindResourceCode() == kind) {
		//defining the construction as complete
		//((SettlementPoints*)world[coordinateX][coordinateY].getResource().get())->setIsComplete(true);
		//add one infrastructure to the counter
		AddInfrastructure(kind);
	}
}

void World::manufactorVehicle(int coordinateX, int coordinateY, int kind) {

	shared_ptr<MovingCarryingItem> newVehicle = make_shared<MovingCarryingItem>(kind);
	if (kind == 11)
		((SettlementPoints*)world[coordinateX / 5][coordinateY / 5].getResource().get())->setCurrentAmountCars(((SettlementPoints*)world[coordinateX / 5][coordinateY / 5].getResource().get())->getCurrentAmountCars() + 1);
	else if (kind == 12)
		((SettlementPoints*)world[coordinateX / 5][coordinateY / 5].getResource().get())->setCurrentAmountTrucks(((SettlementPoints*)world[coordinateX / 5][coordinateY / 5].getResource().get())->getCurrentAmountTrucks() + 1);
	PlaceTheNewVehicle(newVehicle, coordinateX, coordinateY);
}

void World::buildSettlementFromStart(int coordinateX, int coordinateY, int kind) {

	shared_ptr<SettlementPoints> newSettlement = make_shared<SettlementPoints>(kind, true);
	PlaceTheNewSettlement(newSettlement, coordinateX, coordinateY);
	AddInfrastructure(kind);
}

void World::selectCoordinate(int x, int y) {

	selectedCoordinateX = x;
	selectedCoordinateY = y;
}

void World::rain(int amount) {

	for (int i = 0; i < world.size(); i++) {
		for (int j = 0; j < world[i].size(); j++) {
			if (world[i][j].getResource().get()->getKindResourceCode() == 3 || world[i][j].getResource().get()->getKindResourceCode() == 4)
				world[i][j].getResource().get()->addOneToCurrentAmountResources();
		}
	}
}