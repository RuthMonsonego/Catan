#include "Resource.h"
#include "ConfigurationManager.h"

Resource::Resource(int kind)
{
    this->kind = kind;
    amountOfResources = ConfigurationManager::getStartResouceAmount(kind);
}

int Resource::getKindResourceCode()
{
    return kind;
}

int Resource::getCurrentAmountResources()
{
    return amountOfResources;
}

void Resource::setCurrentAmountResources(int newAmount)
{
    if (newAmount < 0)
        throw "Negative resources amount";
    else if (newAmount < ConfigurationManager::getMaxResouceAmount(kind))
    {
        amountOfResources = newAmount;
    }
    else
        amountOfResources = ConfigurationManager::getMaxResouceAmount(kind);
}

void Resource::addOneToCurrentAmountResources() {
    if (amountOfResources < ConfigurationManager::getMaxResouceAmount(kind))
        amountOfResources++;
}

void Resource::TakeOneResourceTone()
{
    if (amountOfResources == 0)
        throw "The resource in this tail has run out";
    amountOfResources--;
}