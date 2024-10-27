#include "SettlementPoints.h"
#include "ConfigurationManager.h"
#include <iostream>

SettlementPoints::SettlementPoints(int kind, bool complete) : Resource(kind) {
    for (int i = 0; i < 4; ++i) {
        resourcesStorage[i] = 0;
    }
    isComplete = complete;
    amountOfCars = 0;
    amountOfTrucks = 0;
}

int SettlementPoints::getCurrentAmountCars() {
    return amountOfCars;
}

void SettlementPoints::setCurrentAmountCars(int newAmount) {
    amountOfCars = newAmount;
}

int SettlementPoints::getCurrentAmountTrucks() {
    return amountOfTrucks;
}

void SettlementPoints::setCurrentAmountTrucks(int newAmount) {
    amountOfTrucks = newAmount;
}

bool SettlementPoints::getIsComplete() {
    return isComplete;
}

void SettlementPoints::setIsComplete(bool newIsComplete) {
    isComplete = newIsComplete;
}

void SettlementPoints::ResetAllResources() {
    for (int i = 0; i < 4; ++i) {
        resourcesStorage[i] = 0;
    }
}

void SettlementPoints::printAlllResources() {
    for (int i = 0; i < 4; ++i) {
        std::cout << " " << resourcesStorage[i];
    }
}

void SettlementPoints::addForAllResources(int* amounts) {
    for (int i = 0; i < 4; i++) {
        addResourse(i, amounts[i]);
    }
}

void SettlementPoints::addResourse(int index, int amount) {

    if (resourcesStorage[index] + amount > ConfigurationManager::getMaxCapacity(getKindResourceCode(), index))
        resourcesStorage[index] = ConfigurationManager::getMaxCapacity(getKindResourceCode(), index);
    else
        resourcesStorage[index] += amount;
}

void SettlementPoints::addAmountToContemporaryStorage(std::string resource, int amount) {
    int index = resourcesStorage[ConfigurationManager::convertResourceToIndex(resource)];
    if (resourcesStorage[index] + amount > ConfigurationManager::getMaxCapacity(getKindResourceCode(), index))
        resourcesStorage[index] = ConfigurationManager::getMaxCapacity(getKindResourceCode(), index);
    else
        resourcesStorage[index] += amount;
}

int SettlementPoints::getAmountOfResourceInStorage(int index) {
    return resourcesStorage[index];
}

void SettlementPoints::setAmountOfResourceInStorage(int index, int amount) {
    resourcesStorage[index] = amount;
}