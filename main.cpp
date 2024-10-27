#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "Input.h"
#include "Command.h"
#include "CommandType.h"
#include "MovingCarryingItem.h"
#include "ConfigurationManager.h"

using namespace std;

int main()
{
	//+World
	Input i;
	vector<vector<string>> vec = i.parse_and_store();
	World& world = World::createInstance(vec);

	//+Start
	unordered_map<string, int> buildItems = {
		{"Village", 7},
		{"City", 8},
		{"Road", 9},
		{"Car", 11},
		{"Truck", 12},
		{"Helicopter", 13}
	};
	for (shared_ptr<Command> startCommand : i.start) {

		shared_ptr<MovingCarryingItem> sharedPerson = make_shared<MovingCarryingItem>(10);
		switch (startCommand.get()->commandType) {

		case CommandType::RESOURCE:
			//change the resource amount
			if (world.world[(stoi(startCommand.get()->arguments[2]) - 1) / 5][(stoi(startCommand.get()->arguments[3]) - 1) / 5].getResource().get()->getKindResourceCode() == 1) {
				world.world[(stoi(startCommand.get()->arguments[2]) - 1) / 5][(stoi(startCommand.get()->arguments[3]) - 1) / 5].coordinates[(stoi(startCommand.get()->arguments[2]) - 1) % 5][(stoi(startCommand.get()->arguments[3]) - 1) % 5].getTerrestrialItem().get()->addAmountToContemporaryCarrying(startCommand.get()->arguments[1], stoi(startCommand.get()->arguments[0]));
			}
			else if (world.world[(stoi(startCommand.get()->arguments[2]) - 1) / 5][(stoi(startCommand.get()->arguments[3]) - 1) / 5].getResource().get()->getKindResourceCode() == 7 || world.world[(stoi(startCommand.get()->arguments[2]) - 1) / 5][(stoi(startCommand.get()->arguments[3]) - 1) / 5].getResource().get()->getKindResourceCode() == 8) {
				((SettlementPoints*)world.world[(stoi(startCommand.get()->arguments[2]) - 1) / 5][(stoi(startCommand.get()->arguments[3]) - 1) / 5].getResource().get())->addAmountToContemporaryStorage(startCommand.get()->arguments[1], stoi(startCommand.get()->arguments[0]));
			}
			else {
				world.world[(stoi(startCommand.get()->arguments[2]) - 1) / 5][(stoi(startCommand.get()->arguments[3]) - 1) / 5].getResource().get()->setCurrentAmountResources(stoi(startCommand.get()->arguments[0]));
			}
			break;

		case CommandType::PEOPLE:
			//create person in this coordinate
			world.world[(stoi(startCommand.get()->arguments[1]) - 1) / 5][(stoi(startCommand.get()->arguments[2]) - 1) / 5].coordinates[(stoi(startCommand.get()->arguments[1]) - 1) % 5][(stoi(startCommand.get()->arguments[2]) - 1) % 5].setTerrestrialItem(sharedPerson);
			//change the people amount in this tail
			world.world[(stoi(startCommand.get()->arguments[1]) - 1) / 5][(stoi(startCommand.get()->arguments[2]) - 1) / 5].getResource().get()->addOneToCurrentAmountResources();
			break;

		case CommandType::BUILD:
			//build the infrastructure
			world.buildSettlementFromStart((stoi(startCommand.get()->arguments[1]) - 1) / 5, (stoi(startCommand.get()->arguments[2]) - 1) / 5, buildItems[startCommand.get()->arguments[0]]);
			break;

		case CommandType::MANUFACTURE:
			world.manufactorVehicle(stoi(startCommand.get()->arguments[1]) - 1, stoi(startCommand.get()->arguments[2]) - 1, buildItems[startCommand.get()->arguments[0]]);
			break;
		}
	}

	//+Input
	shared_ptr<Command> prevCommand;
	for (shared_ptr<Command> inputCommand : i.steps) {

		switch (inputCommand.get()->commandType) {

		case CommandType::SELECT:
			//change the selected coordinate
			world.selectCoordinate(stoi(inputCommand.get()->arguments[0]) - 1, stoi(inputCommand.get()->arguments[1]) - 1);
			break;

		case CommandType::WORK:
			//move him to the current place
			world.world[(stoi(inputCommand.get()->arguments[0]) - 1) / 5][(stoi(inputCommand.get()->arguments[1]) - 1) / 5].coordinates[(stoi(inputCommand.get()->arguments[0]) - 1) % 5][(stoi(inputCommand.get()->arguments[1]) - 1) % 5].setTerrestrialItem(world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].coordinates[world.getSelectedCoordinateX() % 5][world.getSelectedCoordinateY() % 5].getTerrestrialItem());
			//reduce one person fron the old tail
			world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].coordinates[world.getSelectedCoordinateX() % 5][world.getSelectedCoordinateY() % 5].setTerrestrialItem(nullptr);
			// add one person to the new tail
			if (world.world[(stoi(inputCommand.get()->arguments[0]) - 1) / 5][(stoi(inputCommand.get()->arguments[1]) - 1) / 5].getResource().get()->getKindResourceCode() == 7 || world.world[(stoi(inputCommand.get()->arguments[0]) - 1) / 5][(stoi(inputCommand.get()->arguments[1]) - 1) / 5].getResource().get()->getKindResourceCode() == 8)
				world.world[(stoi(inputCommand.get()->arguments[0]) - 1) / 5][(stoi(inputCommand.get()->arguments[1]) - 1) / 5].getResource().get()->addOneToCurrentAmountResources();
			break;

		case CommandType::WAIT:
			switch (prevCommand.get()->commandType)
			{
			case CommandType::RAIN:
				world.rain(stoi(inputCommand.get()->arguments[0]) - stoi(prevCommand.get()->arguments[0]));
				break;
			case CommandType::BUILD:
				world.finishBuildingFromInput((stoi(prevCommand.get()->arguments[1]) - 1) / 5, (stoi(prevCommand.get()->arguments[2]) - 1) / 5, buildItems[prevCommand.get()->arguments[0]]);
				break;
			case CommandType::DEPOSIT:
				((SettlementPoints*)world.world[(stoi(prevCommand.get()->arguments[0]) - 1) / 5][(stoi(prevCommand.get()->arguments[1]) - 1) / 5].getResource().get())->addForAllResources(world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].coordinates[world.getSelectedCoordinateX() % 5][world.getSelectedCoordinateY() % 5].getTerrestrialItem().get()->getContemporaryCarrying());
				break;
			case CommandType::TAKE_RESOURCES:
				for (int index = 0; index < 4; index++) {
					int amountInStorage = ((SettlementPoints*)world.world[(stoi(prevCommand.get()->arguments[0]) - 1) / 5][(stoi(prevCommand.get()->arguments[1]) - 1) / 5].getResource().get())->getAmountOfResourceInStorage(index);
					int amountStayPlace = ((MovingCarryingItem*)world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].coordinates[world.getSelectedCoordinateX() % 5][world.getSelectedCoordinateY() % 5].getTerrestrialItem().get())->getAmountStayPlace(index);
					if (amountStayPlace > 0) {
						if (amountStayPlace < amountInStorage) {
							((SettlementPoints*)world.world[(stoi(prevCommand.get()->arguments[0]) - 1) / 5][(stoi(prevCommand.get()->arguments[1]) - 1) / 5].getResource().get())->setAmountOfResourceInStorage(index, amountInStorage - amountStayPlace);
							((MovingCarryingItem*)world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].coordinates[world.getSelectedCoordinateX() % 5][world.getSelectedCoordinateY() % 5].getTerrestrialItem().get())->setAmountInStorage(index, ((MovingCarryingItem*)world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].coordinates[world.getSelectedCoordinateX() % 5][world.getSelectedCoordinateY() % 5].getTerrestrialItem().get())->getAmountInStorage(index) + amountStayPlace);
						}
						else {
							((SettlementPoints*)world.world[(stoi(prevCommand.get()->arguments[0]) - 1) / 5][(stoi(prevCommand.get()->arguments[1]) - 1) / 5].getResource().get())->setAmountOfResourceInStorage(index, 0);
							((MovingCarryingItem*)world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].coordinates[world.getSelectedCoordinateX() % 5][world.getSelectedCoordinateY() % 5].getTerrestrialItem().get())->setAmountInStorage(index, ((MovingCarryingItem*)world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].coordinates[world.getSelectedCoordinateX() % 5][world.getSelectedCoordinateY() % 5].getTerrestrialItem().get())->getAmountInStorage(index) + amountInStorage);
						}
					}
				}
				break;
			case CommandType::WORK:
				world.world[(stoi(prevCommand.get()->arguments[0]) - 1) / 5][(stoi(prevCommand.get()->arguments[1]) - 1) / 5].getResource().get()->TakeOneResourceTone();
				break;
			default:
				break;
			}
			break;

		case CommandType::BUILD:
			//build the infrastructure
			world.buildSettlementFromInput((stoi(inputCommand.get()->arguments[1]) - 1) / 5, (stoi(inputCommand.get()->arguments[2]) - 1) / 5, buildItems[inputCommand.get()->arguments[0]]);
			break;

		case CommandType::MAKE_EMPTY:
			//reset the resouce amount
			world.world[(stoi(inputCommand.get()->arguments[0]) - 1) / 5][(stoi(inputCommand.get()->arguments[1]) - 1) / 5].getResource().get()->setCurrentAmountResources(0);
			if (world.world[(stoi(inputCommand.get()->arguments[0]) - 1) / 5][(stoi(inputCommand.get()->arguments[1]) - 1) / 5].getResource().get()->getKindResourceCode() > 6 && world.world[(stoi(inputCommand.get()->arguments[0]) - 1) / 5][(stoi(inputCommand.get()->arguments[1]) - 1) / 5].getResource().get()->getKindResourceCode() < 10)
				((SettlementPoints*)world.world[(stoi(inputCommand.get()->arguments[0]) - 1) / 5][(stoi(inputCommand.get()->arguments[1]) - 1) / 5].getResource().get())->ResetAllResources();
			break;

		case CommandType::PEOPLE:
			world.world[(stoi(inputCommand.get()->arguments[1]) - 1) / 5][(stoi(inputCommand.get()->arguments[2]) - 1) / 5].getResource().get()->setCurrentAmountResources(world.world[(stoi(inputCommand.get()->arguments[1]) - 1) / 5][(stoi(inputCommand.get()->arguments[2]) - 1) / 5].getResource().get()->getCurrentAmountResources() + stoi(inputCommand.get()->arguments[0]));
			break;

		default:
			break;
		}
		prevCommand = inputCommand;
	}

	//+Asserts
	unordered_map<string, int> assertCases = {
		{"SelectedResource", 1},
		{"SelectedCategory", 2},
		{"SelectedComplete", 3},
		{"CityCount", 4},
		{"VillageCount", 5},
		{"RoadCount", 6},
		{"SelectedPeople", 7},
		{"SelectedCar", 8},
		{"SelectedTruck", 9}
	};

	for (string assertCommand : i.asserts) {

		cout << assertCommand;
		switch (assertCases[assertCommand]) {

		case 1:
			//print amount for every resource in the current tail
			if (world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].getResource().get()->getKindResourceCode() < 7)
				for (int i = 3; i <= 6; i++)
				{
					if (i == world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].getResource().get()->getKindResourceCode())
						cout << " " << world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].getResource().get()->getCurrentAmountResources();
					else
						cout << " 0";
				}
			else if (world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].getResource().get()->getKindResourceCode() < 10) {
				((SettlementPoints*)world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].getResource().get())->printAlllResources();
			}
			break;

		case 2:
			cout << " " << ConfigurationManager::getTileKindName(world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].getResource().get()->getKindResourceCode());
			break;

		case 3:
			if (((SettlementPoints*)world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].getResource().get())->getIsComplete())
				cout << " True";
			else
				cout << " False";
			break;

		case 4:
			cout << " " << world.getCountCities();
			break;

		case 5:
			cout << " " << world.getCountVillages();
			break;

		case 6:
			cout << " " << world.getCountRoads();
			break;

		case 7:
			cout << " " << world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].getResource().get()->getCurrentAmountResources();
			break;

		case 8:
			cout << " " << ((SettlementPoints*)world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].getResource().get())->getCurrentAmountCars();
			break;

		case 9:
			cout << " " << ((SettlementPoints*)world.world[world.getSelectedCoordinateX() / 5][world.getSelectedCoordinateY() / 5].getResource().get())->getCurrentAmountTrucks();
			break;
		}
		cout << endl;
	}

	//print the world
	//for (int i = 0; i < world.world.size(); i++) {
	//	for (int j = 0; j < world.world[i].size(); j++) {
	//		cout << world.world[i][j].getResource().get()->getKindResourceCode() << "  ";
	//	}
	//	cout << endl;
	//}

	return 0;
}