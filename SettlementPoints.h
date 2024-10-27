#pragma once

#include "Resource.h"
#include <iostream>

class SettlementPoints : public Resource {
    int resourcesStorage[4];
    bool isComplete;
    int amountOfCars;
    int amountOfTrucks;

    void addResourse(int index, int amount);
public:
    SettlementPoints(int kind, bool complete);

    int getCurrentAmountCars();
    void setCurrentAmountCars(int newAmount);

    int getCurrentAmountTrucks();
    void setCurrentAmountTrucks(int newAmount);

    bool getIsComplete();
    void setIsComplete(bool newIsComplete);

    void ResetAllResources();
    void printAlllResources();
    void addForAllResources(int* amounts);
    void addAmountToContemporaryStorage(std::string resource, int amount);
    int getAmountOfResourceInStorage(int index);
    void setAmountOfResourceInStorage(int index, int amount);
};
