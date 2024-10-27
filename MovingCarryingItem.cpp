#include "MovingCarryingItem.h"
#include<iostream>
#include<string>
#include "ConfigurationManager.h"

MovingCarryingItem::MovingCarryingItem(int k) :kind(k) {
	for (int i = 0; i < 4; ++i) {
		contemporaryCarrying[i] = 0;
	}
}

int MovingCarryingItem::getKindCode() {
	return kind;
}

int* MovingCarryingItem::getContemporaryCarrying() {
	return contemporaryCarrying;
}

void MovingCarryingItem::addAmountToContemporaryCarrying(std::string resource, int amount) {
	int index = contemporaryCarrying[ConfigurationManager::convertResourceToIndex(resource)];
	if (contemporaryCarrying[index] + amount > ConfigurationManager::getMaxCapacity(kind, index))
		contemporaryCarrying[index] = ConfigurationManager::getMaxCapacity(kind, index);
	else
		contemporaryCarrying[index] += amount;
}

int MovingCarryingItem::getAmountStayPlace(int index) {
	return ConfigurationManager::getMaxCapacity(kind, index) - contemporaryCarrying[index];
}

int MovingCarryingItem::getAmountInStorage(int index) {
	return contemporaryCarrying[index];
}

void MovingCarryingItem::setAmountInStorage(int index, int amount) {
	contemporaryCarrying[index] = amount;
}